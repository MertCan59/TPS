#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle State"), 
	ECS_MovementState UMETA(DisplayName = "Movement State"), 
	ECS_JumpingState UMETA(DisplayName = "Jumping State"),
	ECS_GravityState UMETA(DisplayName = "Gravity State")
};
