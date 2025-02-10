// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Characters/Player/Movement/Movement.h"
#include "InputActionValue.h"
#include "Characters/Player/TpsPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMovement::UMovement()
{
	if (OwningCharacter && MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = false;
		MovementComponent->RotationRate = FRotator(0.f, 400.f, 0.f);
	}
}

void UMovement::BeginPlay()
{
	Super::BeginPlay();
	CachedSpeed=CurrentSpeed;
	CachedArmSpringRotation=OwningCharacter->GetArmSpring()->GetRelativeRotation();
	CachedPawnRotation=OwningCharacter->GetController()->GetControlRotation();
	if (auto MovementDerived=Cast<UMovement>(this))
	{
		MovementComponent->MaxAcceleration=MovementDerived->GetMaxAcceleration();
		MovementComponent->BrakingDecelerationWalking=MovementDerived->GetMaxDeceleration();
	}
}

void UMovement::Move(const FInputActionValue& Value)
{
	if (!CanMove())return;
	
	const auto MovementInput=Value.Get<FVector2D>();
	CachedInput=MovementInput;
	
	if (OwningCharacter)
	{
		const auto ControlRotation=OwningCharacter->GetControlRotation();
		const FRotator YawRotation(0.f,ControlRotation.Yaw,0.f);
		const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		FVector MoveDirection = (ForwardDirection * MovementInput.Y) + (RightDirection * MovementInput.X);
		MoveDirection.Normalize();

		if (MovementComponent && MovementInput.X!=0)
		{
			OwningCharacter->AddMovementInput(RightDirection,MovementInput.X);
		}
		
		if (MovementComponent && MovementInput.Y!=0)
		{
			OwningCharacter->AddMovementInput(ForwardDirection, MovementInput.Y);
		}
		
	}
	if (auto MovementDerived=Cast<UMovement>(this))
	{
		MovementComponent->MaxWalkSpeed=MovementDerived->GetCurrentSpeed();
	}
}

void UMovement::Look(const FInputActionValue& Value)
{
	const auto LookAxis = Value.Get<FVector2D>();
	
	if (OwningCharacter->GetCharacterState()==ECharacterState::ECS_JumpingState)return;
	if (OwningCharacter && OwningCharacter->Controller)
	{
		
		if (OwningCharacter->GetCharacterState()!=ECharacterState::ECS_MovementState)
		{
			
			//TODO:
			OwningCharacter->GetArmSpring()->bUsePawnControlRotation=false;
			FRotator Current = OwningCharacter->GetArmSpring()->GetRelativeRotation();
			FRotator TargetRotation=Current;
			
			if (LookAxis.X!=0 && !IsYawRestricted())
			{
				TargetRotation.Yaw = FMath::Clamp(TargetRotation.Yaw + LookAxis.X, -50.0f, 50.0f);;
				YawAimOffset =FMath::Clamp(YawAimOffset + LookAxis.X, -101.0f, 101.0f);

			}
			if (LookAxis.Y != 0 )
			{
				TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch + LookAxis.Y, -50.0f, 50.0f);
				PitchAimOffset=FMath::Clamp(PitchAimOffset + LookAxis.Y, -101.0f, 101.0f);
			}
			FRotator SmoothRotation=UKismetMathLibrary::RInterpTo(
				Current,
				TargetRotation,
				GetWorld()->GetDeltaSeconds(),
				GetCameraSpeed()
				);
			OwningCharacter->GetArmSpring()->SetRelativeRotation(SmoothRotation);
		}else
		{
			YawAimOffset=0.f;
			PitchAimOffset=0.f;
			FRotator SmoothArmSpringRotation=UKismetMathLibrary::RInterpTo(
				OwningCharacter->GetArmSpring()->GetRelativeRotation(),
				CachedArmSpringRotation,
				GetWorld()->GetDeltaSeconds(),
				GetCameraSpeed()
				);
			OwningCharacter->GetArmSpring()->SetRelativeRotation(SmoothArmSpringRotation);
			OwningCharacter->GetArmSpring()->bUsePawnControlRotation=true;
			FRotator CurrentRotation = OwningCharacter->Controller->GetControlRotation();
			FRotator TargetRotation = CurrentRotation;
			if (LookAxis.X != 0 && !IsYawRestricted())
			{
				TargetRotation.Yaw += LookAxis.X;
			}
			if (LookAxis.Y != 0 )
			{
				TargetRotation.Pitch = FMath::Clamp(TargetRotation.Pitch + LookAxis.Y, -89.0f, 89.0f);
			}
			FRotator SmoothedRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), GetCameraSpeed());
			OwningCharacter->GetController()->SetControlRotation(SmoothedRotation);
		}
	}
}

void UMovement::SprintStart(const FInputActionValue& Value)
{
	OwningCharacter->SetCharacterSprinting(true);
	SetCurrentSpeed(GetCachedSpeed() * SprintModifier);
}

void UMovement::SprintStop(const FInputActionValue& Value)
{
	OwningCharacter->SetCharacterSprinting(false);
	SetCurrentSpeed(GetCachedSpeed());
}

bool UMovement::CanMove() const
{
	return OwningCharacter->GetCharacterState()==ECharacterState::ECS_Idle || OwningCharacter->GetCharacterState()==ECharacterState::ECS_MovementState;
}

bool UMovement::IsYawRestricted() const
{
	return OwningCharacter->GetCharacterState()==ECharacterState::ECS_GravityState || OwningCharacter->GetCharacterState()==ECharacterState::ECS_JumpingState;
}
