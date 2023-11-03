// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TankGame/Characters/TankBase.h"
#include "TankGame/GameState/TankGameState.h"
#include "TankGame/Projectiles/BaseProjectile.h"
#include "TankGame/Widget/Scoreboard.h"



ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATankPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction,ETriggerEvent::Completed,this,&ATankPlayerController::OnSetDestinationCompleted);
		EnhancedInputComponent->BindAction(ShootClickAction,ETriggerEvent::Triggered,this,&ATankPlayerController::OnFireTriggered);
		EnhancedInputComponent->BindAction(ScoreboardAction,ETriggerEvent::Triggered,this,&ATankPlayerController::OnScoreboardPress);
		EnhancedInputComponent->BindAction(ScoreboardAction,ETriggerEvent::Completed,this,&ATankPlayerController::OnScoreboardUnpress);
		EnhancedInputComponent->BindAction(ReturnToMainMenu,ETriggerEvent::Completed,this,&ATankPlayerController::OnReturnMainMenuPress);
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}	
}

void ATankPlayerController::OnSetDestinationTriggered()
{
	 FHitResult Hit;
	 bool bHitSuccessful = false;
	 bHitSuccessful=GetHitResultUnderCursor(ECC_Visibility,true,Hit);
	
	if(bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
}

void ATankPlayerController::OnSetDestinationCompleted()
{
	if(TankRef)
	{
		//Call BP native event
		BP_AIMove(TankRef,CachedDestination);		
	}	
}

void ATankPlayerController::OnFireTriggered()
{
	if(bCanShoot && TankRef)
	{
		bCanShoot = false;

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]
		{
			//GEngine->AddOnScreenDebugMessage(-1,15.f,FColor::Yellow,TEXT("Enter Lambda Reset Fire"));
			bCanShoot =true;
		});
	
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
		FVector Location = TankRef->GetProjectileSpawnPointLocation();
		FRotator Rotation = TankRef->GetProjectileSpawnPointRotation();
		
		FireServer(Location,Rotation,TankRef);
	}
}

void ATankPlayerController::OnScoreboardPress()
{
	//UE_LOG(LogTemp,Warning,TEXT("Open scoreboard"));
	Scoreboard = Scoreboard == nullptr ? CreateWidget<UScoreboard>(this,ScoreboardClass):Scoreboard;
	if(!Scoreboard->IsInViewport())
	{
		Scoreboard->AddToViewport(1);
	}
	if(Scoreboard && IsLocalController())
	{
		UE_LOG(LogTemp,Warning,TEXT("Widget is created"));		
		Scoreboard = Scoreboard == nullptr ? CreateWidget<UScoreboard>(this,ScoreboardClass):Scoreboard;
		Scoreboard->SetVisibility(ESlateVisibility::HitTestInvisible);		
	}
	
}

void ATankPlayerController::OnScoreboardUnpress()
{
	//UE_LOG(LogTemp,Warning,TEXT("Close scoreboard"));
	if(Scoreboard)
	{
		Scoreboard->RemoveFromParent();
	}
}

void ATankPlayerController::OnReturnMainMenuPress()
{
	if(GetWorld()->GetMapName() != "MenuMap")
	{
		UGameplayStatics::OpenLevel(this,"MenuMap");
	}	
}

void ATankPlayerController::AddScore()
{
	ATankPlayerState* TankPlayerState = Cast<ATankPlayerState>(PlayerState);
	if(TankPlayerState)
	{
		UE_LOG(LogTemp,Warning,TEXT("Playerstate exist"));
		TankPlayerState->AddScore(1);
		Scoreboard->UpdateScoreboard();		
	}
}


void ATankPlayerController::FireServer_Implementation(const FVector Location,const FRotator Rotation,ATankBase* Tank)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Tank;
	GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass,Location,Rotation,SpawnParameters);
}

void ATankPlayerController::BP_AIMove_Implementation(ATankBase* Tank, const FVector Destination)
{
}

void ATankPlayerController::SetTargetViewClient_Implementation(ATankBase* Tank)
{
	SetViewTargetWithBlend(Tank);
	TankRef=Tank;
}



