#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

// Forward declare
class ATurnManager;

UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "Turn System")
    ATurnManager* TurnManager; // Pointer to TurnManager instance
};
