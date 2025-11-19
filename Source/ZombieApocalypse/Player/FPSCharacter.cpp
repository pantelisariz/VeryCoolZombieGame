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
	
	RunSpeed = 1000.f;
	WalkSpeed = 600.f;
	
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	
	Cash = 600;

	// Gun stuff, can also be changed in blueprint
	BaseDamage = 25.f;
	TraceDistance = 10000.f;
	FireRate = 1.f;
	TraceChannel = ECC_Visibility;

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

//The shooting logic when the player holds down the fire button
void AFPSCharacter::StartFire()
{
	bIsFiring = true;

	// If FireRate <= 0,do semi-automatic fire
	if (FireRate <= 0.f)
	{
		FireShot();
		return;
	}

	if (!GetWorld())
	{
		return;
	}

	// Fire immediately then start timer for subsequent shots
	FireShot();
	const float TimeBetweenShots = 1.0f / FMath::Max(0.0001f, FireRate);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &AFPSCharacter::FireShot, TimeBetweenShots, true, TimeBetweenShots);
}

void AFPSCharacter::StopFire()
{
	bIsFiring = false;
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
	}
}

// The actual ray casting and damage application
void AFPSCharacter::FireShot()
{
	UWorld* World = GetWorld();
	if (!World || !CameraComponent)
	{
		return;
	}

	// Trace origin / direction
	const FVector TraceStart = CameraComponent->GetComponentLocation();
	const FVector Direction = CameraComponent->GetForwardVector();
	const FVector TraceEnd = TraceStart + Direction * TraceDistance;

	// Prepare collision params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	// Perform trace
	FHitResult Hit;
	const bool bDidHit = World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);

	// No hit
	if (!bDidHit)
	{
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Blue, false, 1.0f, 0, 0.5f);
		return;
	}

	// We hit something.
	DrawDebugSphere(World, Hit.ImpactPoint, 8.0f, 8, FColor::Red, false, 1.0f);

	AActor* HitActor = Hit.GetActor();
	if (!HitActor)
	{
		// Hit something without an actor, in our case it will be probably nothing
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
		return;
	}

	// If the hit actor is one of our pawns, nuke it (TODO: or apply damage later)
	if (ACustomPawnBase* HitPawn = Cast<ACustomPawnBase>(HitActor))
	{
		HitPawn->Destroy();

		//apply damage placehodler for later
		//UGameplayStatics::ApplyPointDamage(HitPawn, BaseDamage, Direction, Hit, GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		// We hit an actor that is NOT a target, this will happen a lot
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
	}
}