#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.h"
#include "Barricade.generated.h"

UCLASS()
class UNBEATENCORTEGE_API ABarricade : public AActor
{
	GENERATED_BODY()
	
public:	
	ABarricade();
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* root;
	UPROPERTY(EditDefaultsOnly)
	UWall* block1;
	UPROPERTY(EditDefaultsOnly)
	UWall* block2;
	UPROPERTY(EditDefaultsOnly)
	UWall* block3;
	UPROPERTY(EditDefaultsOnly)
	UWall* block4;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> debris;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

private:
	bool m_isDamaged;
	UPROPERTY()
	AActor* m_debris;

};
