// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieApocalypse/HUD/GunInfoHUD.h"
#include "Gun.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void StartFire();
	void EndFire();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGunInfoHUD> GunInfoHUDClass;
	UPROPERTY()
	TObjectPtr<UGunInfoHUD> GunInfoHUD;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 FireRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 Range;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 ReloadTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmoCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmoCount;

};
