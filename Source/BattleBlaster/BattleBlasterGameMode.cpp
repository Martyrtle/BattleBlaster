// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"

// Called when the game starts or when spawned
void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), towers);
	towerCount = towers.Num();
	UE_LOG(LogTemp, Display, TEXT("Number of towers: %d"), towerCount);

	if (APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		tank = Cast<ATank>(playerPawn);
		if (!tank)
		{
			UE_LOG(LogTemp, Display, TEXT("GameMode: Failed to find the tank actor!"));
		}
	}
}

