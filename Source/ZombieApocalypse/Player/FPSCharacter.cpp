// Copyright University of Inland Norway


#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "GameFramework/DamageType.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/AllDelegates.h"
#include "ZombieApocalypse/Interactables/InteractableActor.h"
#include "ZombieApocalypse/Interactables/PurchasableGun.h"

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
	
	MeleeWeaponPlacementPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeleeWeaponPlacementPoint"));
	MeleeWeaponPlacementPoint -> SetupAttachment(RootComponent.Get());
	
	
	
	
	RunSpeed = 1000.f;
	WalkSpeed = 600.f;
	
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	
	Cash = 600;
	


	
	OnGunPurchased.AddUObject(this, &AFPSCharacter::SetGun);
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
	
	SpawnGun(StartingGunClass);
	
	TArray<FString> StartingGunAttachmentClassesKeys;
	StartingGunAttachmentClasses.GetKeys(StartingGunAttachmentClassesKeys);
	
	for (FString AttachmentSlotName : StartingGunAttachmentClassesKeys)
	{
		for (UGunAttachmentSlotComponent* GunAttachmentSlot : CurrentGun -> AttachmentSlots)
		{
			UE_LOG(LogTemp, Warning, TEXT("AttachmentSlot name: %s %s"), *AttachmentSlotName, *GunAttachmentSlot -> GetName() );
			
			
			if (GunAttachmentSlot -> GetName() != AttachmentSlotName)
			{
				continue;
			}
			GunAttachmentSlot -> CurrentAttachmentClass = StartingGunAttachmentClasses[AttachmentSlotName];
			GunAttachmentSlot -> CreateAttachment();
			UE_LOG(LogTemp, Warning, TEXT("AttachmentSlot name: %s"), *GunAttachmentSlot -> CurrentAttachmentClass -> GetDisplayNameText().ToString());
		
		}
	}
	


	SpawnMeleeWeapon(StartingMeleeClass);
	
	CashChanged.AddUObject(this, &AFPSCharacter::ChangeCash);
	HealthChanged.AddUObject(this, &AFPSCharacter::ChangeHealth);
	AmmoChanged.AddUObject(this, &AFPSCharacter::ChangeAmmo);
	
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



void AFPSCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack"));
	
	if (not GetWorld() or not CameraComponent)
	{
		return;
	}
	
	if (TimeLastInteract + (0.5f * 0.95) >= GetWorld() -> TimeSeconds)
	{
		return;
	}
	
	
	
	const FVector TraceStart = CameraComponent -> GetComponentLocation();
	const FVector Direction = CameraComponent -> GetForwardVector();
	const FVector TraceEnd = TraceStart + Direction * 250;
	
	auto NewDirection = Direction.ToOrientationQuat();
	
	
	
	FCollisionShape SweepShape;
	SweepShape.SetCapsule(30.f,30.f);
	
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	FHitResult Hit;
	const bool bDidHit = GetWorld() -> SweepSingleByChannel(Hit, TraceStart, TraceEnd, NewDirection, TraceChannel, SweepShape);

	if (!bDidHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 1.0f, 0, 0.5f);
		return;
	}
	

	DrawDebugCapsule(GetWorld(), Hit.ImpactPoint, 10.f, 30.f, NewDirection, FColor::Red, false, 2.0f);
	
	AActor* HitActor = Hit.GetActor();
	if (!HitActor)
	{
		// Hit something without an actor, in our case it will be probably nothing
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
		return;
	}

	if (AInteractableActor* HitInteractable = Cast<AInteractableActor>(HitActor))
	{
		TimeLastInteract = GetWorld() -> TimeSeconds;
		
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Yellow, false, 1.0f, 0, 0.5f);
		if (APurchasableActor* HitPurchasableGun = Cast<APurchasableActor>(HitActor))
		{
			HitPurchasableGun -> Purchase(Cash);
		}
	}
	else
	{
		// We hit an actor that is NOT a target, this will happen a lot
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Melee attack successful"));
}




void AFPSCharacter::SpawnGun(TSubclassOf<AGun> GunWeaponClass)
{
	if (not GunWeaponClass)
	{
		return;
	}
	
	CurrentGun = GetWorld() -> SpawnActor<AGun>(GunWeaponClass, GunPlacementPoint -> GetRelativeLocation(), FRotator(0,-90,0));

	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentGun -> AttachToComponent(CameraArmComponent, AttachmentRules);
	CurrentGun -> PlayerCameraComponent = CameraComponent;
	
	
	CurrentGun -> AddCombatHUD();
	
}



void AFPSCharacter::SpawnMeleeWeapon(TSubclassOf<AMeleeWeapon> MeleeWeaponClass)
{
	if (not MeleeWeaponClass)
	{
		return;
	}
	
	CurrentMeleeWeapon = GetWorld() -> SpawnActor<AMeleeWeapon>(MeleeWeaponClass, MeleeWeaponPlacementPoint -> GetRelativeLocation(), FRotator(0,-90,0));

	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentMeleeWeapon -> AttachToComponent(CameraArmComponent, AttachmentRules);
	CurrentMeleeWeapon -> PlayerCameraComponent = CameraComponent;
	CashChanged.AddUObject(this, &AFPSCharacter::ChangeCash);
}



void AFPSCharacter::SetGun(AGun* NewGun)
{
	FVector CurrentGunPos = FVector(0,0,0);
	if (CurrentGun)
	{
		CurrentGunPos = CurrentGun -> GetActorLocation();
		
		FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepRelative, true);
		CurrentGun -> DetachFromActor(DetachmentRules);
		CurrentGun -> Destroy();
		CurrentGun = nullptr;
	}
	
	if (not NewGun)
	{
		return;
	}
	
	
	UE_LOG(LogTemp, Warning, TEXT("CurrentGun - X: %f, Y: %f, Z: %f"), CurrentGunPos.X, CurrentGunPos.Y, CurrentGunPos.Z);
	CurrentGun = NewGun;
	
	CurrentGun -> SetActorRotation(FRotator(0,0,0));
	CurrentGun -> SetActorLocation(CurrentGunPos);
	
	UE_LOG(LogTemp, Warning, TEXT("NewGun - X: %f, Y: %f, Z: %f"), CurrentGun -> GetActorLocation().X, CurrentGun -> GetActorLocation().Y, CurrentGun -> GetActorLocation().Z);
	
	

	
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentGun -> AttachToActor(this, AttachmentRules);
	CurrentGun -> PlayerCameraComponent = CameraComponent;
	
	CurrentGun -> SetActorLocation(GunPlacementPoint -> GetRelativeLocation());
	
	
	
	
	UE_LOG(LogTemp, Warning, TEXT("GunPlacementPoint - X: %f, Y: %f, Z: %f"), GunPlacementPoint -> GetRelativeLocation().X, GunPlacementPoint -> GetRelativeLocation().Y, GunPlacementPoint -> GetRelativeLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("CurrentGun - X: %f, Y: %f, Z: %f"), CurrentGun -> GetActorLocation().X, CurrentGun -> GetActorLocation().Y, CurrentGun -> GetActorLocation().Z);
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



void AFPSCharacter::ChangeAmmo(int32 AmmoChangeValue)
{
	CurrentGun -> CurrentCarryAmmo += AmmoChangeValue;
	CurrentGun -> GunCombatHUD -> UpdateBulletCount(CurrentGun -> CurrentMagazineAmmo, CurrentGun-> CurrentCarryAmmo);
}



void AFPSCharacter::ChangeHealth(int32 HealthChangeValue)
{
	CurrentHealth += HealthChangeValue;
}