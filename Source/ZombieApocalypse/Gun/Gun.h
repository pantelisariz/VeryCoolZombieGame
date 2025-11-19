// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "ZombieApocalypse/HUD/GunInfoHUD.h"
#include "Gun.generated.h"


DECLARE_DELEGATE_OneParam(FZombieKilledDelegate, int32 /*CashChangeValue */);


UCLASS()
class ZOMBIEAPOCALYPSE_API AGun : public AActor
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
	void FireShot();
	//had to move 2 functions to public to be able to call them from the controller
	/*   end stuff for shooting  */
	
	void FireShotStatChanges();
	
	void Reload();
	
	
	
	//ray casting for shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	
	//is the player holding down the fire button
	bool bIsFiring = false;

	// Probably need this to handle automatic fire
	FTimerHandle TimerHandle_AutoFire;
	FTimerHandle TimerHandle_Fire;
	FTimerHandle TimerHandle_Reload;
	FTimerHandle TimerHandle_HUDReload;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	//The stuff i had to move to public to be able to call from controller
	//This will be called when the player presses the fire button
	void StartFire();
	void EndFire();
	
	void StartReloading();
	

	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGunInfoHUD> GunInfoHUDClass;
	UPROPERTY()
	UGunInfoHUD* GunInfoHUD;
	

	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float FireRate;
	float TimeBetweenShots;
	float TimeLastShot;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	float ReloadTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmoCount;
	int32 CurrentAmmoCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 AmmoUsedPerShot;
	bool bIsReloading;
	float ReloadProgress;
	
	
	

	TObjectPtr<UCameraComponent> PlayerCameraComponent;
	
	FZombieKilledDelegate CashGained;



};
