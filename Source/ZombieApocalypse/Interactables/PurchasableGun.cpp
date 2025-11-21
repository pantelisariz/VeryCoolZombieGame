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
	
	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidget -> SetupAttachment(Mesh);
	
	
	PurchasableGunClass = nullptr;
	PurchasableGun = nullptr;
	PurchasableGunInfoHUDClass = nullptr;
	
	
}

void APurchasableGun::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	SpawnPurchasableGun();
	SetupStatHUD();
	*/
	
	
}

void APurchasableGun::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	SetupGunOnClassChange(PropertyChangedEvent);
	
	/*
	if (not (PropertyChangedEvent.Property and 
PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(APurchasableGun, PurchasableGunInfoHUDClass)))
	{
		return;
	}
	*/
	
}



void APurchasableGun::SetupGunOnClassChange(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property and 
	PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(APurchasableGun, PurchasableGunClass))
	{
		if (not bAutoCreateGun)
		{
			return;
		}
		CreatePurchasableGun();
	}
}



void APurchasableGun::CreatePurchasableGun()
{
	if (PurchasableGun and PurchasableGun -> IsValidLowLevel())
	{
		PurchasableGun -> ConditionalBeginDestroy();
		PurchasableGun -> Destroy();
		PurchasableGun = nullptr;
	}
	
	if (not PurchasableGunClass)
	{
		return;
	}
	PurchasableGun = NewObject<AGun>(this, PurchasableGunClass);
	if (not PurchasableGun)
	{
		return;
	}
	PurchasableGun -> SetFlags(RF_Transactional);
	SpawnPurchasableGun();
}



void APurchasableGun::SpawnPurchasableGun()
{
	PurchasableGun = GetWorld() -> SpawnActor<AGun>(PurchasableGunClass, GunPlacementPoint -> GetRelativeLocation(), FRotator(0,0,0));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	PurchasableGun -> AttachToComponent(GunPlacementPoint, AttachmentRules);
	
	SetupPurchasableGun();
}



void APurchasableGun::SetupPurchasableGun()
{
	GunTypeInText = PurchasableGun -> GunTypeInText;
	Damage = PurchasableGun -> Damage;
	FireRate = PurchasableGun -> FireRate;
	Range = PurchasableGun -> Range;
	ReloadTime = PurchasableGun -> ReloadTime;
	MagazineCapacity = PurchasableGun -> MagazineCapacity;
	MaxCarryAmmo = PurchasableGun -> MaxCarryAmmo;
	BulletPerAmmo = PurchasableGun -> BulletPerAmmo;
	AmmoUsedPerShot = PurchasableGun -> AmmoUsedPerShot;
	
	/*
	PurchasableGun -> Damage = Damage;
	PurchasableGun -> FireRate = FireRate;
	PurchasableGun -> Range = Range;
	PurchasableGun -> ReloadTime = ReloadTime;
	PurchasableGun -> MagazineCapacity = MagazineCapacity;
	PurchasableGun -> MaxCarryAmmo = MaxCarryAmmo;
	PurchasableGun -> BulletPerAmmo = BulletPerAmmo;
	PurchasableGun -> AmmoUsedPerShot = AmmoUsedPerShot;
	*/
	
	
	
	if (not PurchasableGunInfoHUD)
	{
		SetupStatHUD();
		return;
	}
	
	
	InfoWidget -> SetWidget(PurchasableGunInfoHUD);
	PurchasableGunInfoHUD -> SetGun(PurchasableGun);
	PurchasableGunInfoHUD -> SetGunInfo();
	
	
	
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
	InfoWidget -> SetWidget(PurchasableGunInfoHUD);
	PurchasableGunInfoHUD -> SetGun(PurchasableGun);
	PurchasableGunInfoHUD -> SetGunInfo();
}
