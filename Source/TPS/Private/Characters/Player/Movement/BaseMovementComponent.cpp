// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Characters/Player/Movement/BaseMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPS/Public/Characters/Player/TpsPlayer.h"

// Sets default values for this component's properties
UBaseMovementComponent::UBaseMovementComponent()
{
	OwningCharacter=Cast<ATpsPlayer>(GetOwner());
	if (OwningCharacter)
	{
		OwningCharacter->bUseControllerRotationYaw = false;
		MovementComponent=Cast<UCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
	}
}
void UBaseMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}
