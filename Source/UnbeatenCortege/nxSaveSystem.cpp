// Conquested Path. All rights reserved.


#include "nxSaveSystem.h"
#include "Kismet/GameplayStatics.h"

void UnxSaveSystem::SaveProgress(int32 money)
{
	UnxSaveSystem* saveObject = dynamic_cast<UnxSaveSystem*>(UGameplayStatics::CreateSaveGameObject(UnxSaveSystem::StaticClass()));

	saveObject->money = money;
	SaveEditProgress(saveObject);
}

UnxSaveSystem* UnxSaveSystem::RetriveProgress()
{
	UnxSaveSystem* loadObject = dynamic_cast<UnxSaveSystem*>(UGameplayStatics::LoadGameFromSlot(FString("Slot1"), 0));
	return loadObject;
}

void UnxSaveSystem::MakePurchase(EPurchaseProduct Product, int32 price)
{
	UnxSaveSystem* handle = RetriveProgress();
	handle->money -= price;
	handle->purchases.Add(Product);

	SaveEditProgress(handle);
}

void UnxSaveSystem::SaveEditProgress(UnxSaveSystem* obj)
{
	UGameplayStatics::SaveGameToSlot(obj, FString("Slot1"), 0);
}