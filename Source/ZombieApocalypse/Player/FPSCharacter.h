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




	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void SetupGun();
	
	
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
	TSubclassOf<AGun> StartingGunClass;
	
	
	// Will be empty, so we can use this point as where the gun should spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS_PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;
	
};
