#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "EnemySoldier.generated.h"

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


public: // virtual
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FGenericTeamId GetGenericTeamId() const override;


public:	// properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FOffensivity offensivity;

};
