#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle State"), 
	ECS_MovementState UMETA(DisplayName = "Movement State"), 
	ECS_JumpingState UMETA(DisplayName = "Jumping State"),
	ECS_GravityState UMETA(DisplayName = "Gravity State")
};
UENUM(BlueprintType)
enum class ECharacterIdleState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped State"), 
	ECS_OneHanded UMETA(DisplayName = "One Handed State"), 
	ECS_TwoHanded UMETA(DisplayName = "Two Handed State"), 
};
UENUM(BlueprintType)
enum class ECharacterMoveState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped State"),
	ECS_OneHanded UMETA(DisplayName = "One Handed State"), 
	ECS_TwoHanded UMETA(DisplayName = "Two Handed State"), 
};
