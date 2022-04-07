#include "NonPlayerCharacter.h"

#include "NonPlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "NonPlayerComponent.h"
#include "Character/ClothComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANonPlayerCharacter::ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NonPlayerComponent = CreateDefaultSubobject<UNonPlayerComponent>(TEXT("Non Player"));

	GetCharacterMovement()->bUseRVOAvoidance = true;

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

void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ANonPlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TArray<USceneComponent*> ChildComponents;
	GetMesh()->GetChildrenComponents(false, ChildComponents);

	if (!AIControllerClass)
	{
		AIControllerClass = ANonPlayerCharacterController::StaticClass();
	}

	for (auto&& Component : ChildComponents)
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
		{
			SkeletalMeshComponent->SetMasterPoseComponent(GetMesh());
		}
	}
}

int32 ANonPlayerCharacter::GetReputation() const
{
	return NonPlayerComponent->GetReputation();
}
