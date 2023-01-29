// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATank();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

private:



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera System", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera System", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = "Variables")
	float Speed = 100.0f;

	//Rotation Speed
	UPROPERTY(EditAnywhere, Category = "Variables")
	float RSpeed = 100.0f;

	APlayerController* TankPlayerController;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float Value);

	void Turn(float Value);


	



};
