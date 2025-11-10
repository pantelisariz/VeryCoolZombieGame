// Copyright University of Inland Norway


#include "Zombie_AIController.h"

#include "Zombie.h"
#include "ZombieApocalypse/AI/CustomPawnBase.h"
#include "ZombieApocalypse/AI/Human/Human.h"


AZombie_AIController::AZombie_AIController(FObjectInitializer const& ObjectInitializer)
{
	AZombie_AIController::SetupPerceptionSystem();
}

void AZombie_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AZombie_AIController::SetupPerceptionSystem()
{
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception  Component")));
		SightConfig -> SightRadius = 900.0f;
		SightConfig -> LoseSightRadius = 1000.0f;
		SightConfig -> PointOfViewBackwardOffset = 80.0f;
		SightConfig -> NearClippingRadius = 50.0f;
		SightConfig -> PeripheralVisionAngleDegrees = 90.0f;
		SightConfig -> SetMaxAge(3.0f);
		// SightConfig -> AutoSuccessRangeFromLastSeenLocation = 50.f;
		SightConfig -> DetectionByAffiliation.bDetectEnemies = true;
		SightConfig -> DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig -> DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent() -> SetDominantSense(*SightConfig -> GetSenseImplementation());
		GetPerceptionComponent() -> OnTargetPerceptionUpdated.AddDynamic(this, &AZombie_AIController::OnTargetDetected);
		GetPerceptionComponent() -> ConfigureSense(*SightConfig);
	}
	
}

void AZombie_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	AHuman* HumanCast = Cast<AHuman>(Actor);
	if (not HumanCast)
	{
		return;
	}
	
	AZombie* const ZombieCast = Cast<AZombie>(GetPawn());
	if (not ZombieCast)
	{
		return;
	}
	
	GetBlackboardComponent() -> SetValueAsBool("bCanSeeHuman", Stimulus.WasSuccessfullySensed());
	GetBlackboardComponent() -> SetValueAsObject("TargetActor", Actor);

	GEngine -> AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Actor class: %s"), *Actor->GetClass()->GetName() ));

	

	
	// GEngine -> AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Zombie Location; X: %f Y: %f Z: %f"), ZombieLocation.X, ZombieLocation.Y, ZombieLocation.Z));
	// GEngine -> AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PawnBase Location; X: %f Y: %f Z: %f"), PawnBaseLocation.X, PawnBaseLocation.Y, PawnBaseLocation.Z));
}