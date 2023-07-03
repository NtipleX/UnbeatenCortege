#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "nxWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType: uint8
{
	Pistol UMETA(DisplayName="Pistoll"),
	SMG,
	AssaultRifle
};

UENUM(BlueprintType)
enum class EThrowableType : uint8
{
	Smoke,
	Grenade,
	Molotov
};

UCLASS()
class UNBEATENCORTEGE_API AnxWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AnxWeapon();
	bool fireWeapon(FVector direction, FVector startPos);

	UPROPERTY(EditDefaultsOnly, Category = nx)
	class USoundCue* SoundFire;

	UPROPERTY(EditDefaultsOnly, Category = nx)
	class UParticleSystem* ParticleFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = nx)
	float reloadTime;

	// Weapon spread
	UPROPERTY(EditDefaultsOnly, Category = nx)
	float MinSpread;
	// Weapon spread
	UPROPERTY(EditDefaultsOnly, Category = nx)
	float MaxSpread;

	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType;

	UFUNCTION()
	void OnGameStarted();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/// Properties
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* weaponMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AnxProjectile> projectile;

	FTimerHandle m_timer_reload;

};
