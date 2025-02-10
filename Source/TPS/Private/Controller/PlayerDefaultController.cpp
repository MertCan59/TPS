// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Controller/PlayerDefaultController.h"
#include "EnhancedInputSubsystems.h"


APlayerDefaultController::APlayerDefaultController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerDefaultController::BeginPlay()
{
	Super::BeginPlay();
	if (this)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputContext,0);
		}
	}
}
