#include "ReactionSimulatorWidget.h"

#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "ReactionTypes.h"

void UReactionSimulatorWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ExecuteButton)
    {
        ExecuteButton->OnClicked.AddDynamic(this, &UReactionSimulatorWidget::OnExecuteClicked);
    }
}

void UReactionSimulatorWidget::OnExecuteClicked()
{
    const FString NpcName = NPCSelector ? NPCSelector->GetSelectedOption() : FString();
    const FString SituationStr = SituationSelector ? SituationSelector->GetSelectedOption() : FString();

    ESituationCode Situation = ESituationCode::S1;
    if (SituationStr == TEXT("S2")) Situation = ESituationCode::S2;
    else if (SituationStr == TEXT("S3")) Situation = ESituationCode::S3;
    else if (SituationStr == TEXT("S4")) Situation = ESituationCode::S4;
    else if (SituationStr == TEXT("S5")) Situation = ESituationCode::S5;
    else if (SituationStr == TEXT("S6")) Situation = ESituationCode::S6;

    FEmotionVector Vector;
    if (JoySlider) Vector.Joy = JoySlider->GetValue();
    if (AngerSlider) Vector.Anger = AngerSlider->GetValue();
    if (SadnessSlider) Vector.Sadness = SadnessSlider->GetValue();
    if (SurpriseSlider) Vector.Surprise = SurpriseSlider->GetValue();
    if (FearSlider) Vector.Fear = FearSlider->GetValue();
    if (DisgustSlider) Vector.Disgust = DisgustSlider->GetValue();

    const FString Hash = BuildInputHash(NpcName, Situation, Vector);

    FReactionOutput Output = QueryLocalDb(Hash);
    if (Output.ReactionDescription.IsEmpty())
    {
        // Stub LLM response
        Output.ReactionDescription = TEXT("반응 없음");
        Output.Dialogue = TEXT("...");
        CacheLocal(Hash, Output);
    }

    if (ReactionDescriptionText)
    {
        ReactionDescriptionText->SetText(FText::FromString(Output.ReactionDescription));
    }

    if (DialogueBox)
    {
        UTextBlock* NewLine = NewObject<UTextBlock>(this);
        if (NewLine)
        {
            NewLine->SetText(FText::FromString(Output.Dialogue));
            DialogueBox->AddChildToVerticalBox(NewLine);
        }
    }
}

FString UReactionSimulatorWidget::BuildInputHash(const FString& NpcName, ESituationCode Situation, const FEmotionVector& Vector) const
{
    return FString::Printf(TEXT("%s_%d_%.2f_%.2f_%.2f_%.2f_%.2f_%.2f"), *NpcName, (int32)Situation,
        Vector.Joy, Vector.Anger, Vector.Sadness, Vector.Surprise, Vector.Fear, Vector.Disgust);
}

FReactionOutput UReactionSimulatorWidget::QueryLocalDb(const FString& Hash) const
{
    if (const FReactionOutput* Found = LocalDb.Find(Hash))
    {
        return *Found;
    }
    return FReactionOutput();
}

void UReactionSimulatorWidget::CacheLocal(const FString& Hash, const FReactionOutput& Output)
{
    LocalDb.Add(Hash, Output);
}

