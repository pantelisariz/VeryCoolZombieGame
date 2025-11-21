// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "ZombieApocalypse/Gun/Gun.h"
#include "FullGunInfoHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UFullGunInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY()
	AGun* CurrentGun;
	
public:
	void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* BulletCountBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* BulletTextCounter;
	
};
