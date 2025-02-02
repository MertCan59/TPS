// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMovementState.h"
#include "GameFramework/Character.h"
#include "TPS/Public/Controller/PlayerDefaultController.h"

#include "TpsPlayer.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UMovement;
class UJump;

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
	
// Set external variables for accessing from other classes 
public:
	
	//** PLAYER STATE  **//
	FORCEINLINE ECharacterState GetCharacterState() const{return CharacterState;}
	FORCEINLINE void SetCharacterState(ECharacterState NewState){CharacterState=NewState;}
	FORCEINLINE void SetCharacterSprinting(bool Sprint){bIsSprint=Sprint;}

	//** PLAYER GROUND CONTROLLER  **/
	FORCEINLINE bool GetCharacterGrounded() const{return bIsGrounded;}
	FORCEINLINE bool GetCharacterSprint() const{return bIsSprint;}
	FORCEINLINE USpringArmComponent* GetArmSpring() const{return CameraBoom;}
	FORCEINLINE UJump* GetJump()const {return JumpController;}
	
	//** PLAYER Jog CONTROLLER  **/
	UMovement* GetMovement() const{return MovementController;}
	
protected:
	ECharacterState CharacterState=ECharacterState::ECS_Idle;
	virtual void BeginPlay() override;
	
//For Components
private:
	UPROPERTY(VisibleAnywhere,Category="Components")
	USceneComponent* PlayerRootComponent;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UCapsuleComponent* PlayerCapsule;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UMovement* MovementController;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UJump* JumpController;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	UCameraComponent* ViewCamera;
	
//For polishing variables such as length, height
private:
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraHeight;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraYOffset ;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float TargetArmLength;
	
	bool bIsGrounded;
	bool bIsSprint;

//For private funcs	
private:
};