// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZombieApocalypse/Gun/Gun.h"
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
	
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
	

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	int32 Cash;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	AGun* CurrentGun;
	
	
	// Will be empty, so we can use this point as where the gun should spawn in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunPlacementPoint;
	

};
