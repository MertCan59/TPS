// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/Movement/BaseMovementComponent.h"
#include "TPS/public/Characters/Player/PlayerMovementState.h"
#include "Jump.generated.h"

/**
 * This class will be used for player's jump actions and its own variables such as jump height, jump force
 */
UCLASS()
class TPS_API UJump : public UBaseMovementComponent
{
	GENERATED_BODY()
	
//TODO:Main Functions such as Jump
public:
	UJump();
	virtual void BeginPlay() override;
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

	
//TODO:For Getter and Setter Functions
public:

	float GetMaxJumpHeight()const {return MaxJumpHeight;}
	float GetJumpForce()const {return JumpForce;}

//TODO:For general variables
private:

	//** JUMP VARIABLES **//
	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	float MaxJumpHeight;

	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	float JumpForce;


	float SmoothFactor=2.0f;
};
