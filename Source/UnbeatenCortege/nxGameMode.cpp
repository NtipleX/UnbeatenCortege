#include "nxGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MapOffensive.h"

void AnxGameMode::StartPlay()
{
	Super::StartPlay();
	mapOffensive = dynamic_cast<AMapOffensive*>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AMapOffensive::StaticClass()));
}