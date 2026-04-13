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
	void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float GroundSpeed;//地面速度
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float LookYaw;//鼠标横向
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float LookPitch;//鼠标纵向
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	EMovementState Gait = EMovementState::Walk;//移动状态
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	EStance Stance = EStance::Idle;//姿态
	
	
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Character")
	// bool bIsSneaking  = false;//是否静步
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Character")
	// bool bIsSprinting = false;//是否冲刺
	//
	// UPROPERTY(BlueprintReadOnly, Category = "Character")
	// bool bIsCrouch = false;//是否蹲下
	
	
private:
	//角色指针
	// UPROPERTY()
	// class ALootPlayerCharacter* lootCharacter = nullptr;
	UPROPERTY()
	TWeakObjectPtr<class ALootPlayerCharacter> LootCharacter;
};
