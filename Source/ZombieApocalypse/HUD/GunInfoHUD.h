// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "GunInfoHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UGunInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	void NativeConstruct() override;

	void UpdateAllText();
	
	void UpdateBulletCount(int32 NewBulletCount);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* BulletCountBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* BulletTextCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Variable", meta = (BindWidget))
	int32 BulletCount;
	int32 MaxBulletCount;
};
