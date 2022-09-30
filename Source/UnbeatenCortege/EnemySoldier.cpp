#include "EnemySoldier.h"

AEnemySoldier::AEnemySoldier()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

