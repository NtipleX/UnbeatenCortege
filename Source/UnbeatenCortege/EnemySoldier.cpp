#include "EnemySoldier.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemySoldier::AEnemySoldier()
{
	PrimaryActorTick.bCanEverTick = true;
	offensivity.Level = 1;
	offensivity.Experience = 0;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FGenericTeamId AEnemySoldier::GetGenericTeamId() const
{
	return FGenericTeamId(2);
}

FRotator AEnemySoldier::fireWeaponBasic(FVector point)
{
	FVector loc = GetActorLocation();
	FVector2D A{point - loc};
	float sina = A.Y / A.Size();
	float angle = FMath::Acos(sina) * 57.296 * -1 * FMath::Sign(A.X);
	return FRotator(0,angle,0);
}

float AEnemySoldier::rotateToPoint(FVector target)
{
	FVector origin = GetActorLocation();
	FVector2D A{ target - origin };
	float sina = A.Y / FMath::Sqrt(pow(A.Y, 2) + pow(A.X, 2));

	float UEDegree = UKismetMathLibrary::Asin(sina) * 57.296;
	if (A.X < 0)
	{
		float angle = 90.f;
		float diff = angle - fabs(UEDegree);
		UEDegree = (diff + angle) * FMath::Sign(A.Y);
	}

	return UEDegree;
	
}