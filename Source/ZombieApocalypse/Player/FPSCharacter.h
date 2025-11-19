// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZombieApocalypse/Gun/Gun.h"
#include "ZombieApocalypse/HUD/PlayerStatHUD.h"
#include "FPSCharacter.generated.h"


UCLASS()
class ZOMBIEAPOCALYPSE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	/*   stuff for shooting  */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 25.f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 10000.f;

	//shots per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 1.f;

	//ray casting for shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	//is the player holding down the fire button
	bool bIsFiring = false;

	// Probably need this to handle automatic fire
	FTimerHandle TimerHandle_AutoFire;

	//Functions for shooting logic
	//this one is for the ray casting
	void FireShot();
	//had to move 2 functions to public to be able to call them from the controller
	/*   end stuff for shooting  */

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerStatHUD> PlayerInfoHUDClass;
	UPROPERTY()
	TObjectPtr<UPlayerStatHUD> PlayerInfoHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true", ForceUnits = "hp"))
	int32 MaxHealth;
	int32 CurrentHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true", ForceUnits = "cm/s"))
	float RunSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true", ForceUnits = "cm/s"))
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true", ForceUnits = "$"))
	int32 Cash;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	AGun* CurrentGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> StartingGun;
	
	
	// Will be empty, so we can use this point as where the gun should spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;

	//The stuff i had to move to public to be able to call from controller
	//This will be called when the player presses the fire button
	void StartFire();
	//duh
	void StopFire();

};
