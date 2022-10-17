#include "nxGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MapOffensive.h"
#include "nxStructure.h"

void AnxGameMode::StartPlay()
{
	Super::StartPlay();
	mapOffensive = dynamic_cast<AMapOffensive*>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AMapOffensive::StaticClass()));
	auto stab = Cast<AnxStructure>(UGameplayStatics::GetActorOfClass(GetWorld(), mainStab.Get()));
	stab->destroyed.AddDynamic(this, &AnxGameMode::GameOverEvent);
}

