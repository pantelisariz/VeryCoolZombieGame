// Copyright University of Inland Norway


#include "PurchasableGunInfoHUD.h"

void UPurchasableGunInfoHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPurchasableGunInfoHUD::Setup(AGun* GunToSet)
{
	SetGun(GunToSet);
	SetGunInfo();
}

void UPurchasableGunInfoHUD::SetGun(AGun* GunToSet)
{
	PurchasableGun = GunToSet;
}

AGun* UPurchasableGunInfoHUD::GetGun()
{
	return PurchasableGun;
}

void UPurchasableGunInfoHUD::SetGunInfo()
{
	FText TextToDisplay = FText::FromString( FString::Printf(TEXT("Damage: %d \n Fire Rate: %.2f \n Range: %.2f \n  Reload Time: %.2f \n Magazine Capacity: %d \n Max Carry Ammo: %d \n Bullet per Ammo: %d \n Ammo Used Per Shot: %d"), PurchasableGun -> Damage, PurchasableGun -> FireRate, PurchasableGun -> Range, PurchasableGun -> ReloadTime, PurchasableGun -> MagazineCapacity, PurchasableGun -> MaxCarryAmmo, PurchasableGun -> BulletPerAmmo, PurchasableGun -> AmmoUsedPerShot));
	GunInfoText -> SetText(TextToDisplay);
}


