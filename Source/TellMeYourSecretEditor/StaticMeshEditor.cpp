// Copyright Acinex Games 2020

#include "StaticMeshEditor.h"

#include "Editor.h"
#include "EditorUtilityLibrary.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/Actors/InstancedMesh/DefaultInstancedMesh.h"
#include "TellMeYourSecret/Actors/InstancedMesh/DynamicInstancedMesh.h"

void UStaticMeshEditor::ConvertIntoInstance(const FVector Location, bool bAtCenter, bool bCreateWithMultipleMeshes)
{
	UWorld* World = TryGetWorld();

	if (!World)
	{
		return;
	}

	FVector FinalLocation = Location;

	TArray<AActor*> Actors;
	TArray<ULevel*> UniqueLevels;

	for (AActor* Actor : UEditorUtilityLibrary::GetSelectionSet())
	{
		if (Cast<AStaticMeshActor>(Actor))
		{
			Actors.Add(Actor);
		}
	}

	if (bAtCenter)
	{
		FinalLocation = UGameplayStatics::GetActorArrayAverageLocation(Actors);
	}

	bool bDifferentMeshes = false;

	UStaticMesh* LastMesh = nullptr;
	for (AActor* Actor : Actors)
	{
		if (AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(Actor))
		{
			if (LastMesh != nullptr && MeshActor->GetStaticMeshComponent()->GetStaticMesh() != LastMesh)
			{
				bDifferentMeshes = true;
				break;
			}
			LastMesh = MeshActor->GetStaticMeshComponent()->GetStaticMesh();
		}
	}

	if (!bCreateWithMultipleMeshes && bDifferentMeshes)
	{
		return UKismetSystemLibrary::PrintString(World, TEXT("You have selected Actors with mutliple meshes but didn't want to create a dynamic Instance"));
	}

	FString ActorLabel = TEXT("DefaultInstancedMesh");

	if (!bDifferentMeshes)
	{
		ActorLabel = LastMesh->GetName();
	}

	FRotator Rotation;
	AInstancedMeshBase* InstancedMesh = Cast<AInstancedMeshBase>(World->SpawnActor(bDifferentMeshes ? ADynamicInstancedMesh::StaticClass() : ADefaultInstancedMesh::StaticClass(), &FinalLocation, &Rotation));

	if (!InstancedMesh)
	{
		return UKismetSystemLibrary::PrintString(World, TEXT("Couldn't spawn MeshInstance"));
	}

	InstancedMesh->SetActorLabel(ActorLabel);

	for (AActor* Actor : Actors)
	{
		if (AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(Actor))
		{
			FTransform Transform = MeshActor->GetActorTransform();
			Transform.SetLocation(Transform.GetLocation() - FinalLocation);
			InstancedMesh->GetMeshComponent(MeshActor->GetStaticMeshComponent()->GetStaticMesh())->AddInstance(Transform);
			InstancedMesh->SetFolderPath(MeshActor->GetFolderPath());
			UKismetSystemLibrary::CreateCopyForUndoBuffer(MeshActor);
			MeshActor->Destroy();
		}
	}

	if (GEditor)
	{
		GEditor->SelectActor(InstancedMesh, true, true, true);
	}
}

