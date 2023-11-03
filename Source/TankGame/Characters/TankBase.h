// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TankGame/Controller/TankPlayerController.h"
#include "TankBase.generated.h"


class USpringArmComponent;

UCLASS()
class TANKGAME_API ATankBase : public ACharacter
{
	GENERATED_BODY()
public:
	ATankBase();

	UPROPERTY()
	ATankPlayerController* TankPlayerController;
	void DebugDestroy();

private:
	UPROPERTY(VisibleAnywhere,Category ="Tank")
	class USceneComponent* ProjectileSpawnPoint;

public:	
	FORCEINLINE FVector GetProjectileSpawnPointLocation()const{return ProjectileSpawnPoint->GetComponentLocation();}
	FORCEINLINE FRotator GetProjectileSpawnPointRotation()const{return ProjectileSpawnPoint->GetComponentRotation();}
	void SetTankPlayerController(ATankPlayerController* PlayerController);
	void RespawnTank();
	void AddScore();

};
