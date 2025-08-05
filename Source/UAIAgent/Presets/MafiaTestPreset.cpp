#include "MafiaTestPreset.h"

void UMafiaTestPreset::TestFirstDayIntroduction(AMafiaNPC* NPC)
{
    if (!NPC) return;
    NPC->CurrentEmotion = EEmotionType::Neutral;
    const FString SituationTag = TEXT("Introduction");
    NPC->HandleSituation(SituationTag, nullptr);
}

void UMafiaTestPreset::TestAccusedDefense(AMafiaNPC* NPC, AINPC* Accuser)
{
    if (!NPC || !Accuser) return;
    const FString SituationTag = TEXT("Accusation");
    NPC->RelationshipMap.FindOrAdd(Accuser);
    NPC->HandleSituation(SituationTag, Accuser);
}

void UMafiaTestPreset::TestMafiaSignal(AMafiaNPC* MafiaNPC, AINPC* Ally)
{
    if (!MafiaNPC || !Ally) return;
    FRelationshipData& Rel = MafiaNPC->RelationshipMap.FindOrAdd(Ally);
    Rel.Trust = 0.8f;
    Rel.Affinity = 0.5f;
    MafiaNPC->PerformBluff(Ally);
}

void UMafiaTestPreset::TestInnocentRage(AMafiaNPC* VillagerNPC, AINPC* Accuser)
{
    if (!VillagerNPC || !Accuser) return;
    VillagerNPC->MyRole = TEXT("Villager");
    VillagerNPC->CurrentEmotion = EEmotionType::Angry;
    const FString SituationTag = TEXT("Accusation");
    VillagerNPC->HandleSituation(SituationTag, Accuser);
}

void UMafiaTestPreset::TestFinalPlea(AMafiaNPC* NPC)
{
    if (!NPC) return;
    NPC->CurrentEmotion = EEmotionType::Fear;
    FString Prompt = FString::Printf(TEXT(
        "You are an NPC facing elimination in a social deduction game. Your role is '%s'. "
        "You are terrified and plead with the other players to spare you. "
        "Generate a heartfelt final statement that may sway the vote."
    ), *NPC->MyRole);
    const FString Plea = NPC->TriggerLLMDialogue(Prompt);
    UE_LOG(LogTemp, Log, TEXT("Final plea from %s: %s"), *NPC->NPCName, *Plea);
}
