// Copyright University of Inland Norway


#include "CustomPawnBase.h"

// Sets default values
ACustomPawnBase::ACustomPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(GetRootComponent());

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider -> SetupAttachment(GetRootComponent());

	
	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));
	FloatingPawnMovementComponent -> UpdatedComponent = RootComponent;
	FloatingPawnMovementComponent -> bConstrainToPlane = 1;
	FloatingPawnMovementComponent -> SetPlaneConstraintNormal( FVector(0,0, 1) );


	health = 100;
	maxSpeed = 100;
	
	PawnAIController = nullptr;
	BehaviorTree = nullptr;
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



