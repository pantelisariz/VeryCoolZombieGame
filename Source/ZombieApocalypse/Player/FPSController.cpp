// Copyright University of Inland Norway


#include "FPSController.h"
#include "GameFramework/PlayerController.h"


AFPSController::AFPSController()
{
}

void AFPSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem -> AddMappingContext(DefaultInputMappingContext, 0);
		UE_LOG(LogTemp, Warning, TEXT("Added DefaultInputMappingContext"));

	}
}