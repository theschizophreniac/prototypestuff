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

FVector UBP_CPP::Gravity(AActor* Actor, AActor* ASelf)
{
    const float G = 1.f;
    UPrimitiveComponent* Root1 = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
    UPrimitiveComponent* Root2 = Cast<UPrimitiveComponent>(ASelf->GetRootComponent());

    if (!Root1 || !Root2) return FVector::ZeroVector;
    if (!Root1->IsSimulatingPhysics() || !Root2->IsSimulatingPhysics()) return FVector::ZeroVector;

    float Mass1 = Root1->GetMass();
    float Mass2 = Root2->GetMass();

    FVector Delta = (ASelf->GetActorLocation() - Actor->GetActorLocation());
    FVector Direction = Delta.GetSafeNormal();

    // Convert to meters
    float DistanceSq = (Delta.Size() / 100.f) * (Delta.Size() / 100.f);

    if (DistanceSq <= KINDA_SMALL_NUMBER) return FVector::ZeroVector;

    /* 
        m1 * m2 / r^2 * g = einstein i thinK? idk...
        its almost midnight i dont get paid enough!!!!!
    */
    float ForceMagnitude = (G * Mass1 * Mass2) / DistanceSq;

    return Direction * ForceMagnitude;
}


