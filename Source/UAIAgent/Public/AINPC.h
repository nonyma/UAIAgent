#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCEnums.h"
#include "AINPC.generated.h"

UCLASS(Blueprintable)
class AINPC : public AActor
{
    GENERATED_BODY()
public:
    AINPC();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    FString NPCName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    FString MBTIType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    EEmotionType CurrentEmotion = EEmotionType::Neutral;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
    EReactionType LastReaction = EReactionType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
    TMap<AINPC*, FRelationshipData> RelationshipMap;

    UFUNCTION(BlueprintCallable, Category = "NPC")
    virtual void HandleSituation(const FString& SituationTag, AINPC* SourceNPC);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    virtual void UpdateInternalState(const FString& SituationTag, AINPC* SourceNPC);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    virtual EReactionType DecideReaction(const FString& SituationTag, AINPC* SourceNPC);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    virtual void ExecuteReaction(EReactionType ReactionType, AINPC* TargetNPC);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    virtual FString TriggerLLMDialogue(const FString& PromptContext);

protected:
    FString SendPromptToLLM(const FString& Prompt) const;
};
