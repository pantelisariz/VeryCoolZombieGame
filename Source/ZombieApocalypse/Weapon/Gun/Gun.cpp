// Copyright University of Inland Norway


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ZombieApocalypse/AllDelegates.h"
#include "ZombieApocalypse/AI/CustomPawnBase.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	
	
	
	
	
	/*
	 * Here you can set the default stats of the gun
	 */
	WeaponTypeInText = ("Gun");
	
	Damage = 60;
	FireRate = 3.f;
	Range = 1500.f;
	ReloadTime = 1.5f;
	MagazineCapacity = 10;
	CurrentMagazineAmmo = MagazineCapacity;
	CurrentCarryAmmo = MagazineCapacity * 4;
	MaxCarryAmmo = 300;
	BulletPerAmmo = 1;
	AmmoUsedPerShot = 1;
	
	DamageBeforeAttachments = Damage;
	FireRateBeforeAttachments = FireRate;
	RangeBeforeAttachments = Range;
	ReloadTimeBeforeAttachments = ReloadTime;
	MagazineCapacityBeforeAttachments = MagazineCapacity;
	CurrentCarryAmmoBeforeAttachments = CurrentCarryAmmo;
	MaxCarryAmmoBeforeAttachments = MaxCarryAmmo;
	BulletPerAmmoBeforeAttachments = BulletPerAmmo;
	AmmoUsedPerShotBeforeAttachments = AmmoUsedPerShot;
	
	
	
	/*
	 *
	 */
	
	
	
	TraceChannel = ECC_Visibility;
	TimeLastShot = 0.f;
	bIsReloading = false;
	
	GunCombatHUDClass = nullptr;
	GunCombatHUD = nullptr;
	
	bHasGottenAllAttachments = false;
	
	
	
	
	

}



// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	GetAllAttachments();

	TimeBetweenShots  = 1.0f / FMath::Max(0.0001f, FireRate);
}



// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsReloading)
	{
		ReloadProgress = FMath::FInterpConstantTo(ReloadProgress, 1.f, DeltaTime, 1 / ReloadTime);
		GunCombatHUD -> UpdateReloadProgressBar(ReloadProgress);
	}
	
}



void AGun::StartFire()
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
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &AGun::Fire, 1/FireRate, true, 0);
}



void AGun::EndFire()
{
	bIsFiring = false;
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
	}
}



void AGun::StartReloading()
{
	if (CurrentCarryAmmo <= 0)
	{
		return;
	}
	GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AGun::Reload, ReloadTime, false, ReloadTime);
	bIsReloading = true;
}



void AGun::AddCombatHUD()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	
	
	if (not GunCombatHUDClass)
	{
		return;
	}
	

	
	GunCombatHUD = CreateWidget<UGunCombatHUD>(CastPlayerController, *(GunCombatHUDClass));
	
	check(GunCombatHUD);
	GunCombatHUD -> AddToViewport();
	
	GunCombatHUD -> UpdateBulletCount(CurrentMagazineAmmo, CurrentCarryAmmo);
	
}



void AGun::Fire()
{
	if (not GetWorld() or not PlayerCameraComponent)
	{
		return;
	}
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_Reload))
	{
		return;
	}
	
	if (TimeLastShot + (TimeBetweenShots * 0.95) >= GetWorld() -> TimeSeconds)
	{
		return;
	}
	
	if (CurrentMagazineAmmo <= 0)
	{
		StartReloading();
		return;
	}
	
	

	GetWorldTimerManager().SetTimer(TimerHandle_MultiShot, this, &AGun::FireShot, 0.01f/FireRate, false);
}



void AGun::FireShot()
{
	UWorld* World = GetWorld();
	
	FireShotStatChanges();

	// Trace origin / direction
	const FVector TraceStart = PlayerCameraComponent -> GetComponentLocation();
	const FVector Direction = PlayerCameraComponent -> GetForwardVector();
	const FVector TraceEnd = TraceStart + Direction * Range;

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
		int32 CalculatedDamage = Damage * BulletPerAmmo;
		HitPawn -> TakeDamage(CalculatedDamage);
		//apply damage placehodler for later
		//UGameplayStatics::ApplyPointDamage(HitPawn, BaseDamage, Direction, Hit, GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		// We hit an actor that is NOT a target, this will happen a lot
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
	}
}



void AGun::FireShotStatChanges()
{
	TimeLastShot = GetWorld() -> TimeSeconds;
	
	CurrentMagazineAmmo -= AmmoUsedPerShot;
	GunCombatHUD -> UpdateBulletCount(CurrentMagazineAmmo, CurrentCarryAmmo);
}



void AGun::Reload()
{
	if (not bIsReloading)
	{
		return;
	}
	
	if (CurrentCarryAmmo <= 0)
	{
		FinishedReloading();
		return;
	}
	
	
	int32 ReloadAmount = MagazineCapacity - CurrentMagazineAmmo;
	if (CurrentCarryAmmo < ReloadAmount)
	{
		ReloadAmount = CurrentCarryAmmo;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Reloading before, %d, %d, %d"), CurrentMagazineAmmo, MagazineCapacity, CurrentCarryAmmo);
	CurrentCarryAmmo -= ReloadAmount;
	CurrentMagazineAmmo += ReloadAmount;
	GunCombatHUD -> UpdateBulletCount(CurrentMagazineAmmo, CurrentCarryAmmo);
	UE_LOG(LogTemp, Warning, TEXT("Reloading after, %d, %d, %d"), CurrentMagazineAmmo, MagazineCapacity, CurrentCarryAmmo);
	
	
	FinishedReloading();
}



void AGun::FinishedReloading()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Reload);
	
	bIsReloading = false;
	ReloadProgress = 0.f;
	
	
	GunCombatHUD -> UpdateReloadProgressBar(ReloadProgress);
}



