// Copyright University of Inland Norway


#include "FPSController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include  "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


AFPSController::AFPSController()
{
}

void AFPSController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	if (not EnhancedInputComponent)
	{
		return;
	}
	
	// Set up user input
	
	EnhancedInputComponent -> BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &AFPSController::Move);
	
	EnhancedInputComponent -> BindAction(LookAction.Get(), ETriggerEvent::Triggered, this, &AFPSController::Look);
	
	
	EnhancedInputComponent -> BindAction(JumpAction.Get(), ETriggerEvent::Started, this, &AFPSController::JumpStart);
	EnhancedInputComponent -> BindAction(JumpAction.Get(), ETriggerEvent::Completed, this, &AFPSController::JumpEnd);
	
	EnhancedInputComponent -> BindAction(RunAction.Get(), ETriggerEvent::Started, this, &AFPSController::RunStart);
	EnhancedInputComponent -> BindAction(RunAction.Get(), ETriggerEvent::Completed, this, &AFPSController::RunEnd);
	
	EnhancedInputComponent -> BindAction(InteractAction.Get(), ETriggerEvent::Triggered, this, &AFPSController::Interact);
	
	EnhancedInputComponent -> BindAction(ReloadAction.Get(), ETriggerEvent::Triggered, this, &AFPSController::Reload);
	
	EnhancedInputComponent -> BindAction(FireAction.Get(), ETriggerEvent::Started, this, &AFPSController::FireStart);
	EnhancedInputComponent -> BindAction(FireAction.Get(), ETriggerEvent::Completed, this, &AFPSController::FireEnd);
	
	EnhancedInputComponent -> BindAction(PauseAction.Get(), ETriggerEvent::Completed, this, &AFPSController::TogglePause);
	

	UE_LOG(LogTemp, Warning, TEXT("Added DefaultInputMappingContext"));
	
}



void AFPSController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("Controller possessed Player"));
	
	
	FPSCharacter = Cast<AFPSCharacter>(InPawn);
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem -> AddMappingContext(CurrentMappingContext.Get(), 0);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Cant get InputLocalPlayerSubsystem"));
	
	
}




void AFPSController::Move(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Move"));
	
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	FPSCharacter -> AddMovementInput(ForwardDirection, MovementVector.Y);
	FPSCharacter -> AddMovementInput(RightDirection, MovementVector.X);
	
}

void AFPSController::Look(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Warning, TEXT("Look"));
	
	const FVector2d LookAxisVector = Value.Get<FVector2d>();
	
	FPSCharacter -> AddControllerYawInput(LookAxisVector.X);
	FPSCharacter -> AddControllerPitchInput(LookAxisVector.Y);
}

void AFPSController::JumpStart()
{
	FPSCharacter -> Jump();
}

void AFPSController::JumpEnd()
{
	FPSCharacter -> StopJumping();
}

void AFPSController::RunStart()
{
	FPSCharacter -> GetCharacterMovement() -> MaxWalkSpeed = FPSCharacter -> RunSpeed;
}

void AFPSController::RunEnd()
{
	FPSCharacter -> GetCharacterMovement() -> MaxWalkSpeed = FPSCharacter -> WalkSpeed;
}

void AFPSController::FireStart()
{
	if (FPSCharacter)
	{
		FPSCharacter->CurrentGun->StartFire();
	}
}

void AFPSController::FireEnd()
{
	if (FPSCharacter)
	{
		FPSCharacter->CurrentGun->EndFire();
	}
}

void AFPSController::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading in controller"));
	
	if (FPSCharacter and not FPSCharacter -> CurrentGun -> bIsReloading and FPSCharacter -> CurrentGun -> CurrentMagazineAmmo != FPSCharacter -> CurrentGun -> MagazineCapacity)
	{
		FPSCharacter->CurrentGun->StartReloading();
	}
	
}

void AFPSController::TogglePause()
{
	if (bIsPaused)
	{
		bIsPaused = false;
		// Unpause the game
		SetPause(false);
		// Return game input
		bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
	else
	{

		// Pause the game
		SetPause(true);
		bIsPaused = true;
		// Free mouse cursor and UI input
		bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		//it was used for pause might be useful for score
		//InputMode.SetWidgetToFocus(PauseMenuWidget->TakeWidget());
		//InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);

	}
	
}


void AFPSController::Interact()
{
	
}

