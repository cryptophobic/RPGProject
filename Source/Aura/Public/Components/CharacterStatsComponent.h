// Copyright Cryptophobic

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Dexterity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Constitution;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCharacterStats BaseStats;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	FCharacterStats Modifiers;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	FCharacterStats GetFinalStats() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyModifier(const FCharacterStats& StatChanges);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ClearModifiers();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void TakeDamage(int32 Amount);
		
};
