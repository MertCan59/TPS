// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/Movement/BaseMovementComponent.h"
#include "TPS/public/Characters/Player/PlayerMovementState.h"
#include "Characters/Player/PlayerMovementState.h"
#include "Jump.generated.h"

/**
 * This class will be used for player's jump actions and its own variables such as jump height, jump force
 */

class UAnimMontage;
UCLASS()
class TPS_API UJump : public UBaseMovementComponent
{
	GENERATED_BODY()
	
//TODO:Main Functions such as Jump
public:
	UJump();
	virtual void BeginPlay() override;
	
	void PlayMontage();
	void StopJump(const FInputActionValue& Value);
	void SetCanJump(bool CanJump){bCanJump=CanJump;}
	
//TODO:For Getter and Setter Functions
public:
	float GetMaxJumpHeight()const {return MaxJumpHeight;}
	float GetJumpForce()const {return JumpForce;}
	float GetSmoothFactor()const {return SmoothFactor;}

	bool GetCanJump()const{return bCanJump;}
	bool GetIsJumping()const {return bIsJumping;}

	//** BLUEPRINT CALLABLE FUNCTIONS **//
	UFUNCTION(BlueprintCallable)
	void ApplyJump();

	UFUNCTION(BlueprintCallable)
	void ChangeState();

protected:
	
	
//TODO: For private funcs	
private:

//TODO:For general variables
private:
	
	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	UAnimMontage* JumpMontage;
	
	//** JUMP VARIABLES **//
	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	float MaxJumpHeight;

	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	float JumpForce;

	UPROPERTY(EditDefaultsOnly,Category="Jump Properties", meta=(AllowPrivateAccess=true))
	float SmoothFactor=2.0f;

	bool bCanJump;
	bool bIsJumping;
};
