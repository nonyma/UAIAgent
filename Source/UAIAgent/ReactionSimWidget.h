#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ReactionSimWidget.generated.h"

/** Enumeration for situation codes */
UENUM(BlueprintType)
enum class ESituationCode : uint8
{
    S1 UMETA(DisplayName="S1"),
    S2 UMETA(DisplayName="S2"),
    S3 UMETA(DisplayName="S3"),
    S4 UMETA(DisplayName="S4"),
    S5 UMETA(DisplayName="S5"),
    S6 UMETA(DisplayName="S6")
};

/** Widget that provides UI for the reaction simulator */
UCLASS()
class UAIAgent_API UReactionSimWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    /** NPC selection dropdown */
    UPROPERTY(meta=(BindWidget))
    UComboBoxString* NPCDropdown;

    /** Situation selection dropdown */
    UPROPERTY(meta=(BindWidget))
    UComboBoxString* SituationDropdown;

    /** Emotion sliders */
    UPROPERTY(meta=(BindWidget))
    USlider* JoySlider;

    UPROPERTY(meta=(BindWidget))
    USlider* AngerSlider;

    UPROPERTY(meta=(BindWidget))
    USlider* SadnessSlider;

    UPROPERTY(meta=(BindWidget))
    USlider* SurpriseSlider;

    UPROPERTY(meta=(BindWidget))
    USlider* FearSlider;

    UPROPERTY(meta=(BindWidget))
    USlider* DisgustSlider;

    /** Persona description text */
    UPROPERTY(meta=(BindWidget))
    UTextBlock* PersonaDescriptionText;

    /** Reaction description output */
    UPROPERTY(meta=(BindWidget))
    UTextBlock* ReactionDescriptionText;

    /** Dialogue log vertical box */
    UPROPERTY(meta=(BindWidget))
    UVerticalBox* DialogueLogBox;

    /** Run simulation button */
    UPROPERTY(meta=(BindWidget))
    UButton* RunButton;

private:
    /** Stored emotion values in same order as UI */
    float EmotionValues[6];

    UFUNCTION()
    void OnRunSimulation();
};

