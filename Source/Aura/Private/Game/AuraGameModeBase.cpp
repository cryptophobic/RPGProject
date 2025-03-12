#include "Game/AuraGameModeBase.h"
#include "Game/TurnManager.h" // Include TurnManager

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (TurnManager == nullptr) // Check to prevent double-spawning
	{
		// Spawn TurnManager in the world
		TurnManager = GetWorld()->SpawnActor<ATurnManager>(ATurnManager::StaticClass());

		if (TurnManager)
		{
			UE_LOG(LogTemp, Warning, TEXT("TurnManager spawned successfully!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn TurnManager!"));
		}
	}
}
