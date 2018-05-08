// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank * GetControlledTank() const; //as a getter, const makes sense
	ATank * GetPlayerTank() const; //as a getter, const makes sense
	void BeginPlay() override;
	
	
	
};
