// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include <vector>
#include "SimulationController.generated.h"


struct Batch;
// Struct for the Unreal DataTable
USTRUCT(BlueprintType)
struct FPopulationDensityEffect : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PopulationDensity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NormalPopulationDensity;
};



UCLASS()
class ZOMBIEAPOCALYPSE_API ASimulationController : public AActor
{
	GENERATED_BODY()
	
public:	
	ASimulationController();

	// Runs one simulation step each Tick 
	virtual void Tick(float DeltaTime) override;

	// Function to read data from Unreal DataTable into the graphPts vector
	void ReadDataFromTableToVectors();


	// Unreal Lookup table for population density effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Variables")
	class UDataTable* PopulationDensityEffectTable{ nullptr };

	// How long each time step is in Unreal, in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Variables")
	float SimulationStepTime{ 1.f };

	// Turn on/off debug printing to the Output Log
	UPROPERTY(EditAnywhere, Category = "Simulation Variables")
	bool bShouldDebug{ false };


	// Stocks (initial)

	// Just to check if we are correctly updating stocks - used in SimulationHUD
	float Bitten{ 0.f };          // s Bitten -> in BittenArraySize


	
	// GRAPH points: population_density_effect_on_zombie_bites
	// Values read in from Unreal DataTable for more flexibility
	std::vector<std::pair<float, float>> graphPts;
		//= {
		//{0.000f, 0.014f}, {0.200f, 0.041f}, {0.400f, 0.101f}, {0.600f, 0.189f}, {0.800f, 0.433f},
		//{1.000f, 1.000f}, {1.200f, 1.217f}, {1.400f, 1.282f}, {1.600f, 1.300f}, {1.800f, 1.300f},
		//{2.000f, 1.300f}
		//};

	// Time accumulator for simulation steps, used in Tick function
	float AccumulatedTime{ 0.f };

	// Number of time steps completed - to keep track and compare to Stella
	int TimeStepsFinished{ 0 };

	// ----- TIME SPECS -----
	const int STARTTIME = 0;
	const int STOPTIME = 120;
	const double DT = 1.0; // Euler, daily steps

	// ----- CONSTANTS / INITIALIZATION -----
	const double days_to_become_infected_from_bite = 15.0; // Days
	const double Bitten_Two_capacity = 100.0;              // People (capacity inside conveyor)
	const double patient_zero = 1.0;                       // Zombies
	const double CONVERSION_FROM_PEOPLE_TO_ZOMBIES = 1.0;  // Zombies/People
	const double normal_number_of_bites = 1.0;             // People/zombie/day
	const double land_area = 1000.0;                       // m2
	const double normal_population_density = 0.1;          // people/m2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Variables")
	// Stocks (initial)
	double Susceptible = 100.0;        // People (called Zombies in the text, but used as People)
	double Zombies = patient_zero;     // Zombies
	// Conveyor content is the stock "Bitten_Two" (people incubating):
	std::vector<Batch*> conveyor;            // accepts multiple batches



protected:
	virtual void BeginPlay() override;

};
