// Copyright University of Inland Norway


#include "PurchasableGunInfoHUD.h"

void UPurchasableGunInfoHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPurchasableGunInfoHUD::SetGun(AGun* GunToSet)
{
	CurrentGun = GunToSet;
}

AGun* UPurchasableGunInfoHUD::GetGun()
{
	return CurrentGun;
}

void UPurchasableGunInfoHUD::SetGunInfo()
{
	FText TextToDisplay = FText::FromString( FString::Printf(TEXT("Damage: %d \n Fire Rate: %.2f \n Range: %.2f \n  Reload Time: %.2f \n Magazine Capacity: %d \n Max Carry Ammo: %d \n Bullet per Ammo: %d \n Ammo Used Per Shot: %d"), CurrentGun -> Damage, CurrentGun -> FireRate, CurrentGun -> Range, CurrentGun -> ReloadTime, CurrentGun -> MagazineCapacity, CurrentGun -> MaxCarryAmmo, CurrentGun -> BulletPerAmmo, CurrentGun -> AmmoUsedPerShot));
	GunInfoText -> SetText(TextToDisplay);
}


