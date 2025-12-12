// Copyright University of Inland Norway


#include "PurchasableGun.h"

#include "Kismet/GameplayStatics.h"

APurchasableGun::APurchasableGun()
{
	GunPlacementPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunPlacementPoint"));
	GunPlacementPoint -> SetupAttachment(Mesh);	
	
	/*
	TextBlock = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextBlock"));
	TextBlock -> SetupAttachment(Mesh);	
	*/
	
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider -> SetupAttachment(Mesh);
	SphereCollider -> SetSphereRadius(300.f);
	
	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidget -> SetupAttachment(Mesh);
	
	
	PurchasableGunClass = nullptr;
	PurchasableGun = nullptr;
	PurchasableGunInfoHUDClass = nullptr;
	
	
	RespawnStatHUD();
}

void APurchasableGun::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	SpawnPurchasableGun();
	SetupStatHUD();
	*/
	
	CreatePurchasableGun();
	if (PurchasableGunInfoHUD)
	{
		SetStatsToGun();
		SetHUDVariables();
	}
	
	TArray<FString> StartingGunAttachmentClassesKeys;
	StartingGunAttachmentClasses.GetKeys(StartingGunAttachmentClassesKeys);
	
	for (FString AttachmentSlotName : StartingGunAttachmentClassesKeys)
	{
		for (UGunAttachmentSlotComponent* GunAttachmentSlot : PurchasableGun -> AttachmentSlots)
		{
			UE_LOG(LogTemp, Warning, TEXT("AttachmentSlot name: %s %s"), *AttachmentSlotName, *GunAttachmentSlot -> GetName() );
			
			
			if (GunAttachmentSlot -> GetName() != AttachmentSlotName)
			{
				continue;
			}
			GunAttachmentSlot -> CurrentAttachmentClass = StartingGunAttachmentClasses[AttachmentSlotName];
			GunAttachmentSlot -> CreateAttachment();
			
		
		}
	}
	SetGunStatsToStats();
	SetHUDVariables();
}




void APurchasableGun::CreatePurchasableGun()
{
	
	if (not PurchasableGunClass)
	{
		return;
	}
	PurchasableGun = GetWorld() -> SpawnActor<AGun>(PurchasableGunClass, FVector(0,0,0), FRotator(0,0,0));
	if (not PurchasableGun)
	{
		return;
	}
	SpawnPurchasableGun();
}



void APurchasableGun::SpawnPurchasableGun()
{
	PurchasableGun = GetWorld() -> SpawnActor<AGun>(PurchasableGunClass, FVector(0,0,0), FRotator(0,0,0));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	PurchasableGun -> AttachToComponent(GunPlacementPoint, AttachmentRules);
	
	
	
	SetupPurchasableGun();
}



void APurchasableGun::SetGunStatsToStats()
{
	GunTypeInText = PurchasableGun -> WeaponTypeInText;
	Damage = PurchasableGun -> Damage;
	FireRate = PurchasableGun -> FireRate;
	Range = PurchasableGun -> Range;
	ReloadTime = PurchasableGun -> ReloadTime;
	MagazineCapacity = PurchasableGun -> MagazineCapacity;
	MaxCarryAmmo = PurchasableGun -> MaxCarryAmmo;
	BulletPerAmmo = PurchasableGun -> BulletPerAmmo;
	AmmoUsedPerShot = PurchasableGun -> AmmoUsedPerShot;
}



void APurchasableGun::SetStatsToGun()
{
	PurchasableGun -> WeaponTypeInText = GunTypeInText;
	PurchasableGun -> Damage = Damage;
	PurchasableGun -> FireRate = FireRate;
	PurchasableGun -> Range = Range;
	PurchasableGun -> ReloadTime = ReloadTime;
	PurchasableGun -> MagazineCapacity = MagazineCapacity;
	PurchasableGun -> MaxCarryAmmo = MaxCarryAmmo;
	PurchasableGun -> BulletPerAmmo = BulletPerAmmo;
	PurchasableGun -> AmmoUsedPerShot = AmmoUsedPerShot;
}



void APurchasableGun::SetupPurchasableGun()
{
	SetStatsToGun();	
	
	if (not PurchasableGunInfoHUD)
	{
		SetupStatHUD();
		return;
	}
	
	SetHUDVariables();
	
	/*
	FText TextToDisplay = FText::FromString( FString::Printf(TEXT("Damage: %d \n Fire Rate: %.2f \n Range: %.2f \n  Reload Time: %.2f \n Magazine Capacity: %d \n Max Carry Ammo: %d \n Bullet per Ammo: %d \n Ammo Used Per Shot: %d"), Damage, FireRate, Range, ReloadTime, MagazineCapacity, MaxCarryAmmo, BulletPerAmmo, AmmoUsedPerShot));
	TextBlock -> SetText(TextToDisplay);
	*/
}



void APurchasableGun::SetupStatHUD()
{
	if (not PurchasableGunInfoHUDClass)
	{
		return;
	}
	
	PurchasableGunInfoHUD = CreateWidget<UPurchasableGunInfoHUD>(GetWorld(), *(PurchasableGunInfoHUDClass));
	
	check(PurchasableGunInfoHUD);
	SetHUDVariables();
}

void APurchasableGun::RespawnStatHUD()
{
	if (not PurchasableGunInfoHUDClass)
	{
		return;
	}
	
	PurchasableGunInfoHUD = CreateWidget<UPurchasableGunInfoHUD>(GetWorld(), *(PurchasableGunInfoHUDClass));
	check(PurchasableGunInfoHUD);
	
	InfoWidget -> SetWidget(PurchasableGunInfoHUD);
	SetGunStatsToStats();
	PurchasableGunInfoHUD -> SetGun(PurchasableGun);
	PurchasableGunInfoHUD -> SetGunInfo();
}


void APurchasableGun::SetHUDVariables()
{
	InfoWidget -> SetWidget(PurchasableGunInfoHUD);
	SetGunStatsToStats();
	PurchasableGunInfoHUD -> SetGun(PurchasableGun);
	PurchasableGunInfoHUD -> SetGunInfo();
}
