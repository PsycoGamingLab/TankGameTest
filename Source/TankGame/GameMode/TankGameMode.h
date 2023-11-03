// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TankGame/Controller/TankPlayerController.h"
#include "TankGame/Characters/TankBase.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	int index= -1;
	UPROPERTY()
	ATankPlayerController* TankPlayerController = nullptr;
	UPROPERTY()
	ATankBase* Tank = nullptr;
	UPROPERTY()
	TArray<AActor*> FoundPlayerStart;
protected:
	/** Called as part of DispatchPostLogin */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void SetTargetView();
public:
	void AddScore(const ATankPlayerController* AttackerController);
	void RespawnTank(ATankBase*Tank);

};
