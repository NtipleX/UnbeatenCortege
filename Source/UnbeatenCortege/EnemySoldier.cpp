#include "EnemySoldier.h"

AEnemySoldier::AEnemySoldier()
{
	PrimaryActorTick.bCanEverTick = true;
	offensivity.Level = 1;
	offensivity.Experience = 0;
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

FGenericTeamId AEnemySoldier::GetGenericTeamId() const
{
	return FGenericTeamId(2);
}