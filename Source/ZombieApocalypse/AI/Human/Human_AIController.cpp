// Copyright University of Inland Norway


#include "Human_AIController.h"
#include "ZombieApocalypse/AI/CustomPawnBase.h"
#include "Human.h"
#include "ZombieApocalypse/AI/Zombie/Zombie.h"

AHuman_AIController::AHuman_AIController(FObjectInitializer const& ObjectInitializer)
{
	AHuman_AIController::SetupPerceptionSystem();
}

void AHuman_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AHuman_AIController::SetupPerceptionSystem()
{
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception  Component")));
		SightConfig -> SightRadius = 900.0f;
		SightConfig -> LoseSightRadius = 1100.0f;
		SightConfig -> PointOfViewBackwardOffset = 80.0f;
		SightConfig -> NearClippingRadius = 50.0f;
		SightConfig -> PeripheralVisionAngleDegrees = 180.0f;
		SightConfig -> SetMaxAge(3.0f);
		// SightConfig -> AutoSuccessRangeFromLastSeenLocation = 50.f;
		SightConfig -> DetectionByAffiliation.bDetectEnemies = true;
		SightConfig -> DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig -> DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent() -> SetDominantSense(*SightConfig -> GetSenseImplementation());
		GetPerceptionComponent() -> OnTargetPerceptionUpdated.AddDynamic(this, &AHuman_AIController::OnTargetDetected);
		GetPerceptionComponent() -> ConfigureSense(*SightConfig);
	}
	
}

void AHuman_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (!Actor->IsA(AZombie::StaticClass())) return;

	GetBlackboardComponent()->SetValueAsBool("bCanSeeZombie", Stimulus.WasSuccessfullySensed());
	GetBlackboardComponent()->SetValueAsObject("TargetActor", Stimulus.WasSuccessfullySensed() ? Actor : nullptr);


	// GEngine -> AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Zombie Location; X: %f Y: %f Z: %f"), ZombieLocation.X, ZombieLocation.Y, ZombieLocation.Z));
	// GEngine -> AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PawnBase Location; X: %f Y: %f Z: %f"), PawnBaseLocation.X, PawnBaseLocation.Y, PawnBaseLocation.Z));
}