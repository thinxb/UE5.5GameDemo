// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LootCharacterEnums/LootCharacterEnums.h"
#include "LootAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOOT_API ULootAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaTime);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float Speed;//速度
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	EGaitState GaitState = EGaitState::Walk;//状态记录
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bIsSneaking  = false;//是否静步
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bIsSprinting = false;//是否冲刺
	
	
private:
	//角色指针
	UPROPERTY()
	class ALootPlayerCharacter* lootCharacter = nullptr;
};
