#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "nxTunnel.h"
#include "Engine/EngineTypes.h"
#include "Containers/Queue.h"
#include "GameFramework/Character.h"
#include "nxEnemySpawner.generated.h"

UCLASS(NotBlueprintable)
class UNBEATENCORTEGE_API AnxEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<AnxTunnel*> tunnels;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACharacter> enemyToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACharacter>> cortegesToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<int> waves;

	
public:	
	AnxEnemySpawner();

	UFUNCTION(BlueprintCallable)
	void spawnCortege();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle respawnKD;
	int m_index;
	int currentWaveEnemyCounter;
	TQueue<TSubclassOf<ACharacter>, EQueueMode::Spsc> corteges;
	TArray<class AEnemySoldier*> spawnedEnemySoldiers;

};
