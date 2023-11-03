// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "TankGame/Controller/TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TankGame/GameState/TankGameState.h"
#include "TankGame/PlayerState/TankPlayerState.h"

void ATankGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp,Warning,TEXT("PostLogin"));
	Super::OnPostLogin(NewPlayer);
	
	TankPlayerController = Cast<ATankPlayerController>(NewPlayer);
	if(TankPlayerController)
	{
		TArray<AActor*> FoundActors;
		//Get all tank in the map
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATankBase::StaticClass(), FoundActors);
		index++;
		Tank = Cast<ATankBase>(FoundActors[index]);
		if(Tank)
		{
			//Assign current player controller to the associate tank
			Tank->SetTankPlayerController(TankPlayerController);
			
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate;
 
			// Lambda delay (problem to SetTargetView immediately)
			TimerDelegate.BindLambda([&]()
			{				
				SetTargetView();				
			}); 
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);			
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Fail to cast TankBase"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Fail to cast TankPlayerController"));
	}	
}

void ATankGameMode::SetTargetView()
{
	//Set Target view and save tank ref on TankPlayerController
	TankPlayerController->SetTargetViewClient(Tank);
}

void ATankGameMode::AddScore(const ATankPlayerController* AttackerController)
{
	ATankPlayerState* AttackerPlayerState = Cast<ATankPlayerState>(AttackerController->PlayerState);	
	if(AttackerPlayerState)
	{
		UE_LOG(LogTemp,Warning,TEXT("Add score from game mode"));
		AttackerPlayerState->AddScore(1);
	}
}

void ATankGameMode::RespawnTank(ATankBase*TankRef)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),FoundPlayerStart);
	
	int Rand = FMath::RandRange(1,FoundPlayerStart.Num()-1);	
	FVector RespawnLocation = FoundPlayerStart[Rand]->GetActorLocation();
	TankRef->SetActorLocation(RespawnLocation);
}
