#pragma once

#include "CoreMinimal.h"
#include "NPCEnums.generated.h"

UENUM(BlueprintType)
enum class EEmotionType : uint8
{
    Neutral      UMETA(DisplayName = "Neutral"),
    Happy        UMETA(DisplayName = "Happy"),
    Sad          UMETA(DisplayName = "Sad"),
    Angry        UMETA(DisplayName = "Angry"),
    Fear         UMETA(DisplayName = "Fear"),
    Surprise     UMETA(DisplayName = "Surprise"),
    Disgust      UMETA(DisplayName = "Disgust")
};

UENUM(BlueprintType)
enum class EReactionType : uint8
{
    None        UMETA(DisplayName = "None"),
    Speak       UMETA(DisplayName = "Speak"),
    Gesture     UMETA(DisplayName = "Gesture"),
    Vote        UMETA(DisplayName = "Vote"),
    Bluff       UMETA(DisplayName = "Bluff"),
    Accuse      UMETA(DisplayName = "Accuse"),
    Defend      UMETA(DisplayName = "Defend")
};

USTRUCT(BlueprintType)
struct FRelationshipData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Affinity = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Trust = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> InteractionHistory;
};
// ...NPCEnums.h 원본 코드...
