// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"


#include "Spaceship.generated.h"

UCLASS()
class SPACESHIPC_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	ASpaceship();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPhysicsThrusterComponent> Thruster;


protected:
	virtual void BeginPlay() override;

	void TakeOff(float Value);

	void MoveUp(float Value);

	void MoveSide(float Value);

	void SetCentre();

	void Roll(float Value);

	void MoveForward(float Value);

	void LBPress();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RotateTorque = 400.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TiltTorque = 100.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float LiftStrength = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MaxThrust = 10000.f;

	UPROPERTY(BlueprintReadOnly)
	FVector ForwardVelocity;

	UPROPERTY(BlueprintReadOnly)
	float Thrust;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: 
};
