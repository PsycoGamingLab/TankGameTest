// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "TankGame/GameState/TankGameState.h"

void ATankPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void ATankPlayerState::AddScore(float Points)
{	
	SetScore(GetScore()+Points);
	UE_LOG(LogTemp,Warning,TEXT("Add score on Player State and broadcast ScoreChange %d"),Score);
}
