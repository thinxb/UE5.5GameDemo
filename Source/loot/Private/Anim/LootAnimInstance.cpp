// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/LootAnimInstance.h"
#include "Character/LootPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void ULootAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (!lootCharacter)
	{
		lootCharacter = Cast<ALootPlayerCharacter>(TryGetPawnOwner());
		if (!lootCharacter)
		{
			MoveSpeed = 0.f;
			GaitState = EGaitState::Walk;
			return;
		}
		
		Right = lootCharacter->MouseRight;
		UP = lootCharacter->MouseUp;
	}
	

	//更新移动速度与状态
	if (UCharacterMovementComponent* Movecomt = lootCharacter->GetCharacterMovement())
	{
		FVector Velocity = Movecomt->Velocity;
		Velocity.Z = 0.f;//忽略垂直速度
		MoveSpeed = Velocity.Size();
		GaitState = lootCharacter->GetGaitState();//更新状态
		// 状态名称  调试
		FString StateName;
		
		switch (GaitState) {
		case EGaitState::Sneak:
			bIsSneaking = true;
			StateName = "静步";
			break;
		case EGaitState::Walk:
			break;
		case EGaitState::Sprint:
			bIsSprinting = true;
			StateName = "奔跑";
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,FString::Printf(TEXT("状态: %s"),*StateName));
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,FString::Printf(TEXT("速度: %f"),MoveSpeed));
	}
}
