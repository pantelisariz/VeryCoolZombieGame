// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API APistol : public AGun
{
	GENERATED_BODY()
	
public:
	APistol();

	
	
	
protected:
	virtual void BeginPlay() override;
};
