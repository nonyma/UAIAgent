#pragma once

#include "CoreMinimal.h"
#include "ReactionTypes.generated.h"

UENUM(BlueprintType)
enum class ESituationCode : uint8
{
    S1 UMETA(DisplayName = "S1"),
    S2 UMETA(DisplayName = "S2"),
    S3 UMETA(DisplayName = "S3"),
    S4 UMETA(DisplayName = "S4"),
    S5 UMETA(DisplayName = "S5"),
    S6 UMETA(DisplayName = "S6")
};

USTRUCT(BlueprintType)
struct FEmotionVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Joy = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Anger = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Sadness = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Surprise = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Fear = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Disgust = 0.f;
};


USTRUCT(BlueprintType)
struct FReactionOutput
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ReactionDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Dialogue;
};

