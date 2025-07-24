#include "SimulationScenarioAsset.h"


void USimulationScenarioAsset::Simulate() const
{
    UE_LOG(LogTemp, Log, TEXT("Simulating NPC %s | Situation %s"), *NPCName,
        *StaticEnum<ESituationCode>()->GetNameStringByValue((int64)SituationCode));

    UE_LOG(LogTemp, Log, TEXT("Emotion: Joy %.2f Anger %.2f Sadness %.2f Surprise %.2f Fear %.2f Disgust %.2f"),
        EmotionVector.Joy, EmotionVector.Anger, EmotionVector.Sadness,
        EmotionVector.Surprise, EmotionVector.Fear, EmotionVector.Disgust);
    UE_LOG(LogTemp, Log, TEXT("Persona: %s"), *Persona);
}

