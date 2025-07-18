// MyAIController.cpp

#include "MyAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();
    Timer = 0.0f;
    RandomLocation = GetPawn()->GetActorLocation() + FVector(500, 0, 0);
}

void AMyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    Timer += DeltaSeconds;

    if (Timer > 2.0f)
    {
        UpdateMovement();
        UpdateRotation();
        Timer = 0.0f;
    }
}

void AMyAIController::UpdateMovement()
{
    MoveToLocation(RandomLocation);
}

void AMyAIController::UpdateRotation()
{
    APawn* ControlledPawn = GetPawn();
    if (ControlledPawn)
    {
        FRotator NewRotation = CalculateLookAtRotation(
            ControlledPawn->GetActorLocation(),
            RandomLocation
        );
        ControlledPawn->SetActorRotation(NewRotation);
    }
}

FRotator AMyAIController::CalculateLookAtRotation(const FVector& From, const FVector& To)
{
    return UKismetMathLibrary::FindLookAtRotation(From, To);
}
