// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "CounterHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UCounterHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void UpdateAllText();
	void SetZombieTextCounter();
	void SetBittenTextCounter();
	void SetHumanTextCounter();
	void SetTimeTextCounter();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* ZombieBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* ZombieTextCounter;
	int32 ZombiePopulationCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* BittenBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* BittenTextCounter;
	int32 BittenPopulationCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* HumanBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* HumanTextCounter;
	int32 HumanPopulationCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* TimeBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* TimeTextCounter;
	int32 Time;
	

	
	
};
