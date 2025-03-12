// Copyright Cryptophobic

#pragma once

#include "Components/CharacterStatsComponent.h"
#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ATurnManager;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

	// Pointer to TurnManager
	UPROPERTY(BlueprintReadOnly, Category = "Turn System")
	ATurnManager* TurnManager;

	// Function to find and set TurnManager automatically
	UFUNCTION(BlueprintCallable, Category = "Turn System")
	void FindTurnManager();

	// Move and Attack API
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void MoveToTile(const FVector& Destination);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AttackTarget(AAuraCharacterBase* Target);
	
	// Virtual function for turn start
	virtual void StartTurn();

	// Function to end turn (call TurnManager->NextTurn)
	UFUNCTION(BlueprintCallable)
	void EndMyTurn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	UCharacterStatsComponent* StatsComponent;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
