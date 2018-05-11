// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	ATank* possessedTank = GetControlledTank();
	if (possessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Posessed My Tank %s"), *(possessedTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find my tank"));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	//Get world Location 
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); //returns pawn the playercontroller is possession (since this is inheritting from PlayerController)
}


void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction %s"), *(HitLocation.ToString()));		
		//TODO tell tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

//if it hits the landscape, return true
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	
	// find the crosshair position in pixel coords
	OutHitLocation = FVector(0.f);
	int32 viewPortSizeX;
	int32 viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	FVector2D ScreenPixelLocation = FVector2D(viewPortSizeX * CrossHairXLocation, viewPortSizeY * CrossHairYLocation);

	//out, unit vector
	FVector LookDirection;
	if (GetLookDirection(ScreenPixelLocation, LookDirection)) {
		// line-trace along that direction (look direction), and see what we hit, up to a max range
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection:  %s"), *(LookDirection.ToString()));
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {

	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (LookDirection * LineTraceRange);
	FHitResult HitResult;
	auto hasHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
	);
	HitLocation = hasHit ? HitResult.Location : FVector(0);
	return hasHit;

}