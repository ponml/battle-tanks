// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	ATank* possessedTank = GetControlledTank();
	if (possessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController Posessed ai Tank %s"), *(possessedTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NO ai TANK FOUND"));
	}

	ATank* playerTank = GetPlayerTank();
	if (playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI found player tank %s"), *(playerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ai couldn't find player tank"));

	}
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayerTank();
}

void ATankAiController::AimTowardsPlayerTank() {
	auto myTank = GetControlledTank();
	auto playerTank = GetPlayerTank();

	if (playerTank) {
		auto playerLocation = playerTank->GetActorLocation();
		myTank->AimAt(playerLocation);
	}
}

ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); //returns pawn the playercontroller is possession (since this is inheritting from PlayerController)
}

ATank * ATankAiController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	} else {
		return  Cast<ATank>(PlayerPawn);
	}
	
}
