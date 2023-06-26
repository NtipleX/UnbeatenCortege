// Conquested Path. All rights reserved.


#include "nxSaveSystem.h"
#include "Kismet/GameplayStatics.h"

void UnxSaveSystem::SaveProgress(int32 money)
{
	UnxSaveSystem* saveObject = dynamic_cast<UnxSaveSystem*>(UGameplayStatics::CreateSaveGameObject(UnxSaveSystem::StaticClass()));

	saveObject->money = money;
	UGameplayStatics::SaveGameToSlot(saveObject, FString("Slot1"), 0);
}

UnxSaveSystem* UnxSaveSystem::RetriveProgress()
{
	UnxSaveSystem* loadObject = dynamic_cast<UnxSaveSystem*>(UGameplayStatics::LoadGameFromSlot(FString("Slot1"), 0));
	return loadObject;
}



