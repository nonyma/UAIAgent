#include "ReactionSimulatorManager.h"

#include "SimulationScenarioAsset.h"

AReactionSimulatorManager::AReactionSimulatorManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AReactionSimulatorManager::BeginPlay()
{
    Super::BeginPlay();

    if (Scenario)
    {
        Scenario->Simulate();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ReactionSimulatorManager has no Scenario asset."));
    }
}

