// Copyright University of Inland Norway


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	
	CameraArmComponent = nullptr;
	CameraComponent = nullptr;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	TObjectPtr<UCharacterMovementComponent> MovementComponent = GetCharacterMovement();
	MovementComponent -> bOrientRotationToMovement = true;
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SrpingArmComponent"));
	CameraArmComponent -> SetupAttachment(RootComponent.Get());
	CameraArmComponent -> TargetArmLength = -10.f;
	CameraArmComponent -> bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent -> SetupAttachment(CameraArmComponent.Get(), USpringArmComponent::SocketName);
	CameraComponent -> bUsePawnControlRotation = false;
	
	RunSpeed = 1000.f;
	WalkSpeed = 600.f;
	
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	
	Cash = 600;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement() -> MaxWalkSpeed = WalkSpeed;
	
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	
	
	if (not PlayerInfoHUDClass)
	{
		return;
	}
	
	PlayerInfoHUD = CreateWidget<UPlayerStatHUD>(CastPlayerController, *(PlayerInfoHUDClass));
	
	check(PlayerInfoHUD);
	PlayerInfoHUD -> AddToViewport();
	PlayerInfoHUD -> UpdateCashText(Cash);
	
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

}

