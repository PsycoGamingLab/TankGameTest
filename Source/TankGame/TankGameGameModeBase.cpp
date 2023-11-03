// Copyright Epic Games, Inc. All Rights Reserved.


#include "TankGameGameModeBase.h"

#include "Controller/TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
//
// void ATankGameGameModeBase::PostLogin(APlayerController* NewPlayer)
// {
// 	UE_LOG(LogTemp,Warning,TEXT("PostLogin"));
// 	Super::OnPostLogin(NewPlayer);
// 	
// 	
// 	TankPlayerController = Cast<ATankPlayerController>(NewPlayer);
// 	if(TankPlayerController)
// 	{
// 		TArray<AActor*> FoundActors;
// 		//Get all tank in the map
// 		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATankBase::StaticClass(), FoundActors);
// 		index++;
// 		Tank = Cast<ATankBase>(FoundActors[index]);
// 		if(Tank)
// 		{
// 			Tank->SetTankPlayerController(TankPlayerController);
// 			FTimerHandle TimerHandle;
// 			FTimerDelegate TimerDelegate;
//  
// 			// Lambda delay (problem to SetTargetView immediately)
// 			TimerDelegate.BindLambda([&]()
// 			{				
// 				SetTargetView();				
// 			});
//  
// 			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);		
// 		
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp,Warning,TEXT("Fail to cast TankBase"));
// 		}
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp,Warning,TEXT("Fail to cast TankPlayerController"));
// 	}
// 	
// }
//
// void ATankGameGameModeBase::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// }
//
// void ATankGameGameModeBase::SetTargetView()
// {
// 	//Set Target view and save tank ref on TankPlayerController
// 	TankPlayerController->SetTargetViewClient(Tank);
// }
//
// void ATankGameGameModeBase::RespawnTank(ATankBase*TankRef)
// {
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),FoundPlayerStart);
// 	
// 	int Rand = FMath::RandRange(1,FoundPlayerStart.Num()-1);	
// 	FVector RespawnLocation = FoundPlayerStart[Rand]->GetActorLocation();
// 	TankRef->SetActorLocation(RespawnLocation);
// }
