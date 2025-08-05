#pragma once

#include "CoreMinimal.h"
#include "AINPC.h"
#include "AMafiaNPC.generated.h"

UCLASS(Blueprintable)
class AMafiaNPC : public AINPC
{
    GENERATED_BODY()
public:
    AMafiaNPC();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mafia")
    FString MyRole;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mafia")
    TMap<TWeakObjectPtr<AINPC>, FString> PredictedRoleMap;
    UFUNCTION(BlueprintCallable, Category = "Mafia")
    virtual AINPC* PickBluffTarget();
    UFUNCTION(BlueprintCallable, Category = "Mafia")
    virtual void PerformBluff(AINPC* TargetNPC);
    virtual EReactionType DecideReaction(const FString& SituationTag, AINPC* SourceNPC) override;
};
