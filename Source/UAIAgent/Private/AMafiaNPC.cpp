#include "AMafiaNPC.h"

AMafiaNPC::AMafiaNPC()
{
    MyRole = TEXT("Villager");
}

AINPC* AMafiaNPC::PickBluffTarget()
{
    if (RelationshipMap.Num() == 0)
    {
        return nullptr;
    }
    AINPC* BestTarget = nullptr;
    float BestScore = -1.f;
    for (const auto& Elem : RelationshipMap)
    {
        AINPC* Candidate = Elem.Key;
        if (!Candidate) continue;
        const FRelationshipData& Data = Elem.Value;
        const float Score = Data.Trust * 0.7f + Data.Affinity * 0.3f;
        if (Score > BestScore)
        {
            BestScore = Score;
            BestTarget = Candidate;
        }
    }
    return BestTarget;
}

void AMafiaNPC::PerformBluff(AINPC* TargetNPC)
{
    if (!TargetNPC)
    {
        ExecuteReaction(EReactionType::Speak, nullptr);
        return;
    }
    FString Prompt = FString::Printf(TEXT(
        "You are an NPC in a social deduction game. Your hidden role is '%s'. "
        "You want to mislead other players by bluffing. Target player: '%s'. "
        "Your personality type is %s and your current emotion is %s. "
        "Generate a short persuasive statement that casts suspicion on the target without revealing your own role."
        ), *MyRole, *TargetNPC->NPCName, *MBTIType, *UEnum::GetValueAsString(CurrentEmotion));
    const FString BluffLine = TriggerLLMDialogue(Prompt);
    LastReaction = EReactionType::Bluff;
    UE_LOG(LogTemp, Log, TEXT("%s bluffs at %s: %s"), *NPCName, *TargetNPC->NPCName, *BluffLine);
}

EReactionType AMafiaNPC::DecideReaction(const FString& SituationTag, AINPC* SourceNPC)
{
    if (MyRole.Equals(TEXT("Mafia"), ESearchCase::IgnoreCase) && SituationTag.Equals(TEXT("Accusation"), ESearchCase::IgnoreCase))
    {
        AINPC* BluffTarget = PickBluffTarget();
        if (BluffTarget)
        {
            PerformBluff(BluffTarget);
            return EReactionType::Bluff;
        }
    }
    if (SituationTag.Equals(TEXT("Introduction"), ESearchCase::IgnoreCase) && MyRole.Equals(TEXT("Mafia"), ESearchCase::IgnoreCase))
    {
        return EReactionType::Speak;
    }
    return Super::DecideReaction(SituationTag, SourceNPC);
}
