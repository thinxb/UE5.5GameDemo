#pragma once

#include "LootCharacterEnums.generated.h"

UENUM(BlueprintType)
enum class EGaitState : uint8
{
	Sneak   UMETA(DisplayName = "静步"),
	Walk    UMETA(DisplayName = "步行"),
	Sprint  UMETA(DisplayName = "冲刺")
};

UENUM(BlueprintType)
enum class EMovementAction : uint8
{
	Idle    UMETA(DisplayName = "站立"),
	Crouch   UMETA(DisplayName = "蹲下"),
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	// 枪械
	Pistol,
	Rifle,
	Shotgun,
	SMG,
	Sniper,

	// 近战
	Knife,
	Bat,

	// 投掷
	Grenade,
	Flashbang,
};
