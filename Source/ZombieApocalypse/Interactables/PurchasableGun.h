// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "PurchasableActor.h"
#include "Components/TextRenderComponent.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;
	UPROPERTY()
	AGun* PurchasableGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TextBlock;
	
	
	
public:
	void SpawnPurchasableGun();
	
	void SetupPurchasableGun();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> GunType;
	
	
	// Gun variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
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
	int32 MaxAmmoCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableGun|Stats", meta = (AllowPrivateAccess = "true"))
	int32 AmmoUsedPerShot;
	
	
};
