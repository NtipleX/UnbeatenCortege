#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "nxWeapon.h"
#include "nxProjectile.h"
#include "EnemySoldierAnimator.h"
#include "Animation/AnimMontage.h"
#include "EnemySoldier.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyHit);

USTRUCT(BlueprintType)
struct FOffensivity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	int Experience;
};

UCLASS()
class UNBEATENCORTEGE_API AEnemySoldier : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AEnemySoldier();

	UFUNCTION(BlueprintCallable)
	FRotator fireWeaponBasic(FVector point);

	UFUNCTION(BlueprintCallable)
	float rotateToPoint(FVector target);

	UFUNCTION(BlueprintCallable)
	void fireWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	bool HasSeenPlayerBeforeDeath();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;


public:	// properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FOffensivity offensivity;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AnxWeapon> weapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AnxProjectile> ammoOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = nx, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* heroHealthbar;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyHit OnEnemyHit;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* dieMontage;

	UPROPERTY(BlueprintReadWrite)
	bool m_isDead;


private:
	UPROPERTY()
	AnxWeapon* m_gun;

	void sinkBody();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = nx, meta = (AllowPrivateAccess = true))
	float heroHealth;

	float m_lastTimeShot;
	UEnemySoldierAnimator* m_animator;
	FTimerHandle m_sinkingDeath;

	UPROPERTY(BlueprintReadWrite, Category = nx, meta = (AllowPrivateAccess = true))
	bool canShoot;

	uint32 m_sinkCounter;


};
