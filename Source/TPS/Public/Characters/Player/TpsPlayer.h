// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS/Public/Controller/PlayerDefaultController.h"

#include "TpsPlayer.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UMovement;

struct FInputActionValue;

UCLASS()
class TPS_API ATpsPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform)override;
	virtual void PostInitProperties() override;
	
	void Move(const FInputActionValue& Value);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

//For Components
private:
	UPROPERTY(VisibleAnywhere,Category="Components")
	USceneComponent* PlayerRootComponent;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UCapsuleComponent* PlayerCapsule;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UMovement* MovementController;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	UCameraComponent* ViewCamera;
	
	UPROPERTY(EditAnywhere,Category="Input Controller")
	APlayerDefaultController* PlayerDefaultController;

	
	
	//For polishing variables such as length, height
private:
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraHeight;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraYOffset ;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float TargetArmLength;

};
