// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Attachments/GunAttachment.h"
#include "Attachments/GunAttachmentSlotComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "ZombieApocalypse/HUD/CombatHUD.h"
#include "ZombieApocalypse/Weapon/Weapon.h"
#include "Gun.generated.h"




UCLASS()
class ZOMBIEAPOCALYPSE_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual void OnConstruction(const FTransform& Transform) override;
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	
	
	//Functions for shooting logic
	//this one is for the ray casting
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
	FTimerHandle TimerHandle_Reload;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	//The stuff i had to move to public to be able to call from controller
	//This will be called when the player presses the fire button
	void StartFire();
	void EndFire();
	
	void StartReloading();

	virtual void AddCombatHUD() override;
	

	
	// Gun Variables
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	float FireRate;
	float TimeBetweenShots;
	float TimeLastShot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	float ReloadTime;
	bool bIsReloading;
	float ReloadProgress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;
	int32 CurrentMagazineAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 CurrentCarryAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxCarryAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 BulletPerAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 AmmoUsedPerShot;
	
	
	// Attachments
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Attachment", meta = ( AllowPrivateAccess="true"))
	TArray<UGunAttachmentSlotComponent*> AttachmentSlots;
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Weapon")
	void GetAllAttachments();
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Weapon")
	void LogAllAttachments();
	
	
};
