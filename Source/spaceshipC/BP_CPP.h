#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_CPP.generated.h"

class ABP_Spaceship;

USTRUCT(BlueprintType)
struct FDualVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Gravity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Torque;

    FDualVector()
    : Gravity(FVector::ZeroVector), Torque(FVector::ZeroVector) {}
};


UCLASS()
class SPACESHIPC_API UBP_CPP : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Spaceship")
    static FVector CalulateDirection(FVector Forward);

    UFUNCTION(BlueprintCallable, Category="Spaceship")
    static FDualVector Gravity(UPrimitiveComponent* OtherBody, UPrimitiveComponent* SelfBody);
};
