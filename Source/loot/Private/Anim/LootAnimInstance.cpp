// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/LootAnimInstance.h"
#include "Character/LootPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void ULootAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	LootCharacter = Cast<ALootPlayerCharacter>(TryGetPawnOwner());
}

void ULootAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!LootCharacter.IsValid())
	{
		return;
	}

	// 获取移动组件
	if (const UCharacterMovementComponent* Movement = LootCharacter->GetCharacterMovement())
	{
		// 地面速度（忽略 Z 轴）
		const FVector Velocity = Movement->Velocity;
		GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

		// 更新状态（直接从角色获取）
		Gait = LootCharacter->GetMovementState();
		Stance = LootCharacter->GetStance();

		// 鼠标输入（如果角色有这些变量）
		LookYaw = LootCharacter->MouseRight;
		LookPitch = LootCharacter->MouseUp;
	}
	// if (!lootCharacter)
	// {
	// 	lootCharacter = Cast<ALootPlayerCharacter>(TryGetPawnOwner());
	// 	if (!lootCharacter)
	// 	{
	// 		GroundSpeed = 0.f;
	// 		Gait = EMovementState::Walk;
	// 		return;
	// 	}
	// 	
	// 	LookYaw = lootCharacter->MouseRight;
	// 	LookPitch = lootCharacter->MouseUp;
	// }
	//
	//
	// //更新移动速度与状态
	// if (UCharacterMovementComponent* Movement = lootCharacter->GetCharacterMovement())
	// {
	// 	FVector Velocity = Movement->Velocity;
	// 	Velocity.Z = 0.f;//忽略垂直速度
	// 	GroundSpeed = Velocity.Size();
	// 	Gait = lootCharacter->GetMovementState();//更新状态
	// 	Stance = lootCharacter->GetStance();
	// 	// 状态名称  调试
	// 	FString StateName;
	// 	
	// 	switch (Gait) {
	// 	case EMovementState::Sneak:
	// 		bIsSneaking = true;
	// 		StateName = "静步";
	// 		break;
	// 	case EMovementState::Walk:
	// 		break;
	// 	case EMovementState::Sprint:
	// 		bIsSprinting = true;
	// 		StateName = "奔跑";
	// 		break;
	// 	}
	//
	// 	switch (Stance) {
	// 	case EStance::Idle:
	// 		bIsCrouch = false;
	// 		break;
	// 	case EStance::Crouch:
	// 		bIsCrouch = true;
	// 		break;
	// 	}
	// 	
	// 	// GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,FString::Printf(TEXT("状态: %s"),*StateName));
	// 	// GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,FString::Printf(TEXT("速度: %f"),MoveSpeed));
	// }
	
	
}
