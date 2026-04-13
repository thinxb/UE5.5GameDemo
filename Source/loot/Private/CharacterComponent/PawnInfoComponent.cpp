// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/PawnInfoComponent.h"

// Sets default values for this component's properties
UPawnInfoComponent::UPawnInfoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPawnInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPawnInfoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPawnInfoComponent::SetAiming(bool bNewAiming)
{
	if (bAiming != bNewAiming)
	{
		bAiming = bNewAiming;
	}
	
}

void UPawnInfoComponent::SetRunning(bool bNewRunning)
{
	if (bRunning != bNewRunning)
	{
		bRunning = bNewRunning;
	}
}

void UPawnInfoComponent::SetShooting(bool bNewShooting)
{
	if (bShooting != bNewShooting)
	{
		bShooting = bNewShooting;
	}
}

void UPawnInfoComponent::SetUsingLethal(bool bNewUsingLethal)
{
	if (bUsingLethal != bNewUsingLethal)
	{
		bUsingLethal = bNewUsingLethal;
	}
}

void UPawnInfoComponent::SetLeaning(float NewLeaning)
{
	Leaning = FMath::Clamp(NewLeaning, -1.0f, 1.0f);  // 限制范围
}

void UPawnInfoComponent::SetCrouching(bool bNewCrouching)
{
	if (bCrouching != bNewCrouching)
	{
		bCrouching = bNewCrouching;
	}
}

void UPawnInfoComponent::SetReloading(bool bNewReloading)
{
	if (bReloading != bNewReloading)
	{
		bReloading = bNewReloading;
	}
}

void UPawnInfoComponent::SetPerformingAction(bool bNewPerformingAction)
{
	if (bPerformingAction != bNewPerformingAction)
	{
		bPerformingAction = bNewPerformingAction;
	}
}

void UPawnInfoComponent::SetChangingWeapon(bool bNewChangingWeapon)
{
	if (bChangingWeapon != bNewChangingWeapon)
	{
		bChangingWeapon = bNewChangingWeapon;
	}
}

void UPawnInfoComponent::SetInspectingWeapon(bool bNewInspectingWeapon)
{
	if (bInspectingWeapon != bNewInspectingWeapon)
	{
		bInspectingWeapon = bNewInspectingWeapon;
	}
}

void UPawnInfoComponent::SetLookUp(float NewLookUp)
{
	LookUp = FMath::Clamp(NewLookUp, -90.0f, 90.0f);
}

void UPawnInfoComponent::SetLookRight(float NewLookRight)
{
	LookRight = FMath::Clamp(NewLookRight, -90.0f, 90.0f);
}

void UPawnInfoComponent::SetTacticalSprint(bool bNewTacticalSprint)
{
	if (bTacticalSprint != bNewTacticalSprint)
	{
		bTacticalSprint = bNewTacticalSprint;
	}
}

