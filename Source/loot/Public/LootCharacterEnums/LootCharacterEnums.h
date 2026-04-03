#pragma once

#include "LootCharacterEnums.generated.h"

UENUM(BlueprintType)
enum class EGaitState : uint8
{
	Sneak   UMETA(DisplayName = "静步"),
	Walk    UMETA(DisplayName = "步行"),
	Sprint  UMETA(DisplayName = "冲刺")
};

// 未来可增加更多状态枚举
UENUM(BlueprintType)
enum class EMovementAction : uint8
{
	Crouch   UMETA(DisplayName = "蹲下"),
	Prone    UMETA(DisplayName = "匍匐")
};