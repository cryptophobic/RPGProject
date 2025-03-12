#include "Components/CharacterStatsComponent.h"

UCharacterStatsComponent::UCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FCharacterStats UCharacterStatsComponent::GetFinalStats() const
{
	FCharacterStats FinalStats;

	FinalStats.Speed = BaseStats.Speed + Modifiers.Speed;
	FinalStats.Strength = BaseStats.Strength + Modifiers.Strength;
	FinalStats.Dexterity = BaseStats.Dexterity + Modifiers.Dexterity;
	FinalStats.Constitution = BaseStats.Constitution + Modifiers.Constitution;

	return FinalStats;
}

void UCharacterStatsComponent::ApplyModifier(const FCharacterStats& StatChanges)
{
	Modifiers.Speed += StatChanges.Speed;
	Modifiers.Strength += StatChanges.Strength;
	Modifiers.Dexterity += StatChanges.Dexterity;
	Modifiers.Constitution += StatChanges.Constitution;
}

void UCharacterStatsComponent::ClearModifiers()
{
	Modifiers = FCharacterStats(); // Reset modifiers
}

void UCharacterStatsComponent::TakeDamage(int32 Amount)
{
	int32 EffectiveDamage = FMath::Max(Amount - GetFinalStats().Constitution, 1); // At least 1 damage
	BaseStats.Constitution = FMath::Max(BaseStats.Constitution - EffectiveDamage, 0);
}
