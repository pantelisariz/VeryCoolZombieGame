// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "PurchasableActor.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "../HUD/PurchasableGunInfoHUD.h"
#include "Components/WidgetComponent.h"
#include "ZombieApocalypse/Gun/Gun.h"
#include "PurchasableGun.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API APurchasableGun : public APurchasableActor
{
	GENERATED_BODY()
	
	
public:
	APurchasableGun();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	/*
	 * Source for function under:
	 * Cody. (2024, March 18). PostEditChangeProperty for visualizing C++ changes in an artist-friendly way. Retrieved from Medium: 
	 * https://medium.com/@codyjmccarty/posteditchangeproperty-for-visualizing-c-changes-in-an-artist-friendly-way-7e514332eab0
	 */
	
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void SetupGunOnClassChange(FPropertyChangedEvent& PropertyChangedEvent);
	void SetAllGunVariables(FPropertyChangedEvent& PropertyChangedEvent);
	
	void SetupGunHUDOnClassChange(FPropertyChangedEvent& PropertyChangedEvent);
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;
	UPROPERTY()
	AGun* PurchasableGun;
	
	// This was previously used for setting text
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TextBlock;
	*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	USphereComponent* SphereCollider;
	
	
	
public:
	void CreatePurchasableGun();
	void SpawnPurchasableGun();
	void SetGunStatsToStats();
	void SetStatsToGun();
	void SetupPurchasableGun();
	
	void SetupStatHUD();
	
	void SetHUDVariables();
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> PurchasableGunClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	bool bAutoCreateGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPurchasableGunInfoHUD> PurchasableGunInfoHUDClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PurchasableGun|UI", meta = (AllowPrivateAccess = "true"))
	UPurchasableGunInfoHUD* PurchasableGunInfoHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* InfoWidget;

	
	
	
	
	// Gun variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats",  meta = (AllowPrivateAccess = "true"))
	FString GunTypeInText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	float FireRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	float ReloadTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxCarryAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 BulletPerAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 AmmoUsedPerShot;
	
};
