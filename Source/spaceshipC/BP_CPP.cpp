#include "BP_CPP.h"
#include "Spaceship.h"

FVector UBP_CPP::CalulateDirection(FVector Forward)
{
    auto D2R = (180.f / PI);
    // Horizontal (Yaw) calculation
    FVector ShipForward = Forward;
    ShipForward.Z = 0.f;
    ShipForward.Normalize();
    float YawDegrees = FMath::Atan2(ShipForward.Y, ShipForward.X) * D2R;

    // Vertical (Pitch) calculation
    FVector VerticalForward = Forward;
    VerticalForward.Y = 0.f;
    VerticalForward.Normalize();
    float PitchDegrees = FMath::Atan2(VerticalForward.Z, VerticalForward.X) * D2R;

    UE_LOG(LogTemp, Warning, TEXT("Yaw: %f, Pitch: %f"), YawDegrees, PitchDegrees);
    return FVector(YawDegrees, PitchDegrees, 0.f);
}