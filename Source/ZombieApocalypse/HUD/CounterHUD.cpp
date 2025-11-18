// Copyright University of Inland Norway


#include "CounterHUD.h"

void UCounterHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ZombiePopulationCount = 0;
	BittenPopulationCount = 0;
	HumanPopulationCount = 0;
	Time = 0;

	UpdateAllText();
}

void UCounterHUD::UpdateAllText()
{
	SetZombieTextCounter();
	SetBittenTextCounter();
	SetHumanTextCounter();
	SetTimeTextCounter();
}


void UCounterHUD::SetZombieTextCounter()
{
	FText ZombieText = FText::FromString( FString::Printf(TEXT("Amount of Zombies: %d"), (int)ZombiePopulationCount) );
	ZombieTextCounter -> SetText(ZombieText);
}



void UCounterHUD::SetBittenTextCounter()
{
	FText BittenText = FText::FromString( FString::Printf(TEXT("Amount of Bitten: %d"), (int)BittenPopulationCount) );
	BittenTextCounter -> SetText(BittenText);
}



void UCounterHUD::SetHumanTextCounter()
{
	FText HumanText = FText::FromString( FString::Printf(TEXT("Amount of Humans: %d"), (int)HumanPopulationCount ));
	HumanTextCounter -> SetText(HumanText);
}

void UCounterHUD::SetTimeTextCounter()
{
	FText TimeText = FText::FromString( FString::Printf(TEXT("Time: %d"), (int)Time ));
	TimeTextCounter -> SetText(TimeText);
}

