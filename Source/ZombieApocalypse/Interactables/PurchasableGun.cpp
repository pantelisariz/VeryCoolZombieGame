// Copyright University of Inland Norway


#include "PurchasableGun.h"

APurchasableGun::APurchasableGun()
{
	GunPlacementPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunPlacementPoint"));
	GunPlacementPoint -> SetupAttachment(Mesh);	
	
	TextBlock = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextBlock"));
	TextBlock -> SetupAttachment(Mesh);	
	
	

}

void APurchasableGun::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPurchasableGun();
	
	
}



void APurchasableGun::SpawnPurchasableGun()
{
	PurchasableGun = GetWorld() -> SpawnActor<AGun>(GunType, GunPlacementPoint -> GetRelativeLocation(), FRotator(0,0,0));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	PurchasableGun -> AttachToComponent(GunPlacementPoint, AttachmentRules);
	
	SetupPurchasableGun();
}



void APurchasableGun::SetupPurchasableGun()
{
	PurchasableGun -> GunTypeInText = GunTypeInText;
	PurchasableGun -> Damage = Damage;
	PurchasableGun -> FireRate = FireRate;
	PurchasableGun -> Range = Range;
	PurchasableGun -> ReloadTime = ReloadTime;
	PurchasableGun -> MaxAmmoCount = MaxAmmoCount;
	PurchasableGun -> AmmoUsedPerShot = AmmoUsedPerShot;
	
	FText TextToDisplay = FText::FromString( FString::Printf(TEXT("Gun Type: %s \n Damage: %d \n Fire Rate: %.2f \n Range: %.2f \n Max Ammo Count: %d \n Reload Time: %.2f \n Ammo Used Per Shot: %d"), *GunTypeInText, Damage, FireRate, Range, MaxAmmoCount, ReloadTime, AmmoUsedPerShot));
	TextBlock -> SetText(TextToDisplay);
}