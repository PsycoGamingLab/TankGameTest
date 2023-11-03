// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankGame/GameMode/TankGameMode.h"
#include "TankGame/PlayerState/TankPlayerState.h"
#include "TankGame/Projectiles/BaseProjectile.h"

// Sets default values
ATankBase::ATankBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Projectile spawn point setup
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());

	
}

void ATankBase::DebugDestroy()
{
	Destroy();
}

void ATankBase::SetTankPlayerController(ATankPlayerController* PlayerController)
{
	this->TankPlayerController=PlayerController;
}

void ATankBase::RespawnTank()
{
	if(TankPlayerController)
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerController exist"));
		ATankGameMode* GameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(TankPlayerController));
		if(GameMode)
		{
			GameMode->RespawnTank(this);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Cast to Game Mode Fail"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerController Fail"));
	}
	
}

void ATankBase::AddScore()
{
	UE_LOG(LogTemp,Warning,TEXT("Add score on tank base"));
	
	if(TankPlayerController)
	{
		TankPlayerController->AddScore();
	}
	
}



