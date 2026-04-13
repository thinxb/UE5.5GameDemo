// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnInfoComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOT_API UPawnInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnInfoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//蓝图获取
	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsRunning() const { return bRunning; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsShooting() const { return bShooting; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsUsingLethal() const { return bUsingLethal; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	float GetLeaning() const { return Leaning; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsCrouching() const { return bCrouching; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsReloading() const { return bReloading; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsPerformingAction() const { return bPerformingAction; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsChangingWeapon() const { return bChangingWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsInspectingWeapon() const { return bInspectingWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	float GetLookUp() const { return LookUp; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	float GetLookRight() const { return LookRight; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	bool IsTacticalSprint() const { return bTacticalSprint; }
	
	//蓝图修改
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetAiming(bool bNewAiming);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetRunning(bool bNewRunning);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetShooting(bool bNewShooting);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetUsingLethal(bool bNewUsingLethal);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetLeaning(float NewLeaning);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetCrouching(bool bNewCrouching);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetReloading(bool bNewReloading);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetPerformingAction(bool bNewPerformingAction);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetChangingWeapon(bool bNewChangingWeapon);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetInspectingWeapon(bool bNewInspectingWeapon);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetLookUp(float NewLookUp);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetLookRight(float NewLookRight);

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SetTacticalSprint(bool bNewTacticalSprint);
	
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bAiming;//瞄准
	
	UPROPERTY(BlueprintReadOnly,Category = "Character")
	bool bRunning;//奔跑
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bShooting;//开火
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bUsingLethal;//使用致命武器
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float Leaning;//倾斜
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bCrouching;//蹲下
	
	UPROPERTY(BlueprintReadOnly,category = "Character")
	bool bReloading;//重新装填
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bPerformingAction;//执行操作
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bChangingWeapon;//切换武器
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bInspectingWeapon;//检视武器 
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float LookUp;//上下抬头
	
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float LookRight;//左右视角
	
	UPROPERTY(BlueprintReadOnly,Category = "Character")
	bool bTacticalSprint;//战术冲刺
	
	
	
};
