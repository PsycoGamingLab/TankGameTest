// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void AddScore(float Points);
	virtual void OnRep_Score() override;

private:
	int Score;
	
};

inline void ATankPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	
}
