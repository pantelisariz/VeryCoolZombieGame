// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "ZombieApocalypse/HUD/CombatHUD.h"
#include "Weapon.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void AddCombatHUD();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCombatHUD> CombatHUDClass;
	UPROPERTY()
	UCombatHUD* CombatHUD;
	
	TObjectPtr<UCameraComponent> PlayerCameraComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	FString WeaponTypeInText;
	

};
