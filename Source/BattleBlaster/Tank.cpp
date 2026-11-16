// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"

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

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		FHitResult hitResult;
		playerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		FVector impactPoint = hitResult.ImpactPoint;

		DrawDebugSphere(GetWorld(), impactPoint, 10.0f, 10, FColor::Red);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComp->BindAction(moveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		enhancedInputComp->BindAction(turnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
	}
}

void ATank::MoveInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();
	FVector deltaLocation = FVector::Zero();

	deltaLocation.X = speed * inputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::TurnInput(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();
	FRotator deltaRotation = FRotator::ZeroRotator;
	
	deltaRotation.Yaw = turnRate * inputValue * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(deltaRotation, true);
}

