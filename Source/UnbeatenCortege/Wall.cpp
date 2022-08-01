#include "Wall.h"
#include "Materials/Material.h"
#include "TraceHelpers.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UWall::UWall() : m_health(2.f)
{
	/*wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wallMeshComp"));
	RootComponent = wallMesh;
	wallMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PrimaryActorTick.bCanEverTick = false;
	*/
	wallBox = CreateDefaultSubobject<UBoxComponent>(TEXT("wallBox"));
	wallBox->SetupAttachment(this);
	wallBox->SetRelativeLocation(FVector::ZeroVector);

	SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetCollisionResponseToChannels(ECR_Block);
	wallBox->SetWorldScale3D(FVector(1.8, 1.8, 8));
	wallBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	wallBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	wallBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

}





/*float UWall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!--m_health)
	{
		
	}
	else
	{
		wallMesh->SetMaterial(0, wallDarkenMaterial);
	}
	return m_health;
}
*/

void UWall::GetDamage()
{
	if (!--m_health)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), destroySound);
		SetHiddenInGame(true);
		wallBox->SetHiddenInGame(true);
		wallBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		//SetMaterial(0, darkenMaterial);
		if(Cast<UMaterialInstanceDynamic>(GetMaterial(0)))
			Cast<UMaterialInstanceDynamic>(GetMaterial(0))->SetScalarParameterValue(FName("Health"), 0.4f);
		else
			cLog("its not mateialInstanceDynamic..");
		

		UGameplayStatics::PlaySound2D(GetWorld(), hitSound);
	}
}

float UWall::GetHealth() const {
	return m_health;
}