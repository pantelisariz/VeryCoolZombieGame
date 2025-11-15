
#include "..\PlayerCharacter/PawnOverlord.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

APawnOverlord::APawnOverlord()
{
	bShowMouseCursor = true;
}

void APawnOverlord::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	};

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (Subsystem) {
		Subsystem->AddMappingContext(DefaultInputMappingContext, 0);

	};

}
