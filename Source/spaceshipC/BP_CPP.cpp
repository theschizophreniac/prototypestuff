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

FDualVector UBP_CPP::Gravity(UPrimitiveComponent *OtherBody, UPrimitiveComponent *SelfBody)
{
    FDualVector Result;
    //not sure how to expose a variable
    //in a blueprint function, this ought to do methinks?
    const float G = 1.f;
    const float RotationPower = 10000.f;

    if (!OtherBody || !SelfBody) return FDualVector();
    if (!OtherBody->IsSimulatingPhysics() || !SelfBody->IsSimulatingPhysics()) return FDualVector();

    const float Mass1 = OtherBody->GetMass();
    const float Mass2 = SelfBody->GetMass();

    FVector Delta = (SelfBody->GetComponentLocation() - OtherBody->GetComponentLocation());
    FVector Direction = Delta.GetSafeNormal();

    // Convert to meters
    float DistanceSq = (Delta.Size() / 100.f) * (Delta.Size() / 100.f);

    if (DistanceSq <= KINDA_SMALL_NUMBER) return FDualVector();

    /* 
        m1 * m2 / r^2 * g = einstein i thinK? idk...
        its almost midnight i dont get paid enough!!!!!
    */
    float ForceMagnitude = (G * Mass1 * Mass2) / DistanceSq;

    Result.Gravity = Direction * ForceMagnitude;

    // this is the curve of objects

    FVector Forward = OtherBody->GetForwardVector();
    FVector Desired = Forward ^ Direction;

    float rotatePower = FVector::DotProduct(Forward, Desired);

    Result.Torque = (RotationPower * Desired) / DistanceSq;
    return Result;
}
