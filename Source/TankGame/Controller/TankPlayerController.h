// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankBase;
/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> ScoreboardClass;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, meta =(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, meta =(AllowPrivateAccess = "true"))
	class UInputAction* ShootClickAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, meta =(AllowPrivateAccess = "true"))
	class UInputAction* ScoreboardAction;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, meta =(AllowPrivateAccess = "true"))
	class UInputAction* ReturnToMainMenu;
	
protected:

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

	void OnSetDestinationTriggered();
	void OnSetDestinationCompleted();
	void OnFireTriggered();
	void OnScoreboardPress();
	void OnScoreboardUnpress();
	void OnReturnMainMenuPress();

	UFUNCTION(BlueprintNativeEvent)
	void BP_AIMove(ATankBase* Tank,const FVector Destination);
private:

	UPROPERTY()
	class UScoreboard* Scoreboard;
	
	bool bCanShoot=true;
	UPROPERTY()
	ATankBase* TankRef;
	FVector CachedDestination;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	UFUNCTION(Server,Reliable)
	void FireServer(const FVector Location,const FRotator Rotation,ATankBase* Tank);

public:
	UFUNCTION(Client,Reliable)
	void SetTargetViewClient(ATankBase* Tank);
	void AddScore();
	FORCEINLINE void SetTankRef(ATankBase* Tank){TankRef=Tank;}
	
	

};
