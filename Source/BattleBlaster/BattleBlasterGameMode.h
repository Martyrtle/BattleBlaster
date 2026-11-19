// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	int32 countdownDelay = 3;

	UPROPERTY(EditAnywhere)
	float gameOverDelay = 3.0f;

	bool isVictory = false;

	int32 countdownSeconds;
	FTimerHandle countdownTimerHandle;

	ATank* tank;
	int32 towerCount;

	void ActorDied(AActor* deadActor);

	void OnGameOverTimeout();
	void OnCountdownTimerTimeout();
	
};
