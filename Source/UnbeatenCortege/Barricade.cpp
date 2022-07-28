#include "Barricade.h"
#include "TraceHelpers.h"

// Sets default values
ABarricade::ABarricade(): m_isDamaged (false), m_debris(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	block1 = CreateDefaultSubobject<UWall>(TEXT("Block1"));
	block2 = CreateDefaultSubobject<UWall>(TEXT("Block2"));
	block3 = CreateDefaultSubobject<UWall>(TEXT("Block3"));
	block4 = CreateDefaultSubobject<UWall>(TEXT("Block4"));

	block1->SetupAttachment(root);
	block2->SetupAttachment(root);
	block3->SetupAttachment(root);
	block4->SetupAttachment(root);
	block1->SetRelativeLocation(FVector::ZeroVector);
	block2->SetRelativeLocation(FVector::ZeroVector);
	block3->SetRelativeLocation(FVector::ZeroVector);
	block4->SetRelativeLocation(FVector::ZeroVector);


}

// Called when the game starts or when spawned
void ABarricade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarricade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABarricade::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (block1->GetHealth() + block2->GetHealth() + block3->GetHealth() + block4->GetHealth() <= 2)
	{
		Destroy();
		return 0;
	}
	
	if (!m_isDamaged)
	{
		if(!block1->GetHealth() || !block2->GetHealth() || !block3->GetHealth() || !block4->GetHealth())
		{
			m_debris = GetWorld()->SpawnActor<AActor>(debris, GetActorLocation(), FRotator(0,0,0));
			m_isDamaged = true;
		}

	}

	return 0;
}

void ABarricade::Destroyed()
{
	if(m_debris)
		m_debris->Destroy();
	Super::Destroyed();
}