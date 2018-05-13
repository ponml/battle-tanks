// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

//forward delcaration
class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void AimTowardsPlayerTank();
	
	
};
