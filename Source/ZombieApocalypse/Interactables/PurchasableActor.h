// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "PurchasableActor.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API APurchasableActor : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	APurchasableActor();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PurchasableActor", meta = (AllowPrivateAccess = "true"))
	int32 Cost;
	

	
};
