#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReactionTypes.h"
#include "SimulationScenarioAsset.generated.h"

/**
 * DataAsset representing a single reaction simulation scenario.
 */
UCLASS(BlueprintType)
class UAIAGENT_API USimulationScenarioAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /** Name of the NPC */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString NPCName;

    /** Situation code for this scenario */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESituationCode SituationCode = ESituationCode::S1;

    /** Emotion vector values */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FEmotionVector EmotionVector;

    /** Short persona or personality summary */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Persona;

    /** Execute simulation for this scenario */
    UFUNCTION(BlueprintCallable, Category="Simulation")
    void Simulate() const;
};

