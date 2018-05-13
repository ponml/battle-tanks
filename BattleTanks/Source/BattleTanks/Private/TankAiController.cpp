// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayerTank();
}

void ATankAiController::AimTowardsPlayerTank() {
	
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto playerTank = playerPawn ? Cast<ATank>(playerPawn) : nullptr;
	if (playerTank) {
		auto playerLocation = playerTank->GetActorLocation();
		auto myTank = Cast<ATank>(GetPawn());
		myTank->AimAt(playerLocation);
		myTank->Fire();
	}
}