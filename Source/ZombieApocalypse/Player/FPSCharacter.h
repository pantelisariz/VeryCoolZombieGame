// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZombieApocalypse/Weapon/Gun/Gun.h"
#include "ZombieApocalypse/HUD/PlayerStatHUD.h"
#include "ZombieApocalypse/Weapon/MeleeWeapon.h"
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
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	void SpawnGun(TSubclassOf<AGun> GunWeaponClass);
	void SpawnMeleeWeapon(TSubclassOf<AMeleeWeapon> MeleeWeaponClass);
	
	
	
	
	
	
	UFUNCTION()
	void ChangeCash(int32 CashChangeValue);	
	UFUNCTION()
	void ChangeHealth(int32 HealthChangeValue);
	UFUNCTION()
	void ChangeAmmo(int32 AmmoChangeValue);	

	UFUNCTION()
	void Purchase();
	UFUNCTION()
	void SpendMoney(int32 Price);
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerStatHUD> PlayerInfoHUDClass;
	UPROPERTY()
	TObjectPtr<UPlayerStatHUD> PlayerInfoHUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Stats", meta = (AllowPrivateAccess = "true", DisplayName = "Health (hp)"))
	int32 MaxHealth;
	int32 CurrentHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Stats", meta = (AllowPrivateAccess = "true", ForceUnits = "cm/s"))
	float RunSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Stats", meta = (AllowPrivateAccess = "true", ForceUnits = "cm/s"))
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Stats", meta = (AllowPrivateAccess = "true", DisplayName = "Cash ($)"))
	int32 Cash;
	
	
	
	
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Gun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> StartingGunClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Gun", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TSubclassOf<AGunAttachment>> StartingGunAttachmentClasses;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Gun", meta = (AllowPrivateAccess = "true"))
	AGun* CurrentGun;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Melee", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMeleeWeapon> StartingMeleeClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Melee", meta = (AllowPrivateAccess = "true"))
	AMeleeWeapon* CurrentMeleeWeapon;
	
	
	
	
	// Will be empty, so we can use this point as where the gun should spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Gun", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter|Melee", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeleeWeaponPlacementPoint;
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

};
