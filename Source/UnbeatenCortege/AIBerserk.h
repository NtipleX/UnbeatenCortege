#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "AIBerserk.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AAIBerserk : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UWidgetComponent* HealthBar;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATakeable> slot1;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATakeable> slot2;
	UPROPERTY(EditAnywhere)
	FVector socketPos;
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* stabMontage;
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* kickMontage;


public:
	AAIBerserk();

	UFUNCTION(BlueprintCallable)
	void stab();


public:
	virtual void BeginPlay() override;
	virtual void Tick(float delta) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PIC) override;


private:
	ATakeable* m_slot1;
	ATakeable* m_slot2;
	

};
