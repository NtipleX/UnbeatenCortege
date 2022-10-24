// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "nxTunnel.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxTunnel : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* arcMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* innerMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* spawnLoc;

public:
	AnxTunnel();

	UFUNCTION(BlueprintCallable)
	AActor* spawnUnit(TSubclassOf<ACharacter> unitClass);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
