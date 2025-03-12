// Copyright Cryptophobic


#include "Game/TurnManager.h"
#include "Character/AuraCharacterBase.h"
#include "Components/CharacterStatsComponent.h"

ATurnManager::ATurnManager()
{
	PrimaryActorTick.bCanEverTick = false; // Disable ticking unless needed
	CurrentTurnIndex = 0;
}

void ATurnManager::StartBattle()
{
	SortCombatantsBySpeed();
	CurrentTurnIndex = 0;
	StartTurnForCurrentUnit();
}

void ATurnManager::NextTurn()
{
	// Move to next character
	CurrentTurnIndex = (CurrentTurnIndex + 1) % Combatants.Num();

	// Optional: Check if battle should end
	if (IsBattleOver())
	{
		UE_LOG(LogTemp, Warning, TEXT("Battle is over!"));
		return;
	}

	StartTurnForCurrentUnit();
}

void ATurnManager::AddCombatant(AAuraCharacterBase* NewCombatant)
{
	Combatants.AddUnique(NewCombatant);
	SortCombatantsBySpeed(); // Re-sort when new unit added
}

void ATurnManager::RemoveCombatant(AAuraCharacterBase* DeadCombatant)
{
	Combatants.Remove(DeadCombatant);
}

void ATurnManager::SortCombatantsBySpeed()
{
	Combatants.Sort([](const AAuraCharacterBase& A, const AAuraCharacterBase& B)
	{
		const auto* AStats = A.FindComponentByClass<UCharacterStatsComponent>();
		const auto* BStats = B.FindComponentByClass<UCharacterStatsComponent>();

		return AStats->GetFinalStats().Speed > BStats->GetFinalStats().Speed; // Descending speed
	});
}

void ATurnManager::StartTurnForCurrentUnit()
{
	if (Combatants.IsValidIndex(CurrentTurnIndex))
	{
		AAuraCharacterBase* CurrentUnit = Combatants[CurrentTurnIndex];
		UE_LOG(LogTemp, Warning, TEXT("Starting turn for: %s"), *CurrentUnit->GetName());

		// You can call a "StartTurn" function on unit here
		// CurrentUnit->StartTurn();

		// Example: trigger Blueprint event (optional)
		// OnUnitTurnStart.Broadcast(CurrentUnit);
	}
}

bool ATurnManager::IsBattleOver()
{
	// Example placeholder: battle is over if only 1 team remains
	return false; // Implement real logic later (optional)
}
