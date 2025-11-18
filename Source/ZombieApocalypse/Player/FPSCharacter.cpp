// Copyright University of Inland Norway


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
	// CameraArmComponent = nullptr;
	CameraComponent = nullptr;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	TObjectPtr<UCharacterMovementComponent> MovementComponent = GetCharacterMovement();
	MovementComponent -> bOrientRotationToMovement = true;
	
	/*
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SrpingArmComponent"));
	CameraArmComponent -> SetupAttachment(RootComponent.Get());
	CameraArmComponent -> TargetArmLength = 400.f;
	CameraArmComponent -> bUsePawnControlRotation = true;
	*/
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent -> SetupAttachment(RootComponent.Get());
	CameraComponent -> bUsePawnControlRotation = false;
	
	
	
	Cash = 600;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UE_LOG(LogTemp, Warning, TEXT("Setting up Player Input"));

	

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed setting up Player Input"));
		return;	
	}

	
	// EnhancedInputComponent -> BindAction(BackAction, ETriggerEvent::Triggered, this, &AFPSCharacter::BackEvent);
	
	UE_LOG(LogTemp, Warning, TEXT("Finished setting up Player Input"));
}

