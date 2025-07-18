// MyAIController.h

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class UAIAgent_API AMyAIController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    void MoveToTarget();
    void LookAround();

    FVector RandomLocation;
    float Timer;
};
