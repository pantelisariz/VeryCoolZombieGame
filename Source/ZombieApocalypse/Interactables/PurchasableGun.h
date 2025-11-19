// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "PurchasableActor.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableActor", meta = (AllowPrivateAccess = "true"))
	AGun* PurchasableGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableActor", meta = (AllowPrivateAccess = "true"))
	float Value1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableActor", meta = (AllowPrivateAccess = "true"))
	float Value2;
	
};
