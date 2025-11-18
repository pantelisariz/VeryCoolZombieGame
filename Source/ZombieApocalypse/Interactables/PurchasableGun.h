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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableActor", meta = (AllowPrivateAccess = "true"))
	AGun* PurchasableGun;
};
