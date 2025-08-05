#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AMafiaNPC.h"
#include "MafiaTestPreset.generated.h"

UCLASS()
class UMafiaTestPreset : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(CallInEditor, BlueprintCallable, Category="Mafia|Test")
    static void TestFirstDayIntroduction(AMafiaNPC* NPC);
    UFUNCTION(CallInEditor, BlueprintCallable, Category="Mafia|Test")
    static void TestAccusedDefense(AMafiaNPC* NPC, AINPC* Accuser);
    UFUNCTION(CallInEditor, BlueprintCallable, Category="Mafia|Test")
    static void TestMafiaSignal(AMafiaNPC* MafiaNPC, AINPC* Ally);
    UFUNCTION(CallInEditor, BlueprintCallable, Category="Mafia|Test")
    static void TestInnocentRage(AMafiaNPC* VillagerNPC, AINPC* Accuser);
    UFUNCTION(CallInEditor, BlueprintCallable, Category="Mafia|Test")
    static void TestFinalPlea(AMafiaNPC* NPC);
};
