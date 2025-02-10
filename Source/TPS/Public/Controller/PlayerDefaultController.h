// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerDefaultController.generated.h"

/**
 * This class will be used for defining the inputs. Add input variables and their Get...() functions after that move to the TpsPlayer->SetupPlayerInputComponent
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class TPS_API APlayerDefaultController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerDefaultController();
	FORCEINLINE UInputAction* GetMovementAction()const{return MovementAction;}
	FORCEINLINE UInputAction* GetLookAction()const{return LookAction;}
	FORCEINLINE UInputAction* GetAimAction() const{return AimAction;}
	FORCEINLINE UInputAction* GetJumpAction()const{return JumpAction;}
	FORCEINLINE UInputAction* GetRunningAction()const{return RunningAction;}

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* PlayerInputContext;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* AimAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* RunningAction;
	
};
