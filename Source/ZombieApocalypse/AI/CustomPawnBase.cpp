// Copyright University of Inland Norway


#include "CustomPawnBase.h"

#include "ZombieApocalypse/AllDelegates.h"

// Sets default values
ACustomPawnBase::ACustomPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	
	SphereCollider -> SetupAttachment(GetMesh());

	/*
	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));
	FloatingPawnMovementComponent -> UpdatedComponent = RootComponent;
	FloatingPawnMovementComponent -> bConstrainToPlane = 1;
	FloatingPawnMovementComponent -> SetPlaneConstraintNormal( FVector(0,0, 1) );
	*/


	Health = 100;
	MaxWalkSpeed = 100;
	MaxRunSpeed = 300;
	CashChangeValue = 0;
	
	PawnAIController = nullptr;
	BehaviorTree = nullptr;
	
	
	WeaknessLenght = 2.f;
	bIsWeakened = false;
	WeakController = nullptr;
}



// Called when the game starts or when spawned
void ACustomPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ACustomPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void ACustomPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ACustomPawnBase::Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
}



void ACustomPawnBase::TakeDamage(float Damage, bool bDamagerWasMelee)
{
	if (bIsWeakened and bDamagerWasMelee)
	{
		CashChanged.Broadcast(CashChangeValue * 2);
		HealthChanged.Broadcast(8);
		AmmoChanged.Broadcast(2);
		
		Destroy();
		return;
	}
	
	if (bIsWeakened)
	{
		CashChanged.Broadcast(CashChangeValue);
		
		Destroy();
		return;
	}
	
	if (Health - Damage <= HealthToBecomeWeakValue)
	{
		MakeWeak();
		return;
	}
	
	Health -= Damage;
}



void ACustomPawnBase::MakeWeak()
{
	bIsWeakened = true;
	WeakController = GetController();
	WeakController -> UnPossess();
	
	GetMesh() -> SetScalarParameterValueOnMaterials(FName("WeakPercentage"), 5);
	
	GetWorldTimerManager().SetTimer(TimerHandle_Weak, this, &ACustomPawnBase::MakeNormal, WeaknessLenght);
}



void ACustomPawnBase::MakeNormal()
{
	UE_LOG(LogTemp, Warning, TEXT("Make normal"));
	
	bIsWeakened = false;
	WeakController -> Possess(this);
	
	GetMesh() -> SetScalarParameterValueOnMaterials(FName("WeakPercentage"), 0);
}


