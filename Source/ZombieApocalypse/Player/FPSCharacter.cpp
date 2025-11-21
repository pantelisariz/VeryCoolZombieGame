// Copyright University of Inland Norway


#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "GameFramework/DamageType.h"
#include "../AI/CustomPawnBase.h"
#include "DrawDebugHelpers.h"
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
	
	GunPlacementPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunPlacementPoint"));
	GunPlacementPoint -> SetupAttachment(RootComponent.Get());
	
	
	
	
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
	
	
	
	
	if (not StartingGunClass)
	{
		return;
	}
	
	CurrentGun = GetWorld() -> SpawnActor<AGun>(StartingGunClass, GunPlacementPoint -> GetRelativeLocation(), FRotator(0,-90,0));
	SetupGun();

	
	
	
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



void AFPSCharacter::SetupGun()
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentGun -> AttachToComponent(CameraArmComponent, AttachmentRules);
	CurrentGun -> PlayerCameraComponent = CameraComponent;
	CurrentGun -> CashGained.BindUObject(this, &AFPSCharacter::ChangeCash);
	CurrentGun -> AddCombatHUD();
}



void AFPSCharacter::ChangeCash(int32 CashChangeValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Delegate worked"));
	
	if (Cash + CashChangeValue <= 0)
	{
		Cash = 0;
	}
	else
	{
		Cash += CashChangeValue;
	}

	PlayerInfoHUD -> UpdateCashText(Cash);
}

