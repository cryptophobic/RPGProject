// Copyright Cryptophobic

#include "Character/AuraCharacterBase.h"
#include "Game/TurnManager.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h" // To get GameMode easily


// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("CharacterStatsComponent"));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	FindTurnManager(); // Auto-find TurnManager when game starts
}

void AAuraCharacterBase::StartTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("%s starts their turn!"), *GetName());
	// Here, you can enable input for player or start AI for enemies
}

void AAuraCharacterBase::EndMyTurn()
{
	if (TurnManager)
	{
		TurnManager->NextTurn();
	}
}

void AAuraCharacterBase::FindTurnManager()
{
	// Get current GameMode and cast to your custom GameMode
	if (AAuraGameModeBase* GM = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		TurnManager = GM->TurnManager;

		if (TurnManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s found TurnManager."), *GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s could NOT find TurnManager!"), *GetName());
		}
	}
}

// Example Move function
void AAuraCharacterBase::MoveToTile(const FVector& Destination)
{
	int32 MoveRange = StatsComponent->GetFinalStats().Speed;

	// Check distance to destination
	float Distance = FVector::Dist(GetActorLocation(), Destination);

	// Assuming 100 units per tile
	int32 TilesToMove = FMath::FloorToInt(Distance / 100.0f);

	if (TilesToMove <= MoveRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s moves to tile (distance: %d tiles)"), *GetName(), TilesToMove);

		// Move the character (simple teleport for now)
		SetActorLocation(Destination);

		// After moving, end turn automatically (optional)
		EndMyTurn();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s can't move that far! Max range: %d tiles"), *GetName(), MoveRange);
	}
}

// Example Attack function
void AAuraCharacterBase::AttackTarget(AAuraCharacterBase* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("%s tried to attack but no target!"), *GetName());
		return;
	}

	// Check attack range (for now let's assume 1 tile = 100 units range)
	float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());

	// You can later use weapon range here
	const float MaxAttackRange = 200.0f;

	if (Distance > MaxAttackRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s can't attack: target too far!"), *GetName());
		return;
	}

	// Calculate damage
	int32 AttackerStrength = StatsComponent->GetFinalStats().Strength;
	int32 DefenderConstitution = Target->StatsComponent->GetFinalStats().Constitution;

	int32 Damage = FMath::Max(AttackerStrength - (DefenderConstitution / 2), 1); // Always deal at least 1 damage

	UE_LOG(LogTemp, Warning, TEXT("%s attacks %s for %d damage!"), *GetName(), *Target->GetName(), Damage);

	// Apply damage
	Target->StatsComponent->TakeDamage(Damage);

	// End turn automatically after attack (optional)
	EndMyTurn();
}
