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
    /** Move the controlled pawn toward the random location. */
    void UpdateMovement();

    /** Rotate the pawn to face the random location. */
    void UpdateRotation();

    /** Helper used to calculate a look-at rotation. Extracted for easier testing. */
    static FRotator CalculateLookAtRotation(const FVector& From, const FVector& To);

    FVector RandomLocation;
    float Timer;
};
