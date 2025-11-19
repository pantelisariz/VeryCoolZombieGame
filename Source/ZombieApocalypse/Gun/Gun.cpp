// Copyright University of Inland Norway


#include "Gun.h"

#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/AI/CustomPawnBase.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh -> SetupAttachment(RootComponent.Get());	
	

	
	/*
	 * Here you can set the default stats of the gun
	 */
	Damage = 10;
	FireRate = 3;
	Range = 1000;
	ReloadTime = 3;
	MaxAmmoCount = 6;
	CurrentAmmoCount = MaxAmmoCount;
	
	TraceChannel = ECC_Visibility;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	
	
	if (not GunInfoHUDClass)
	{
		return;
	}
	
	GunInfoHUD = CreateWidget<UGunInfoHUD>(CastPlayerController, *(GunInfoHUDClass));
	
	check(GunInfoHUD);
	GunInfoHUD -> AddToViewport();
	GunInfoHUD -> MaxBulletCount = MaxAmmoCount;
	GunInfoHUD -> UpdateBulletCount(CurrentAmmoCount);
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	FireShot();
	const float TimeBetweenShots = 1.0f / FMath::Max(0.0001f, FireRate);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &AGun::FireShot, TimeBetweenShots, true, TimeBetweenShots);
}



void AGun::EndFire()
{
	bIsFiring = false;
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
	}
}

void AGun::FireShot()
{
	UWorld* World = GetWorld();
	if (!World || !PlayerCameraComponent)
	{
		return;
	}

	// Trace origin / direction
	const FVector TraceStart = PlayerCameraComponent->GetComponentLocation();
	const FVector Direction = PlayerCameraComponent->GetForwardVector();
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

