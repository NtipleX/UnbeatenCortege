#include "AIBerserk.h"
#include "Components/WidgetComponent.h"
#include "Takeable.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

AAIBerserk::AAIBerserk(): Health(50.f)
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
	Health -= DamageAmount;

	if (Health <= 0)
	{
		m_slot1->Destroy();
		Destroy();
	}
	
	return 0.f;
}

void AAIBerserk::stab()
{
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("MySection"), stabMontage);
	GetMesh()->GetAnimInstance()->Montage_Play(stabMontage);
}