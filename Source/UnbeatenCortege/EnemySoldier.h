#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemySoldier.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AEnemySoldier : public ACharacter
{
	GENERATED_BODY()

public:

	AEnemySoldier();


public: // virtual

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
