#include "AINPC.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

AINPC::AINPC()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AINPC::HandleSituation(const FString& SituationTag, AINPC* SourceNPC)
{
    UpdateInternalState(SituationTag, SourceNPC);
    EReactionType ChosenReaction = DecideReaction(SituationTag, SourceNPC);
    ExecuteReaction(ChosenReaction, SourceNPC);
}

void AINPC::UpdateInternalState(const FString& SituationTag, AINPC* SourceNPC)
{
    if (SourceNPC)
    {
        FRelationshipData* Relationship = RelationshipMap.Find(SourceNPC);
        if (!Relationship)
        {
            Relationship = &RelationshipMap.Add(SourceNPC);
        }
        if (SituationTag.Equals(TEXT("Accusation"), ESearchCase::IgnoreCase))
        {
            Relationship->Trust = FMath::Clamp(Relationship->Trust - 0.3f, 0.f, 1.f);
            Relationship->Affinity -= 0.2f;
        }
        else if (SituationTag.Equals(TEXT("Introduction"), ESearchCase::IgnoreCase))
        {
            Relationship->Trust = FMath::Clamp(Relationship->Trust + 0.1f, 0.f, 1.f);
            Relationship->Affinity += 0.1f;
        }
        Relationship->InteractionHistory.Add(SituationTag);
    }

    if (SituationTag.Equals(TEXT("Accusation"), ESearchCase::IgnoreCase))
    {
        CurrentEmotion = EEmotionType::Angry;
    }
    else if (SituationTag.Equals(TEXT("Praise"), ESearchCase::IgnoreCase))
    {
        CurrentEmotion = EEmotionType::Happy;
    }
    else
    {
        CurrentEmotion = EEmotionType::Neutral;
    }
}

EReactionType AINPC::DecideReaction(const FString& SituationTag, AINPC* SourceNPC)
{
    if (CurrentEmotion == EEmotionType::Angry)
    {
        return EReactionType::Defend;
    }
    else if (SituationTag.Equals(TEXT("Introduction"), ESearchCase::IgnoreCase))
    {
        return EReactionType::Speak;
    }
    else if (SituationTag.Equals(TEXT("Accusation"), ESearchCase::IgnoreCase))
    {
        return EReactionType::Defend;
    }
    return EReactionType::Speak;
}

void AINPC::ExecuteReaction(EReactionType ReactionType, AINPC* TargetNPC)
{
    LastReaction = ReactionType;
    const FString ReactionString = UEnum::GetValueAsString(ReactionType);
    const FString TargetName = TargetNPC ? TargetNPC->NPCName : TEXT("None");
    UE_LOG(LogTemp, Log, TEXT("%s performs reaction %s towards %s"), *NPCName, *ReactionString, *TargetName);
    if (ReactionType == EReactionType::Speak || ReactionType == EReactionType::Bluff || ReactionType == EReactionType::Defend)
    {
        FString Prompt = FString::Printf(TEXT("NPC '%s' with MBTI %s feels %s in situation '%s'. Generate a short line of dialogue."), *NPCName, *MBTIType, *UEnum::GetValueAsString(CurrentEmotion), *TargetName);
        const FString GeneratedLine = TriggerLLMDialogue(Prompt);
        UE_LOG(LogTemp, Log, TEXT("Generated dialogue: %s"), *GeneratedLine);
    }
}

FString AINPC::TriggerLLMDialogue(const FString& PromptContext)
{
    return SendPromptToLLM(PromptContext);
}

FString AINPC::SendPromptToLLM(const FString& Prompt) const
{
    UE_LOG(LogTemp, Log, TEXT("Sending prompt to LLM: %s"), *Prompt);
    return FString::Printf(TEXT("[LLM Response to: %s]"), *Prompt);
}
