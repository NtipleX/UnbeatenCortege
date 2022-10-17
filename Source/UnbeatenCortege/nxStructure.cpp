#include "nxStructure.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

AnxStructure::AnxStructure() : m_health(100.f)
{
	//Creation
	structBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	structMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	structHealthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	
	//Attachment
	structBox->SetupAttachment(RootComponent);
	structMesh->SetupAttachment(structBox);
	structHealthbar->SetupAttachment(structBox);

	//Positioning
	structBox->SetRelativeLocation(FVector::ZeroVector);
	structMesh->SetRelativeLocation(FVector::ZeroVector);
	structHealthbar->SetRelativeLocation(FVector(0, 0, 125));

	//Configuration
	structBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	structBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	structBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	structBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	structHealthbar->SetWidgetSpace(EWidgetSpace::Screen);
	structHealthbar->SetDrawSize(FVector2D(60, 10));
	structHealthbar->SetVisibility(false, false);

}

void AnxStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

void AnxStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AnxStructure::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	m_health -= DamageAmount;
	structHealthbar->SetVisibility(true, true);
	if (m_health <= 0)
	{
		destroyed.Broadcast();
		Destroy();
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}