// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "PlayerStatHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UPlayerStatHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	void UpdateAllText();
	
	void UpdateCashText(int32 NewCashValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UBorder* CashBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* CashTextCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Variable", meta = (BindWidget))
	int32 Cash;
};
