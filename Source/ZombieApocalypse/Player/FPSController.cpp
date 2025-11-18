// Copyright University of Inland Norway


#include "FPSController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include  "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"


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
	

	UE_LOG(LogTemp, Warning, TEXT("Added DefaultInputMappingContext"));
	
}



void AFPSController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	FPSCharacter = Cast<AFPSCharacter>(InPawn);
	
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (not InputLocalPlayerSubsystem)
	{
		return;
	}
	
	InputLocalPlayerSubsystem -> AddMappingContext(CurrentMappingContext.Get(), 0);
}




void AFPSController::Move(const FInputActionValue& Value)
{
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
}

void AFPSController::JumpStart()
{
}

void AFPSController::JumpEnd()
{
}

void AFPSController::RunStart()
{
}

void AFPSController::RunEnd()
{
}

void AFPSController::FireStart()
{
}

void AFPSController::FireEnd()
{
}

void AFPSController::Reload()
{
}

void AFPSController::Interact()
{
}

