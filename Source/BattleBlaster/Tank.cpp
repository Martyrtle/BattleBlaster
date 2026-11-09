// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(capsuleComp);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* localPlayer = playerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer))
			{
				subsystem->AddMappingContext(defaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

