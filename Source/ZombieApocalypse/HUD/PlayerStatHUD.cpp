// Copyright University of Inland Norway


#include "PlayerStatHUD.h"

void UPlayerStatHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerStatHUD::UpdateAllText()
{
}

void UPlayerStatHUD::UpdateCashText(int32 NewCashValue)
{	
	FText CashText = FText::FromString( FString::Printf(TEXT("$ %d"), (int)NewCashValue ));
	CashTextCounter -> SetText(CashText);
}
