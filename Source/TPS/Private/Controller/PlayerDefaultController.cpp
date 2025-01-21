// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Controller/PlayerDefaultController.h"
#include "EnhancedInputSubsystems.h"


void APlayerDefaultController::BeginPlay()
{
	Super::BeginPlay();
	if (this)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputContext,0);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, "Default Controller has been set");
			}
		}
	}
}
