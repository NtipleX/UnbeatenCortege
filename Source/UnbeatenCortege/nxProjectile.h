#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "nxProjectile.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxProjectile : public AActor
{
	GENERATED_BODY()
		
public:	
	AnxProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* projMesh;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* projParticle;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* projRoot;
	
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* projMovement;
	
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* projBox;

	UPROPERTY(EditDefaultsOnly)
	class USoundCue* SoundNormalHit;
	UPROPERTY(EditDefaultsOnly)
	class USoundCue* SoundNormalHit2;
	UPROPERTY(EditDefaultsOnly)
	class USoundCue* SoundNormalHit3;

	UPROPERTY(EditDefaultsOnly, Category = nx)
	class UParticleSystem* explosion; 
	UPROPERTY(EditDefaultsOnly, Category = nx)
	float damage;

private:
	UFUNCTION()
	void projectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
