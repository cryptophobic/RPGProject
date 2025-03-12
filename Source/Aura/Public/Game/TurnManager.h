// Copyright Cryptophobic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

// Forward declarations
class AAuraCharacterBase;

UCLASS()
class AURA_API ATurnManager : public AActor
{
	GENERATED_BODY()

public:
	ATurnManager();

	// All units participating in combat
	UPROPERTY(BlueprintReadOnly, Category = "Turn Order")
	TArray<AAuraCharacterBase*> Combatants;

	// Current index in turn queue
	UPROPERTY(BlueprintReadOnly, Category = "Turn Order")
	int32 CurrentTurnIndex;

	// Start the whole battle turn system
	UFUNCTION(BlueprintCallable, Category = "Turn Order")
	void StartBattle();

	// Go to next turn
	UFUNCTION(BlueprintCallable, Category = "Turn Order")
	void NextTurn();

	// Add new unit dynamically (optional)
	UFUNCTION(BlueprintCallable, Category = "Turn Order")
	void AddCombatant(AAuraCharacterBase* NewCombatant);

	// Remove unit dynamically (optional for death/removal)
	UFUNCTION(BlueprintCallable, Category = "Turn Order")
	void RemoveCombatant(AAuraCharacterBase* DeadCombatant);

private:
	// Sort characters based on Speed stat
	void SortCombatantsBySpeed();

	// Start the turn for current unit
	void StartTurnForCurrentUnit();

	// Internal check if battle over (optional to implement later)
	bool IsBattleOver();
};
