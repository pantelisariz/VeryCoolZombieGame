// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void StartAttack();
	void EndAttack();
	void Attack();
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	
	float TimeBetweenMeleeAttack;
	float TimeLastMeleeAttack;
	FTimerHandle TimerHandle_AutoAttack;
	
	bool bIsAttacking = false;
	
	
	
	
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	int32 Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	float Cooldown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats", meta = (AllowPrivateAccess = "true"))
	float Range;
	
	

	
};