void AGun::GetAllAttachments()
{

	UE_LOG(LogTemp, Warning, TEXT("Getting All Components"));
	AttachmentSlots.Empty();
	for (UGunAttachmentSlotComponent* GunAttachmentComponent : AttachmentSlots)
	{
		GunAttachmentComponent -> DestroyComponent();
	}
	
	
	TInlineComponentArray<UActorComponent*> Components;
	GetComponents(Components);
	
	TArray<USceneComponent*> ChildrenComponents;
	RootComponent -> GetChildrenComponents(true, ChildrenComponents);
	
	for (USceneComponent* ChildrenComponent : ChildrenComponents)
	{
		UE_LOG(LogTemp, Warning, TEXT("Looking at Component: %s"), *ChildrenComponent->GetName());
		UGunAttachmentSlotComponent* AttachmentComponent = Cast<UGunAttachmentSlotComponent>(ChildrenComponent);
		if (not AttachmentComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed Cast"));
			continue;
		}
		if (AttachmentSlots.Contains(AttachmentComponent))
		{
			continue;
		}
		UE_LOG(LogTemp, Warning, TEXT("Added component to Attachment Slots array"));
		AttachmentSlots.Add(AttachmentComponent);
		
		
		AttachmentComponent -> AttachmentCreated.AddUObject(this, &AGun::AddAttachmentStatsToGun);
		
	}
	bHasGottenAllAttachments = true;
	
}



void AGun::SetupAttachmentStats(TMap<EGunStatType, float> Map)
{
}



void AGun::AddAttachmentStatsToGun(TMap<EGunStatType, FGunStatChange>AttachmentStatChanges)
{
	
	if (AttachmentStatChanges.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachmentStatChanges are empty"));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Amount of stat changes: %d"), AttachmentStatChanges.Num());
	
	TArray<EGunStatType> GunStatsInAttachment;
	AttachmentStatChanges.GenerateKeyArray(GunStatsInAttachment);
	
	for (EGunStatType CurrentGunStat: GunStatsInAttachment)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Current Gun Stat %d"), CurrentGunStat);
		
		
		switch (CurrentGunStat)
		{
		case EGunStatType::Damage:
			Damage = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], DamageBeforeAttachments);
			
			break;		
			
		case EGunStatType::FireRate:
			FireRate = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], FireRateBeforeAttachments);
			
			break;
			
		case EGunStatType::Range:
			Range = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], RangeBeforeAttachments);
			
			break;
			
		case EGunStatType::ReloadTime:
			ReloadTime = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], ReloadTimeBeforeAttachments);
			
			break;
			
		case EGunStatType::MagazineCapacity:
			MagazineCapacity = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], MagazineCapacityBeforeAttachments);
			CurrentMagazineAmmo = MagazineCapacity;
			
			break;
			
		case EGunStatType::CurrentCarryAmmo:
			CurrentCarryAmmo = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], CurrentCarryAmmoBeforeAttachments);
			
			break;
			
		case EGunStatType::MaxCarryAmmo:
			MaxCarryAmmo = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], MaxCarryAmmoBeforeAttachments);
			
			break;
			
		case EGunStatType::BulletPerAmmo:
			BulletPerAmmo = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], BulletPerAmmoBeforeAttachments);
			
			break;
			
		case EGunStatType::AmmoUsedPerShot:
			AmmoUsedPerShot = AttachmentStatChange(AttachmentStatChanges[CurrentGunStat], AmmoUsedPerShot);
			break;
		}
	}
	
	if (GunCombatHUD)
	{
		GunCombatHUD -> UpdateBulletCount(CurrentMagazineAmmo, CurrentCarryAmmo);
	}
}



float AGun::AttachmentStatChange(FGunStatChange GunStatChange, float ValueToSetToo)
{
	TArray<EGunStatChangeType> GunStatChangesInAttachment;
	GunStatChange.Values .GenerateKeyArray(GunStatChangesInAttachment);
	
	for (EGunStatChangeType CurrentGunStatChange: GunStatChangesInAttachment)
	{
		switch (CurrentGunStatChange)
		{
		case EGunStatChangeType::Add:
			ValueToSetToo += GunStatChange.Values[CurrentGunStatChange];
			return ValueToSetToo;
			break;
			
		case EGunStatChangeType::Multiply:
			ValueToSetToo *= GunStatChange.Values[CurrentGunStatChange];
			return ValueToSetToo;
			break;
			
		case EGunStatChangeType::Set:
			ValueToSetToo = GunStatChange.Values[CurrentGunStatChange];
			return ValueToSetToo;
			break;
		}
	}
	
	return 0;
}
