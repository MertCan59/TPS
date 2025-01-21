// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Characters/Player/Movement/Movement.h"

void UMovement::Move(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,1.5f,FColor::Yellow,"Movement Actor component is working smoothly");
	}
}
