#include "EnemySoldier.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "TraceHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/CapsuleComponent.h"

AEnemySoldier::AEnemySoldier() : heroHealth(100.f), m_lastTimeShot(0.f), canShoot(true), m_sinkCounter(0)
{
	PrimaryActorTick.bCanEverTick = true;
	offensivity.Level = 1;
	offensivity.Experience = 0;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	heroHealthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeroWidgetComp"));
	heroHealthbar->SetupAttachment(RootComponent);
	heroHealthbar->SetRelativeLocation(FVector(0, 0, 115));
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
	m_animator = dynamic_cast<UEnemySoldierAnimator*>(GetMesh()->GetAnimInstance());
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
	if(canShoot && GetWorld()->TimeSeconds - m_lastTimeShot >= weapon.GetDefaultObject()->reloadTime*1.2)
	{
		m_lastTimeShot = GetWorld()->TimeSeconds;
		GetWorld()->SpawnActor<AActor>(ammoOverride.Get(), GetActorLocation()-FVector(0,0,0), GetActorRotation(), FActorSpawnParameters());
		UGameplayStatics::PlaySound2D(GetWorld(), weapon.GetDefaultObject()->SoundFire);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), weapon.GetDefaultObject()->ParticleFire, m_gun->GetActorLocation());
		if(m_animator->fireGun)
		{
			m_animator->Montage_JumpToSection(FName("MySection"), m_animator->fireGun);
			m_animator->Montage_Play(m_animator->fireGun);
		}
	}
}

float 	AEnemySoldier::TakeDamage
(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	if (heroHealth < 0.f)
		return 0.f;

	heroHealth -= DamageAmount;

	if (m_animator->hitMontage)
	{
		m_animator->Montage_JumpToSection(FName("Default"), m_animator->hitMontage);
		m_animator->Montage_Play(m_animator->hitMontage);
	}

	if (heroHealth <= 90)
		heroHealthbar->SetVisibility(true, true);

	if (heroHealth <= 0)
	{
		heroHealthbar->SetVisibility(false, false);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AController* CON = GetController();
		CON->StopMovement();
		CON->UnPossess();
		CON->Destroy();
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("MySection"), dieMontage);
		GetMesh()->GetAnimInstance()->Montage_Play(dieMontage);
		GetWorldTimerManager().SetTimer(m_sinkingDeath, this, &AEnemySoldier::sinkBody, 2, false, 2);
	}

	
	OnEnemyHit.Broadcast();

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemySoldier::Destroyed()
{
	if(m_gun)
		m_gun->Destroy();
	Super::Destroyed();
}

void AEnemySoldier::sinkBody()
{
	if (m_sinkCounter++ < 9)
	{
		GetWorldTimerManager().SetTimer(m_sinkingDeath, this, &AEnemySoldier::sinkBody, 0.65, false, 0.65);
		AddActorLocalOffset(FVector(0, 0, -1.8));
	}
}
