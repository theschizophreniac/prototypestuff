#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_CPP.generated.h"

class ABP_Spaceship;

UCLASS()
class SPACESHIPC_API UBP_CPP : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Spaceship")
    static FVector CalulateDirection(FVector Forward);
};
