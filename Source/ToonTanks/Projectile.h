// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Physical Components") // meta = (AllowPrivateAccess = "true")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
		class UProjectileMovementComponent* ProjMoveComp;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
		float m_InitialSpeed = 800.0f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float m_MaxSpeed = 800.0f;
	
	UPROPERTY(EditAnywhere)
		float Damage = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
		class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
