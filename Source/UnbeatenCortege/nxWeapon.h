#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "nxWeapon.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AnxWeapon();
	void fireWeapon(FVector direction);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/// Properties
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* weaponMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AnxProjectile> projectile;

	UPROPERTY(EditDefaultsOnly, Category = nx)
	float reloadTime;

	FTimerHandle m_timer_reload;

};