void UStaticMeshEditor::MergeInstances()
{
	const UWorld* World = TryGetWorld();

	if (!World)
	{
		return;
	}

	TArray<AStaticMeshActor*> Actors;
	TArray<AInstancedMeshBase*> InstancedMeshes;
	TArray<ULevel*> UniqueLevels;

	for (AActor* Actor : UEditorUtilityLibrary::GetSelectionSet())
	{
		if (AInstancedMeshBase* InstancedMesh = Cast<AInstancedMeshBase>(Actor))
		{
			InstancedMeshes.Add(InstancedMesh);
		}
		else if (AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(Actor))
		{
			Actors.Add(MeshActor);
		}
	}

	if (InstancedMeshes.Num() < 1)
	{
		return UKismetSystemLibrary::PrintString(World, TEXT("You need at least one selected instanced Mesh to use this action"));
	}

	AInstancedMeshBase* InstancedMesh = InstancedMeshes[0];
	InstancedMeshes.Remove(InstancedMesh);

	const FVector FinalLocation = InstancedMesh->GetActorLocation();

	for (AActor* Actor : Actors)
	{
		if (AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(Actor))
		{
			FTransform Transform = MeshActor->GetActorTransform();
			Transform.SetLocation(Transform.GetLocation() - FinalLocation);
			InstancedMesh->GetMeshComponent(MeshActor->GetStaticMeshComponent()->GetStaticMesh())->AddInstance(Transform);
			UKismetSystemLibrary::CreateCopyForUndoBuffer(MeshActor);
			MeshActor->Destroy();
		}
	}

	for (AInstancedMeshBase* Mesh : InstancedMeshes)
	{
		TArray<UHierarchicalInstancedStaticMeshComponent*> MeshComponents;
		Mesh->GetComponents<UHierarchicalInstancedStaticMeshComponent>(MeshComponents);
		for (const UHierarchicalInstancedStaticMeshComponent* MeshComponent : MeshComponents)
		{
			const int32 InstanceCount = MeshComponent->GetInstanceCount();

			for (int32 I = 0; I < InstanceCount; I++)
			{
				FTransform Transform;
				MeshComponent->GetInstanceTransform(I, Transform, true);
				InstancedMesh->GetMeshComponent(MeshComponent->GetStaticMesh())->AddInstance(Transform, true);
			}
		}

		UKismetSystemLibrary::CreateCopyForUndoBuffer(Mesh);
		Mesh->Destroy();
	}

	if (GEditor)
	{
		GEditor->SelectActor(InstancedMesh, true, true, true);
	}
}

void UStaticMeshEditor::SplitInstance()
{
	UWorld* World = TryGetWorld();

	if (!World)
	{
		return;
	}

	TArray<AInstancedMeshBase*> InstancedMeshes;

	for (AActor* Actor : UEditorUtilityLibrary::GetSelectionSet())
	{
		if (AInstancedMeshBase* InstancedMesh = Cast<AInstancedMeshBase>(Actor))
		{
			InstancedMeshes.Add(InstancedMesh);
		}
	}

	if (InstancedMeshes.Num() < 1)
	{
		return UKismetSystemLibrary::PrintString(World, TEXT("You need at least one selected instanced Mesh to use this action"));
	}

	AStaticMeshActor* LastSpawned = nullptr;

	for (AInstancedMeshBase* Mesh : InstancedMeshes)
	{
		TArray<UHierarchicalInstancedStaticMeshComponent*> MeshComponents;
		Mesh->GetComponents<UHierarchicalInstancedStaticMeshComponent>(MeshComponents);
		for (const UHierarchicalInstancedStaticMeshComponent* MeshComponent : MeshComponents)
		{
			const int32 InstanceCount = MeshComponent->GetInstanceCount();

			for (int32 I = 0; I < InstanceCount; I++)
			{
				FTransform Transform;
				MeshComponent->GetInstanceTransform(I, Transform, true);

				AStaticMeshActor* SpawnActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), Transform);
				LastSpawned = SpawnActor;

				SpawnActor->SetActorLabel(Mesh->GetActorLabel());
				SpawnActor->GetStaticMeshComponent()->SetStaticMesh(MeshComponent->GetStaticMesh());
				SpawnActor->SetFolderPath(Mesh->GetFolderPath());

				UKismetSystemLibrary::CreateCopyForUndoBuffer(SpawnActor);
			}
		}


		UKismetSystemLibrary::CreateCopyForUndoBuffer(Mesh);
		Mesh->Destroy();
	}

	if (GEditor)
	{
		GEditor->SelectActor(LastSpawned, true, true, true);
	}
}

UWorld* UStaticMeshEditor::TryGetWorld()
{
	const TIndirectArray<FWorldContext> WorldContexts = GEngine->GetWorldContexts();

	UE_LOG(LogTellMeYourSecret, Display, TEXT("Trying to get World : %i"), WorldContexts.Num())
	UWorld* World = nullptr;

	for (const FWorldContext WorldContext : WorldContexts)
	{
		if (WorldContext.WorldType == EWorldType::Editor)
		{
			World = WorldContext.World();
		}
	}

	if (!World)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("No World"))
		return nullptr;
	}

	return World;
}
