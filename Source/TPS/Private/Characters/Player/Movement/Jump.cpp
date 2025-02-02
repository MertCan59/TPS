// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/Movement/Jump.h"
#include "Characters/Player/TpsPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

void UJump::ApplyJump()
{
	const auto JumpDirection = FVector(0.f, 0.f, 1.f);
	if (OwningCharacter && MovementComponent)
	{
		FVector CurrentVelocity = MovementComponent->Velocity;
		CurrentVelocity.X = 0.f; 
		CurrentVelocity.Y = 0.f; 
		MovementComponent->Velocity = CurrentVelocity; 
		if (!MovementComponent->IsFalling() && OwningCharacter->GetCharacterGrounded())
		{
			float DeltaTime = GetWorld()->GetDeltaSeconds();
			float SmoothJumpForce = UKismetMathLibrary::Lerp(GetJumpForce(), 0.f, DeltaTime * GetSmoothFactor());
			FVector SmoothLaunchVelocity = JumpDirection * SmoothJumpForce;
			OwningCharacter->LaunchCharacter(SmoothLaunchVelocity, false, true);
		}
	}
}

void UJump::ChangeState()
{
	OwningCharacter->SetCharacterState(ECharacterState::ECS_JumpingState);
}

void UJump::PlayMontage()
{
	UAnimInstance* AnimInstance=OwningCharacter->GetMesh()->GetAnimInstance();
	if (AnimInstance && JumpMontage)
	{
		AnimInstance->Montage_Play(JumpMontage);
		AnimInstance->Montage_JumpToSection(FName("Jump"),JumpMontage);
	}
}

void UJump::StopJump(const FInputActionValue& Value)
{
	//TODO:
}
