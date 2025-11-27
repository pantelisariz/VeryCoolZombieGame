// Copyright University of Inland Norway


#include "Weapon.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/HUD/CombatHUD.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(RootComponent.Get());	

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::AddCombatHUD()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	
	
	if (not CombatHUDClass)
	{
		return;
	}
	

	
	CombatHUD = CreateWidget<UCombatHUD>(CastPlayerController, *(CombatHUDClass));
	
	check(CombatHUD);
	CombatHUD -> AddToViewport();
}

