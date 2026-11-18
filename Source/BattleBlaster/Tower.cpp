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

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tank)
	{
		float distanceToTank = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		if (distanceToTank <= fireRange)
		{
			RotateTurret(tank->GetActorLocation());
		}
	}
}

