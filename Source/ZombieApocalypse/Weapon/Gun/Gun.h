// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Attachments/GunAttachmentSlotComponent.h"
#include "GameFramework/Actor.h"
#include "ZombieApocalypse/HUD/GunCombatHUD.h"
#include "ZombieApocalypse/Weapon/Weapon.h"
#include "Gun.generated.h"




UCLASS()
class ZOMBIEAPOCALYPSE_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	
	
	//Functions for shooting logic
	//this one is for the ray casting
	void Fire();
	void FireShot();
	//had to move 2 functions to public to be able to call them from the controller
	/*   end stuff for shooting  */
	
	void FireShotStatChanges();
	
	void Reload();
	void FinishedReloading();
	
	
	
	//ray casting for shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	
	//is the player holding down the fire button
	bool bIsFiring = false;

	// Probably need this to handle automatic fire
	FTimerHandle TimerHandle_AutoFire;
	FTimerHandle TimerHandle_Fire;
	FTimerHandle TimerHandle_MultiShot;
	
	FTimerHandle TimerHandle_Reload;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	//The stuff i had to move to public to be able to call from controller
	//This will be called when the player presses the fire button
	void StartFire();
	void EndFire();
	
	void StartReloading();

	void AddCombatHUD();
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|UI")
	TSubclassOf<UGunCombatHUD> GunCombatHUDClass;
	UPROPERTY()
	UGunCombatHUD* GunCombatHUD;
	
	bool bHasGottenAllAttachments;

	
	// Gun Variables
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 Damage;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 DamageBeforeAttachments;


	/**
	 * Higher FireRate means the gun shoots faster
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	float FireRate;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	float FireRateBeforeAttachments;
	
	float TimeBetweenShots;
	float TimeLastShot;
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	float Range;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	float RangeBeforeAttachments;
	
	
	
	/**
	 * Lower ReloadTime means lower time to reload
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	float ReloadTime;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	float ReloadTimeBeforeAttachments;
	
	bool bIsReloading;
	float ReloadProgress;
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 MagazineCapacity;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 MagazineCapacityBeforeAttachments;
	
	int32 CurrentMagazineAmmo;
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 CurrentCarryAmmo;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 CurrentCarryAmmoBeforeAttachments;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 MaxCarryAmmo;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 MaxCarryAmmoBeforeAttachments;


	/**
	 * Amount of bullets shot per ammo
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 BulletPerAmmo;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 BulletPerAmmoBeforeAttachments;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 AmmoUsedPerShot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|AttachmentStats")
	int32 AmmoUsedPerShotBeforeAttachments;
	
	
	
	
	
	
	
	
	
	// Attachments
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Attachment")
	TArray<UGunAttachmentSlotComponent*> AttachmentSlots;
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Weapon")
	void GetAllAttachments();
	
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetupAttachmentStats(TMap<EGunStatType, float> Map);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddAttachmentStatsToGun(TMap<EGunStatType, FGunStatChange> AttachmentStatChanges);
	
	float AttachmentStatChange(FGunStatChange GunStatChange,  float ValueToSetToo);
	

	
	
	
};
