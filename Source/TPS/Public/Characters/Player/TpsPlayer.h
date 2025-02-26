// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMovementState.h"
#include "GameFramework/Character.h"
#include "Interface/Damageable.h"
#include "TPS/Public/Controller/PlayerDefaultController.h"
#include "TpsPlayer.generated.h"

class AHandgun;
class UPlayerAnimInstance;
class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UMovement;
class UJump;

class AWeaponBase;

UCLASS()
class TPS_API ATpsPlayer : public ACharacter,public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default functions for this character's properties
	ATpsPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnConstruction(const FTransform& Transform)override;
	virtual void PostInitProperties() override;
	
// Set external variables for accessing from other classes 
public:
	
	//** PLAYER STATE  **//
	FORCEINLINE ECharacterState GetCharacterState() const{return CharacterState;}
	FORCEINLINE ECharacterIdleState GetCharacterIdleState() const{return CharacterIdleState;}
	FORCEINLINE void SetCharacterState(ECharacterState NewState){CharacterState=NewState;}
	FORCEINLINE void SetCharacterSprinting(bool Sprint){bIsSprint=Sprint;}

	//** PLAYER GROUND CONTROLLER  **/
	FORCEINLINE bool GetCharacterGrounded() const{return bIsGrounded;}
	FORCEINLINE bool GetCharacterSprint() const{return bIsSprint;}
	FORCEINLINE bool GetHasWeapon() const{return bHasWeapon;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AWeaponBase* GetWeaponBase()const{return EquippedWeapon;}
	
	FORCEINLINE USpringArmComponent* GetArmSpring() const{return CameraBoom;}
	FORCEINLINE UCameraComponent* GetViewCamera() const{return ViewCamera;}
	
	FORCEINLINE UJump* GetJump()const {return JumpController;}
	FORCEINLINE UCapsuleComponent* GetPlayerCapsule()const {return PlayerCapsule;}
	
	//** PLAYER Jog CONTROLLER  **/
	UMovement* GetMovement() const{return MovementController;}

	void ReceiveDamage_Implementation() override;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);
	ECharacterState CharacterState=ECharacterState::ECS_Idle;
	ECharacterIdleState CharacterIdleState=ECharacterIdleState::ECS_Unequipped;
	
			//** For Components **//
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
	
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	AWeaponBase* EquippedWeapon;

	UPROPERTY(VisibleAnywhere,Category="Weapon | Attached Weapons")
	TArray<AWeaponBase*> EquippedWeapons;
	
//For polishing variables such as length, height
private:
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraHeight;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float CameraYOffset ;
	
	UPROPERTY(EditAnywhere,Category="Camera Properties")
	float TargetArmLength;

	//** GENERAL CONTROLLERS **//
	bool bIsGrounded;
	bool bIsSprint;
	bool bHasWeapon=false;
	bool bLeftHandIsFull;

//For private funcs	
private:
	void UpdateWeaponInputBinding();
	void UpdateInterval();
};