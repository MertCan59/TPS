// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMovementComponent.h"
#include "TPS/public/Characters/Player/PlayerMovementState.h"
#include "Movement.generated.h"

/**
 * This class will be used for player's movement actions and its own variables such as speed,acceleration and deceleration
 */
UCLASS()
class TPS_API UMovement : public UBaseMovementComponent
{
	GENERATED_BODY()

//TODO:Main Functions such as Move(),Look() 
public:
	UMovement();
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void SprintStart(const FInputActionValue& Value);
	void SprintStop(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	
//TODO:For Getter and Setter Functions
public:
	//**GET SPEED FUNCTIONS **//
	float GetMaxSpeed() const{return MaxSpeed;}
	float GetCurrentSpeed() const{return CurrentSpeed;}
	float GetCachedSpeed() const{return CachedSpeed;}
	float GetMaxAcceleration() const{return MaxAcceleration;}
	float GetMaxDeceleration() const{return MaxDeceleration;}
	FVector2D GetCurrentVelocity() const{return  CachedInput;}
	//**SET SPEED FUNCTIONS **//
	void SetCurrentSpeed(float NewSpeed) {CurrentSpeed=NewSpeed;}
	
	//**GET LOOK FUNCTIONS **//
	float GetCameraSpeed() const{return CameraSpeed;}
	
private:

	//** MOVEMENT VARIABLES **//
	UPROPERTY(EditDefaultsOnly,Category="Movement Properties", meta=(AllowPrivateAccess=true))
	float MaxSpeed=400.f;

	UPROPERTY(EditDefaultsOnly,Category="Movement Properties", meta=(AllowPrivateAccess=true))
	float CurrentSpeed=100.f;

	UPROPERTY(EditDefaultsOnly,Category="Movement Properties", meta=(AllowPrivateAccess=true))
	float MaxAcceleration=50.f;

	UPROPERTY(EditDefaultsOnly,Category="Movement Properties", meta=(AllowPrivateAccess=true))
	float MaxDeceleration=50.f;
	
	UPROPERTY(EditDefaultsOnly,Category="Movement Properties", meta=(AllowPrivateAccess=true))
	float SprintModifier=1.f;

	FVector2D CachedInput;
	
	float CachedSpeed;
	//** LOOK VARIABLES **//
	UPROPERTY(EditDefaultsOnly,Category="Look Properties", meta=(AllowPrivateAccess=true))
	float CameraSpeed=FMath::Clamp(CameraSpeed, 10.0f, 100.0f);
	
//For private funcs
private:
	bool CanMove()const;
	bool IsYawRestricted()const;
};
