#include "ReactionSimWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/EditableTextBox.h"

void UReactionSimWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RunButton)
    {
        RunButton->OnClicked.AddDynamic(this, &UReactionSimWidget::OnRunSimulation);
    }

    // Initialize emotion values to zero
    for (int32 i = 0; i < 6; ++i)
    {
        EmotionValues[i] = 0.f;
    }
}

void UReactionSimWidget::OnRunSimulation()
{
    if (JoySlider)    EmotionValues[0] = JoySlider->GetValue();
    if (AngerSlider)  EmotionValues[1] = AngerSlider->GetValue();
    if (SadnessSlider) EmotionValues[2] = SadnessSlider->GetValue();
    if (SurpriseSlider) EmotionValues[3] = SurpriseSlider->GetValue();
    if (FearSlider)   EmotionValues[4] = FearSlider->GetValue();
    if (DisgustSlider) EmotionValues[5] = DisgustSlider->GetValue();

    // Placeholder: store dropdown selections or perform further logic
    FString SelectedNPC = NPCDropdown ? NPCDropdown->GetSelectedOption() : TEXT("");
    FString SelectedSituation = SituationDropdown ? SituationDropdown->GetSelectedOption() : TEXT("");

    // Clear reaction description for now
    if (ReactionDescriptionText)
    {
        ReactionDescriptionText->SetText(FText::FromString(TEXT("")));
    }

    // Append a placeholder dialogue entry
    if (DialogueLogBox)
    {
        UTextBlock* NewLine = NewObject<UTextBlock>(this);
        FString Line = FString::Printf(TEXT("%s: (dialogue placeholder)"), *SelectedNPC);
        NewLine->SetText(FText::FromString(Line));
        DialogueLogBox->AddChildToVerticalBox(NewLine);
    }
}

