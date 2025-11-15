
#include "..\PlayerCharacter/PawnOverlord.h"
#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

APawnOverlord::APawnOverlord()
{
	bShowMouseCursor = true;
}

void APawnOverlord::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (DefaultInputMappingContext.IsNull())
    {
        UE_LOG(LogTemp, Warning, TEXT("No Input Mapping Context assigned!"));
        return;
    }

    UInputMappingContext* MappingContext = DefaultInputMappingContext.LoadSynchronous();
    if (!MappingContext)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Input Mapping Context!"));
        return;
    }

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(MappingContext, 0);
        UE_LOG(LogTemp, Display, TEXT("Input mapping context added."));
    }
}