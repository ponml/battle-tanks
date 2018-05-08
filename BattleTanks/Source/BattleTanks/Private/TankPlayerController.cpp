// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); //returns pawn the playercontroller is possession (since this is inheritting from PlayerController)
}


