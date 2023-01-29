// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBase"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTop"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnpoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnpoint->SetupAttachment(TurretMesh);
}


void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
		
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}



void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator ToRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), ToRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), RotateSpeed));

}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnpoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnpoint->GetComponentRotation();
	
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

	//DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Blue, false, 3.f);
}





