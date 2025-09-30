#include "Spaceship.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	RootComponent = Mesh;

	Thruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Thruster"));
	Thruster -> SetupAttachment(Mesh);
	Thruster -> bAutoActivate = true;
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	SetCentre();
}

void ASpaceship::TakeOff(float Value)
{ 
	if (Thrust < 100.f)
	{
		float Up = Mesh->GetUpVector().Z;
		float Mass = Mesh->GetMass();
		float Force = ((LiftStrength / Up) * Mass) * Value;
		Thruster->ThrustStrength = Force;
	}
	else
	{
		Mesh->SetPhysicsLinearVelocity(ForwardVelocity);
	}
}

void ASpaceship::MoveUp(float Value)
{
	FVector Force = (Mesh->GetForwardVector() * RotateTorque) * Value;
	Mesh->AddTorqueInDegrees(Force, NAME_None, true);
}

void ASpaceship::MoveSide(float Value)
{
	FVector Force = (Mesh->GetUpVector() * RotateTorque) * Value;
	Mesh->AddTorqueInDegrees(Force, NAME_None, true);
}

void ASpaceship::SetCentre()
{
	FVector Offset = Thruster->GetComponentLocation() - Mesh->GetComponentLocation();
	FVector LocalOffset = Mesh->GetComponentRotation().GetInverse().RotateVector(Offset);
	LocalOffset.Z = 0.f;
	Mesh->SetCenterOfMass(LocalOffset);
	Thruster->SetRelativeLocation(LocalOffset);
}

void ASpaceship::Roll(float Value)
{
	FVector Force = (Mesh->GetRightVector() * TiltTorque) * Value;
	Mesh->AddTorqueInDegrees(Force, NAME_None, true);
}

void ASpaceship::MoveForward(float Value)
{
	if (!FMath::IsNearlyEqual(Value, 0.f, 0.1f))
	{
		float DeltaT = GetWorld()->GetDeltaSeconds();

		float Alpha = FMath::Lerp(0.f, MaxThrust, ((Value + 1) / 2));
		Thrust = FMath::FInterpTo(Thrust, Alpha, DeltaT, 1.f);
	}
	ForwardVelocity = Mesh->GetRightVector() * Thrust;
}

void ASpaceship::LBPress()
{
}


void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("TakeOff"), this, &ASpaceship::TakeOff);
	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &ASpaceship::MoveUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASpaceship::MoveSide);
	PlayerInputComponent->BindAxis(FName("RollShip"), this, &ASpaceship::Roll);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASpaceship::MoveForward);
}

