// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TpsPlayer.generated.h"

class UCapsuleComponent;
class USceneComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TPS_API ATpsPlayer : public APawn
{
	GENERATED_BODY()

public:
	ATpsPlayer();
	virtual void OnConstruction(const FTransform& Transform)override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

public:

//For Components
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PlayerRootComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* PlayerSkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* PlayerCapsuleCollider;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	
//For polishing variables such as length, height
private:
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraHeight;

	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float TargetArmLength;
};
	