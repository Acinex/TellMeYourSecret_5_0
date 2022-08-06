// Copyright Acinex Games 2020

#include "CharacterBase.h"

#include "ClothComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	Voice = CreateDefaultSubobject<UAudioComponent>(TEXT("Voice"));

	Pants = CreateDefaultSubobject<UClothComponent>(TEXT("Pants"));
	Pants->SetClothSlot(EClothSlot::Pants);
	Pants->SetupAttachment(GetMesh());
	Underpants = CreateDefaultSubobject<UClothComponent>(TEXT("Underpants"));
	Underpants->SetClothSlot(EClothSlot::Underpants);
	Underpants->SetupAttachment(GetMesh());
	Bra = CreateDefaultSubobject<UClothComponent>(TEXT("Bra"));
	Bra->SetClothSlot(EClothSlot::Bra);
	Bra->SetupAttachment(GetMesh());
	Socks = CreateDefaultSubobject<UClothComponent>(TEXT("Socks"));
	Socks->SetClothSlot(EClothSlot::Socks);
	Socks->SetupAttachment(GetMesh());
	Shoes = CreateDefaultSubobject<UClothComponent>(TEXT("Shoes"));
	Shoes->SetClothSlot(EClothSlot::Shoes);
	Shoes->SetupAttachment(GetMesh());
	Top = CreateDefaultSubobject<UClothComponent>(TEXT("Top"));
	Top->SetClothSlot(EClothSlot::Top);
	Top->SetupAttachment(GetMesh());
	Dress = CreateDefaultSubobject<UClothComponent>(TEXT("Dress"));
	Dress->SetClothSlot(EClothSlot::Dress);
	Dress->SetupAttachment(GetMesh());
	Hat = CreateDefaultSubobject<UClothComponent>(TEXT("Hat"));
	Hat->SetClothSlot(EClothSlot::Hat);
	Hat->SetupAttachment(GetMesh());
	Gloves = CreateDefaultSubobject<UClothComponent>(TEXT("Gloves"));
	Gloves->SetClothSlot(EClothSlot::Gloves);
	Gloves->SetupAttachment(GetMesh());
}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TArray<USceneComponent*> ChildComponents;
	GetMesh()->GetChildrenComponents(false, ChildComponents);

	for (auto&& Component : ChildComponents)
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
		{
			SkeletalMeshComponent->SetMasterPoseComponent(GetMesh());
		}
	}

	Scale = GetActorScale().Z;
	IKTraceDistance = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * Scale;
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IKOffsetLeftFoot = FMath::VInterpTo(IKOffsetLeftFoot, FootTrace(LeftFootSocket, LeftFootSurface), DeltaTime, IKInterpSpeed);
	IKOffsetRightFoot = FMath::VInterpTo(IKOffsetRightFoot, FootTrace(RightFootSocket, RightFootSurface), DeltaTime, IKInterpSpeed);
}

FVector ACharacterBase::FootTrace(FName Socket, TEnumAsByte<EPhysicalSurface>& OutSurface) const
{
	FVector SocketLocation = GetMesh()->GetSocketLocation(Socket);
	FVector ActorLocation = GetActorLocation();

	FVector Start = {SocketLocation.X, SocketLocation.Y, ActorLocation.Z};
	FVector End = {SocketLocation.X, SocketLocation.Y, ActorLocation.Z - IKTraceDistance};
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		OutSurface = UGameplayStatics::GetSurfaceType(Hit);
		return Hit.Location / Scale;
	}

	OutSurface = SurfaceType_Default;

	return FVector::Zero();
}
