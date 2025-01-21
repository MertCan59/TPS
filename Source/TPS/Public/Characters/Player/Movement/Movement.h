// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMovementComponent.h"
#include "Movement.generated.h"

/**
 * This class will be used for player's movement actions and its own variables such as speed,acceleration and deceleration
 */
UCLASS()
class TPS_API UMovement : public UBaseMovementComponent
{
	GENERATED_BODY()

public:
	void Move(const FInputActionValue& Value);
	
};
