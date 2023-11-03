// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TankGame/Controller/TankPlayerController.h"
#include "Scoreboard.generated.h"

class ATankGameState;
/**
 * 
 */
UCLASS()
class TANKGAME_API UScoreboard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta =(BindWidget))
	class UVerticalBox* VerticalScoreBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> ScoreboardSlotClass;
		
	virtual void BeginDestroy() override;
	void UpdateScoreboard();
	
protected:
	virtual void NativeConstruct() override;
private:
	FTimerHandle ScoreboardUpdate;
	
};
