#include "nxHero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "nxWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "nxAnimator.h"
#include "Kismet/GameplayStatics.h"
#include "nxGameMode.h"
#include "nxHUD.h"

AnxHero::AnxHero()
	: m_gun(nullptr)
	, m_animator(nullptr)
	, heroHealth(100.f)
	, heroAlive(true)
	, isEnemy(true)
	, canShoot(true)
{
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeroCameraComp"));
	heroHealthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeroWidgetComp"));
	camera->SetupAttachment(RootComponent);
	heroHealthbar->SetupAttachment(RootComponent);
	heroHealthbar->SetRelativeLocation(FVector(0, 0, 165));
	camera->SetRelativeLocation(FVector(-250, 0, 0));

	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	auto movm = GetCharacterMovement();
	movm->bOrientRotationToMovement = false;
	movm->RotationRate = FRotator(0, 1700, 0);
	movm->MaxAcceleration = 100'000.f;
	heroHealthbar->SetWidgetSpace(EWidgetSpace::Screen);
	heroHealthbar->SetDrawSize(FVector2D(60, 10));
	heroHealthbar->SetVisibility(false, false);

}

void AnxHero::BeginPlay()
{
	Super::BeginPlay();
	m_animator = Cast<UnxAnimator>(GetMesh()->GetAnimInstance());
	
	/// Spawning & attaching starting gun for hero
	if (startingWeapon)
	{
		FAttachmentTransformRules transformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			true
		);

		m_gun = GetWorld()->SpawnActor<AnxWeapon>(startingWeapon, FTransform());
		if (m_gun)
			m_gun->AttachToComponent(GetMesh(), transformRules, FName("SKT_Pistol"));
		else TRACE_WARNING(LogTemp, "Failed to spawn starting gun");
	}
	else TRACE_WARNING(LogTemp, "Starting gun for hero not specified");
}

void AnxHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_moveForward && m_moveSide)
	{
		m_moveForward /= 1.7;
		m_moveSide /= 1.7;
	}
	AddMovementInput(FVector(m_moveForward, m_moveSide, 0), fabs(m_moveForward) + fabs(m_moveSide), false);
}

void AnxHero::SetupPlayerInputComponent(UInputComponent* pic)
{
	Super::SetupPlayerInputComponent(pic);
	pic->BindAxis("MoveForward", this, &AnxHero::moveForward);
	pic->BindAxis("MoveSide", this, &AnxHero::moveSide);
}

float AnxHero::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	heroHealth -= DamageAmount;
	m_animator->Montage_Play(m_animator->animMontage);

	if (heroHealth <= 0)
	{
		//! heroAlive = false;
		auto gm = dynamic_cast<AnxGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
		auto hud = dynamic_cast<AnxHUD*>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		hud->OnConsumeLife.Broadcast();
		//gm->GameOverEvent();

	}

	if (heroHealth <= 90)
		heroHealthbar->SetVisibility(true, true);
	else heroHealthbar->SetVisibility(false, false);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

void AnxHero::moveForward(float axis)
{
	m_moveForward = axis * 0.55;
}

void AnxHero::moveSide(float axis)
{
	m_moveSide = axis * 0.55;
}

void AnxHero::fireWeapon(FVector pointOnMap)
{
	if(!canShoot)
		return;

	/// Shoot to direction
	FVector start = GetActorLocation();
	pointOnMap.Z = start.Z;
	FVector vectorDirection = pointOnMap - start;
	bool fire = false;
	if (m_gun)
	{
		fire = m_gun->fireWeapon(vectorDirection, GetActorLocation());
	}
	if (fire && m_animator->fireGun)
	{
		m_animator->Montage_JumpToSection(FName("MySection"), m_animator->fireGun);
		m_animator->Montage_Play(m_animator->fireGun);
	}
}

float AnxHero::getHeroHealth() const
{
	return heroHealth;
}

void AnxHero::setHeroHealth(float heatlh)
{
	heroHealth = heatlh;
}

FGenericTeamId AnxHero::GetGenericTeamId() const
{
	return FGenericTeamId(1);
}