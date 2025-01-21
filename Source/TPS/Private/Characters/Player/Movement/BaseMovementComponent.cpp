// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS/Public/Characters/Player/Movement/BaseMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPS/Public/Characters/Player/TpsPlayer.h"

// Sets default values for this component's properties
UBaseMovementComponent::UBaseMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	OwningCharacter=Cast<ATpsPlayer>(GetOwner());
	if (OwningCharacter)
	{
		MovementComponent=Cast<UCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
	}
}

void UBaseMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwningCharacter)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Base Movement owning character starts acting");
		}
	}
	if (MovementComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Base Movement movement component starts acting");
		}
	}
}

