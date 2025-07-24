#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReactionSimulatorManager.generated.h"

class USimulationScenarioAsset;

/**
 * Actor responsible for executing a simulation scenario at game start.
 */
UCLASS()
class UAIAGENT_API AReactionSimulatorManager : public AActor
{
    GENERATED_BODY()

public:
    AReactionSimulatorManager();

protected:
    virtual void BeginPlay() override;

public:
    /** Scenario asset to simulate when the game starts */
    UPROPERTY(EditAnywhere, Category="Simulation")
    TObjectPtr<USimulationScenarioAsset> Scenario;
};

