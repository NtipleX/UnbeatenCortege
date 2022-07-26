#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TraceHelpers.h"
#include "nxHero.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxHero : public ACharacter
{
	GENERATED_BODY()

public:

	AnxHero();

	// Shoot to point
	void fireWeapon(FVector pointOnMap);

public:

	/* @brief getHeroHealth - returns hero health */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float getHeroHealth() const;

	bool isEnemy;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Setting up bindings
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

private:
	/// Input Bindings
	void moveForward(float axis);
	void moveSide(float axis);

private:
	/// Components
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = nx, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* heroHealthbar;

	/// Movement
	float m_moveForward;
	float m_moveSide;

	/// Guns
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class AnxWeapon> startingWeapon;
	class AnxWeapon* m_gun;

	/// Misc
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = nx, meta = (AllowPrivateAccess = true))
	float heroHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = nx, meta = (AllowPrivateAccess = true))
	float heroAlive;

	class UnxAnimator* m_animator;

	
};
