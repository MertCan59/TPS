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
	PlayerSubsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if (this)
	{
		if (PlayerSubsystem)
		{
			PlayerSubsystem->AddMappingContext(PlayerInputContext,0);
		}
	}
}
