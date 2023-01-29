// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
	TankPlayerController->bShowMouseCursor = true;
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		//Draws Yellow Sphere at cursor impact point
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Yellow, false, -1);
		FVector HitLocation = HitResult.ImpactPoint;
		
		RotateTurret(HitLocation);
		
	}

}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = Value*Speed*DeltaTime; 
	AddActorLocalOffset(DeltaLocation, true);

	//AddActorLocalOffset(FVector::ForwardVector)
}


void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * RSpeed * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}

//void ATank::Fire()
//{
//	Super::Fire();
//	DrawDebugSphere(GetWorld(), HitLocation, 25.f, 12, FColor::Red, false, 3);
//}


