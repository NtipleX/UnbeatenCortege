// Fill out your copyright notice in the Description page of Project Settings.


#include "nxEnemySpawner.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySoldier.h"
#include "nxGameMode.h"

// Sets default values
AnxEnemySpawner::AnxEnemySpawner() : m_index(0), currentWaveEnemyCounter(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AnxEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	if (!tunnels.Num() || !cortegesToSpawn.Num() || !waves.Num())
	{
		GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, FString("No corteges specified or tunnels or waves"));
		return;
	}
	for (const auto& item : cortegesToSpawn)
		corteges.Enqueue(item);
	currentWaveEnemyCounter = waves[0];
	waves.RemoveAt(0);
	GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, 1.0f, false, 1.0f);
}

// Called every frame
void AnxEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AnxEnemySpawner::spawnCortege()
{
	/* Enemy wave spawner
	* After each wave has spawned - we wait untill every enemy unit is being destroyed;
	* If we encounter number less then -1 - we gonna wait for the time equals waves[0]*(-1);
	* Zero in waves is reserved.
	*/
	if (currentWaveEnemyCounter <= 0)
	{
		if(waves.IsValidIndex(0))
		{
			if (currentWaveEnemyCounter == 0 && waves[0] > 0)
			{
				// Enemy counter condition
				if(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySoldier::StaticClass()))
				{
					GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, 1.0f, false, 1.0f);
					return;
				}
				currentWaveEnemyCounter = waves[0];
				waves.RemoveAt(0);
				GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, 1.0f, false, 1.0f);
				return;
			}
			else if(currentWaveEnemyCounter == 0 && waves[0] < 0)
			{
				// Timing condition
				currentWaveEnemyCounter = waves[0];
				waves.RemoveAt(0);
				GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, currentWaveEnemyCounter*-1, false, currentWaveEnemyCounter*-1);
				// Actual wave number
				currentWaveEnemyCounter= waves[0];
				waves.RemoveAt(0);
				return;
			}

			// next wave
			else{
			currentWaveEnemyCounter = waves[0];
			waves.RemoveAt(0);
			}
		}
		else
		{
			if (!UGameplayStatics::GetActorOfClass(GetWorld(), AEnemySoldier::StaticClass()))
			{
				GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, 0.5f, false, 0.5f);
				return;
			}
			dynamic_cast<AnxGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->GameWinEvent();
		}
	}

	if (!tunnels.IsValidIndex(m_index))
		m_index = 0;

	TSubclassOf<ACharacter> unitClass;
	if(!corteges.Dequeue(unitClass))
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Cyan, FString("No corteges remain"));
		return;
	}
	tunnels[m_index++]->spawnUnit(unitClass);
	--currentWaveEnemyCounter;
	GetWorldTimerManager().SetTimer(respawnKD, this, &AnxEnemySpawner::spawnCortege, 1.0f, false, 1.0f);
}