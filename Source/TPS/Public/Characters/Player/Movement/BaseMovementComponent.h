// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMovementComponent.generated.h"

class UCharacterMovementComponent;
class ATpsPlayer;
struct FInputActionValue;


UCLASS( ClassGroup=(Custom),Abstract)
class TPS_API UBaseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseMovementComponent();
	virtual void BeginPlay() override;
protected:
	UCharacterMovementComponent* MovementComponent;
	ATpsPlayer* OwningCharacter;
		
};
