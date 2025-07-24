#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReactionTypes.h"
#include "ReactionSimulatorWidget.generated.h"

class UComboBoxString;
class USlider;
class UButton;
class UTextBlock;
class UVerticalBox;

/**\n * UI widget for NPC reaction simulation.\n */
UCLASS(Blueprintable)
class UAIAGENT_API UReactionSimulatorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UComboBoxString> NPCSelector;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UComboBoxString> SituationSelector;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> JoySlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> AngerSlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> SadnessSlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> SurpriseSlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> FearSlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> DisgustSlider;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ExecuteButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PersonaSummaryText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ReactionDescriptionText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> DialogueBox;

private:
    UFUNCTION()
    void OnExecuteClicked();

    FString BuildInputHash(const FString& NpcName, ESituationCode Situation, const FEmotionVector& Vector) const;

    FReactionOutput QueryLocalDb(const FString& Hash) const;

    void CacheLocal(const FString& Hash, const FReactionOutput& Output);

    TMap<FString, FReactionOutput> LocalDb;
};

