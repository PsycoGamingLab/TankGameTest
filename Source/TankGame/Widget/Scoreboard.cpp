// Fill out your copyright notice in the Description page of Project Settings.


#include "Scoreboard.h"
#include "ScoreSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "TankGame/GameState/TankGameState.h"

void UScoreboard::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateScoreboard();
	
	// Every 1 sec update scoreboard 
	GetWorld()->GetTimerManager().SetTimer(
		ScoreboardUpdate,
		this,
		&UScoreboard::UpdateScoreboard,
		1.0f,
		true);
}

void UScoreboard::BeginDestroy()
{
	Super::BeginDestroy();
	ScoreboardUpdate.Invalidate();
}

void UScoreboard::UpdateScoreboard()
{
	//Clear the scoreboard
	VerticalScoreBox->ClearChildren();
	
	//Update scoreboard with PlayerState info
	//Every PlayerState create a single ScoreSlot
	for (auto PlayerInfo : GetWorld()->GetGameState()->PlayerArray)
	{
		UScoreSlot* SingleScoreSlot = CreateWidget<UScoreSlot>(GetWorld(),ScoreboardSlotClass);
		if(SingleScoreSlot)
		{
			SingleScoreSlot->AddToViewport(1);
			SingleScoreSlot->ScoreText->SetText(FText::FromString(FString::SanitizeFloat(PlayerInfo->GetScore())));
			SingleScoreSlot->PlayerNameText->SetText(FText::FromString(PlayerInfo->GetPlayerName()));
			VerticalScoreBox->AddChildToVerticalBox(SingleScoreSlot);
		}
	}
	
}
