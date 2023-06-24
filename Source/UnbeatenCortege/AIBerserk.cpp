#include "AIBerserk.h"
#include "Components/WidgetComponent.h"
#include "Takeable.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"
#include "AITypes.h"
#include "Components/CapsuleComponent.h"
#include "nxHUD.h"
#include "Kismet/GameplayStatics.h"


AAIBerserk::AAIBerserk(): Health(50.f), m_sinkCounter(0)
{
	PrimaryActorTick.bCanEverTick = true;
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetRelativeLocation(FVector(0,0,115));
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawSize(FVector2D(60, 10));
	HealthBar->SetVisibility(false, false);
}

void AAIBerserk::BeginPlay()
{
	Super::BeginPlay();
	if (slot1)
	{
		m_slot1 = GetWorld()->SpawnActor<ATakeable>(slot1.Get(), FTransform());
		m_slot1->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("TakeableSocket"));
		m_slot1->SetActorRelativeTransform(slot1.GetDefaultObject()->MeshToSocketTransform);
	}
}

void AAIBerserk::Tick(float delta)
{
	Super::Tick(delta);
}

FGenericTeamId AAIBerserk::GetGenericTeamId() const
{
	return FGenericTeamId(2);
}

void AAIBerserk::SetupPlayerInputComponent(UInputComponent* PIC)
{
	Super::SetupPlayerInputComponent(PIC);
}

float AAIBerserk::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HealthBar->SetVisibility(true, true);
	if (Health > 0)
		Health -= DamageAmount;
	else
		return 0.f;

	OnEnemyHit.Broadcast();

	if (Health <= 0)
	{
		HealthBar->SetVisibility(false, false);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetController()->StopMovement();
		GetController()->UnPossess();
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("MySection"), dieMontage);
		GetMesh()->GetAnimInstance()->Montage_Play(dieMontage);
		GetWorldTimerManager().SetTimer(m_sinkingDeath, this, &AAIBerserk::sinkBody, 3, false, 3);
		auto hud = dynamic_cast<AnxHUD*>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		hud->OnAwardCoins.Broadcast(2);
		OnSoldierDead.Broadcast();
	}
	
	return 0.f;
}

void AAIBerserk::stab()
{
	
	if(FMath::RandBool())
	{
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("MySection"), stabMontage);
		GetMesh()->GetAnimInstance()->Montage_Play(stabMontage);
	}
	else
	{
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("MySection"), kickMontage);
		GetMesh()->GetAnimInstance()->Montage_Play(kickMontage);
	}
}

void AAIBerserk::sinkBody()
{
	if (m_sinkCounter++ < 6)
	{
		GetWorldTimerManager().SetTimer(m_sinkingDeath, this, &AAIBerserk::sinkBody, 0.35, false, 0.35);
		AddActorLocalOffset(FVector(0, 0, -2.75));
	}
}