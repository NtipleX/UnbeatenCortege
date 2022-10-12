#include "EnemySoldier.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "TraceHelpers.h"

AEnemySoldier::AEnemySoldier() : heroHealth(100.f)
{
	PrimaryActorTick.bCanEverTick = true;
	offensivity.Level = 1;
	offensivity.Experience = 0;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	heroHealthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeroWidgetComp"));
	heroHealthbar->SetupAttachment(RootComponent);
	heroHealthbar->SetRelativeLocation(FVector(0, 0, 100));
	heroHealthbar->SetWidgetSpace(EWidgetSpace::Screen);
	heroHealthbar->SetDrawSize(FVector2D(60, 10));
	heroHealthbar->SetVisibility(false, false);
	SetCanBeDamaged(true);
}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	if (weapon)
	{
		m_gun = GetWorld()->SpawnActor<AnxWeapon>(weapon, FTransform());
		m_gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("SKT_Pistol"));
	}
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

void AEnemySoldier::fireWeapon()
{
	GetWorld()->SpawnActor<AActor>(ammoOverride.Get(), GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
}

float 	AEnemySoldier::TakeDamage
(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	heroHealth -= DamageAmount;

	if (heroHealth <= 0)
	{
		Destroy();
	}

	if (heroHealth <= 90)
		heroHealthbar->SetVisibility(true, true);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemySoldier::Destroyed()
{
	if(m_gun)
		m_gun->Destroy();
	Super::Destroyed();
}

