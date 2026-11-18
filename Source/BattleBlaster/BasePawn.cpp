// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(capsuleComp);

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	projectileSpawnPoint->SetupAttachment(turretMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::Fire()
{
	FVector spawnLocation = projectileSpawnPoint->GetComponentLocation();
	FRotator spawnRotation = projectileSpawnPoint->GetComponentRotation();

	if (AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, spawnLocation, spawnRotation))
	{
		projectile->SetOwner(this);
	}
}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector vectorToTarget = lookAtTarget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.0f, vectorToTarget.Rotation().Yaw, 0.0f);
	FRotator interpolatedRotation = FMath::RInterpTo(turretMesh->GetComponentRotation(), lookAtRotation, GetWorld()->GetDeltaSeconds(), 10.0f);

	turretMesh->SetWorldRotation(interpolatedRotation);
}

