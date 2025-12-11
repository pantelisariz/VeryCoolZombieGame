// Copyright University of Inland Norway


#include "MeleeWeapon.h"

#include "ZombieApocalypse/AllDelegates.h"
#include "ZombieApocalypse/AI/CustomPawnBase.h"


// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Damage = 15.0f;
	Cooldown = 1.5f;
	
	TimeLastMeleeAttack = 0.f;

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	TimeBetweenMeleeAttack  = 1.0f / FMath::Max(0.0001f, Cooldown);

	
}



// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMeleeWeapon::StartAttack()
{
	bIsAttacking = true;

	// If FireRate <= 0,do semi-automatic fire
	if (Cooldown <= 0.f)
	{
		Attack();
		return;
	}

	if (!GetWorld())
	{
		return;
	}

	// Fire immediately then start timer for subsequent shots
	GetWorldTimerManager().SetTimer(TimerHandle_AutoAttack, this, &AMeleeWeapon::Attack, Cooldown, true, 0);
}



void AMeleeWeapon::EndAttack()
{
	bIsAttacking = false;
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoAttack);
	}
}



void AMeleeWeapon::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack"));
	
	if (not GetWorld() or not PlayerCameraComponent)
	{
		return;
	}
	
	if (TimeLastMeleeAttack + (Cooldown * 0.95) >= GetWorld() -> TimeSeconds)
	{
		return;
	}
	
	
	const FVector TraceStart = PlayerCameraComponent -> GetComponentLocation();
	const FVector Direction = PlayerCameraComponent -> GetForwardVector();
	const FVector TraceEnd = TraceStart + Direction * 250;
	
	auto NewDirection = Direction.ToOrientationQuat();
	
	
	
	FCollisionShape SweepShape;
	SweepShape.SetCapsule(30.f,30.f);
	
	
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

	// If the hit actor is one of our pawns, nuke it (TODO: or apply damage later)
	if (ACustomPawnBase* HitPawn = Cast<ACustomPawnBase>(HitActor))
	{
		int32 CalculatedDamage = Damage;
		HitPawn -> TakeDamage(CalculatedDamage, true);
		CashChanged.Broadcast(HitPawn -> CashChangeValue);
		//apply damage placehodler for later
		//UGameplayStatics::ApplyPointDamage(HitPawn, BaseDamage, Direction, Hit, GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		// We hit an actor that is NOT a target, this will happen a lot
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Melee attack successful"));
	
	
	
	TimeLastMeleeAttack = GetWorld() -> TimeSeconds;
}

