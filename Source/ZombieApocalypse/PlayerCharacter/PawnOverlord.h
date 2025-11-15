// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnOverlord.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API APawnOverlord : public APlayerController
{
	GENERATED_BODY()
public:
	APawnOverlord();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAcces = true))
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;


protected:

	virtual void SetupInputComponent() override;
};
