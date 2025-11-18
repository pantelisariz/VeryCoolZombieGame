// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "FPSController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API AFPSController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSController();
	
protected:
	virtual void SetupInputComponent() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultInputMappingContext;
};
