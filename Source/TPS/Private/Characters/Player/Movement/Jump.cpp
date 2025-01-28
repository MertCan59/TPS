// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/Movement/Jump.h"
#include "Characters/Player/TpsPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/Player/PlayerMovementState.h"


UJump::UJump()
{
	if (OwningCharacter && MovementComponent)
	{
		MovementComponent->JumpZVelocity=300.f;
		MovementComponent->AirControl=0.1f;
	}
}

void UJump::BeginPlay()
{
	Super::BeginPlay();
}

void UJump::Jump(const FInputActionValue& Value)
{
	const auto JumpDirection = FVector(0.f, 0.f, 1.f);
	
	if (OwningCharacter && MovementComponent)
	{
		if (!MovementComponent->IsFalling() && OwningCharacter->GetCharacterGrounded())
		{
			OwningCharacter->SetCharacterState(ECharacterState::ECS_JumpingState);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("Entered Jump State"));
			}
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			float SmoothJumpForce = UKismetMathLibrary::Lerp(GetJumpForce(), 0.f, DeltaTime * GetSmoothFactor());
			FVector SmoothLaunchVelocity = JumpDirection * SmoothJumpForce;
			OwningCharacter->LaunchCharacter(SmoothLaunchVelocity, false, true);
		}
		if (MovementComponent->IsFalling() && OwningCharacter->GetCharacterGrounded())
		{
			OwningCharacter->SetCharacterState(ECharacterState::ECS_GravityState);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("Entered Gravity State"));
			}
		}
	}
}

void UJump::StopJump(const FInputActionValue& Value)
{
	
}
