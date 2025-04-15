#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None UMETA(DisplayName = "None"),
	Handgun UMETA(DisplayName = "Handgun"),
	AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	Shotgun UMETA(DisplayName = "Shotgun"),
	Flashlight UMETA(DisplayName = "Flashlight")
};
