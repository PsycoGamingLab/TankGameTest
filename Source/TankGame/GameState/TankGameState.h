// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TankGame/PlayerState/TankPlayerState.h"
#include "TankGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChange);

UCLASS()
class TANKGAME_API ATankGameState : public AGameState
{
	GENERATED_BODY()
	

};