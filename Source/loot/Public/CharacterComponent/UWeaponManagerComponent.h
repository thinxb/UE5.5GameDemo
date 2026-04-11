// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootCharacterEnums/LootCharacterEnums.h"
#include "UWeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOT_API UUWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUWeaponManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
public:
	//当前武器
	UPROPERTY(BlueprintReadOnly,Category = "Weapon")
	EWeaponType CurrentWeaponType = EWeaponType::Knife;
	
	// 当前武器实例（Actor引用）																																				
	// UPROPERTY(BlueprintReadOnly,Category = "Weapon")
	// class AWeaponBase* CurrentWeapon = nullptr;	
	
	//是否开火
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bIsFiring = false;

	//是否换弹
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bIsReloading = false;
	
	// 是否正在持武器（持枪/收枪动画用）
	UPROPERTY(BlueprintReadOnly,Category = "Weapon")
	bool bIsArmed = false;
	
public:
	//更换武器类型
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(EWeaponType Type);
	
	//收武器
	// UFUNCTION(BlueprintCallable)
	// void Unequip();
		
};
