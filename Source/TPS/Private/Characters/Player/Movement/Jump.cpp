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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Jump class working on");
	}
}

void UJump::Jump(const FInputActionValue& Value)
{
	const auto JumpDirection = FVector(0.f, 0.f, 1.f);
	
	if (OwningCharacter && MovementComponent )
	{
		if (!MovementComponent->IsFalling())
		{
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			float SmoothJumpForce = FMath::Lerp(GetJumpForce(), 0.f, DeltaTime * SmoothFactor);
			FVector SmoothLaunchVelocity = JumpDirection * SmoothJumpForce;
			OwningCharacter->LaunchCharacter(SmoothLaunchVelocity, false, true);
		}
	}
}
void UJump::StopJumping(const FInputActionValue& Value)
{
	if (MovementComponent->IsFalling())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, .75f, FColor::Red, "Jump is canceled");
		}
	}
}
