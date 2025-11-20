// Copyright University of Inland Norway


#include "PurchasableGun.h"

APurchasableGun::APurchasableGun()
{
	GunPlacementPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunPlacementPoint"));
	GunPlacementPoint -> SetupAttachment(Mesh);	
	
	TextBlock = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextBlock"));
	TextBlock -> SetupAttachment(Mesh);	
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(Mesh);
	
	
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
	PurchasableGun -> MagazineCapacity = MagazineCapacity;
	PurchasableGun -> MaxCarryAmmo = MaxCarryAmmo;
	PurchasableGun -> BulletPerAmmo = BulletPerAmmo;
	PurchasableGun -> AmmoUsedPerShot = AmmoUsedPerShot;
	
	FText TextToDisplay = FText::FromString( FString::Printf(TEXT("Damage: %d \n Fire Rate: %.2f \n Range: %.2f \n  Reload Time: %.2f \n Magazine Capacity: %d \n Max Carry Ammo: %d \n Bullet per Ammo: %d \n Ammo Used Per Shot: %d"), Damage, FireRate, Range, ReloadTime, MagazineCapacity, MaxCarryAmmo, BulletPerAmmo, AmmoUsedPerShot));
	TextBlock -> SetText(TextToDisplay);
}