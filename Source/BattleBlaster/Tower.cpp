// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

// Sets default values
ATower::ATower()
{
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle fireTimerHandle;
	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &ATower::CheckFireCondition, fireRate, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInFireRange())
	{
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (IsInFireRange())
	{
		Fire();
	}
}

bool ATower::IsInFireRange()
{
	if (tank)
	{
		float distanceToTank = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		return distanceToTank <= fireRange;
	}

	return false;
}

