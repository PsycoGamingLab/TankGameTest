// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "TankGame/Characters/TankBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankGame/GameMode/TankGameMode.h"
#include "TankGame/PlayerState/TankPlayerState.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->SetIsReplicated(true);
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartDestroyTimer();
	ProjectileMesh->OnComponentHit.AddDynamic(this,&ABaseProjectile::OnHit);
}

void ABaseProjectile::StartDestroyTimer()
{
	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&ABaseProjectile::DestroyTimerFinished,
		DestroyTime);
}

void ABaseProjectile::DestroyTimerFinished()
{
	Destroy();
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor)
	{
		ATankBase* TankVictim= Cast<ATankBase>(OtherActor);

		//Check if hitter is different than owner projectile
		if(TankVictim && TankVictim!=GetOwner())
		{
			TankVictim->RespawnTank();
			ATankBase* TankOwner = Cast<ATankBase>(GetOwner());
			ATankGameMode* TankGameMode= GetWorld()->GetAuthGameMode<ATankGameMode>();
			if(TankGameMode)
			{
				//Add score to projectile owner
				TankGameMode->AddScore(TankOwner->TankPlayerController);
			}
		}		
	}
	Destroy();
}
// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::Destroyed()
{
	Super::Destroyed();
}

