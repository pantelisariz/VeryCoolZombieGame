#include "..\PlayerCharacter/ControllerPawn.h"
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

class EnhancedInputComponent;

// Sets default values
AControllerPawn::AControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Attachments and Components */

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	/* Attachments and Components Completed */

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));


}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AControllerPawn::Move(const FInputActionValue& Value)
{
	const FVector2d MovementInput = Value.Get<FVector2D>();
	if(Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, MovementInput.Y);
		AddMovementInput(Right, MovementInput.X);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("IA_Move Activated"));
		}
	}
}


void AControllerPawn::Zoom(const FInputActionValue& Value)
{
	const float ZoomDirection = Value.Get<float>();

	float DesiredOrthoWidth = Camera->OrthoWidth + ZoomDirection * CameraZoomSpeed;
	DesiredOrthoWidth = FMath::Clamp(DesiredOrthoWidth, MinCameraZoom, MaxCameraZoom);
	Camera->SetOrthoWidth(DesiredOrthoWidth);
}

void AControllerPawn::UnitMove(const FInputActionValue& Value)
{

}

// Called every frame
void AControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AControllerPawn::Move );
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AControllerPawn::Zoom );
	}
}

