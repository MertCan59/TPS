#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle State"), 
	ECS_MovementState UMETA(DisplayName = "Movement State"), 
	ECS_RunningState UMETA(DisplayName = "Running State"), 
	ECS_JumpingState UMETA(DisplayName = "Jumping State"),
	ECS_GravityState UMETA(DisplayName = "Gravity State")
};
UENUM(BlueprintType)
enum class ECharacterIdleState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped Idle State"), 
	ECS_OneHandedEquipped UMETA(DisplayName = "Equipped  One Hand State"),
	ECS_TwoHandedEquipped UMETA(DisplayName = "Equipped  Two Hand State")
	
};
UENUM(BlueprintType)
enum class ECharacterMoveState : uint8
{
	ECS_Jog UMETA(DisplayName = " Jogging State"),
	ECS_Run UMETA(DisplayName = "Running State"), 
};

UENUM(BlueprintType)
enum class ECharacterCurrentMoveState : uint8
{
	ECS_Forward UMETA(DisplayName = "Forward State"),
	ECS_ForwardLeft UMETA(DisplayName = "Forward Left State"),
	ECS_ForwardRight UMETA(DisplayName = "Forward Right"),
	
	ECS_Backward UMETA(DisplayName = "Backward State"),
	ECS_BackwardLeft UMETA(DisplayName = "Backward Left State"),
	ECS_BackwardRight UMETA(DisplayName = "Backward Right"),
	
	ECS_Left UMETA(DisplayName = " Left State"),
	ECS_Right UMETA(DisplayName = "Right State"), 
};

