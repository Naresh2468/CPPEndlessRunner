// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetSecetion/GameHud.h"
#include "EndlessRunner/Public/GMRunner.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UGameHud::NativeConstruct()
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(),0),this);
	PauseBtn->OnClicked.AddDynamic(this, &UGameHud::OnPauseClick);
	ResumeBtn->OnClicked.AddDynamic(this, &UGameHud::OnResumeClick);
	RestartGameBtn->OnClicked.AddDynamic(this, &UGameHud::RestartGame);
}

void UGameHud::InitializeHUD(AGMRunner* GMRunner)
{
	if (GMRunner)
	{
		CoinsCountTXT->SetText(FText::AsNumber(0));
		GMRunner->OnCoinCountChanged.AddDynamic(this, &UGameHud::SetCoinsCount);
		GMRunner->OnGemsCountChanged.AddDynamic(this, &UGameHud::SetGemsCount);
		GMRunner->OnCurrentScoreChanged.AddDynamic(this, &UGameHud::SetCurrentScore); 
		localHighscore = GMRunner->TotalHighScore;
	}
}

void UGameHud::SetCoinsCount(const int32 value)
{
	CoinsCountTXT->SetText(FText::AsNumber(value));
}

void UGameHud::SetGemsCount(const int32 value)
{
	GemsCountTXT->SetText(FText::AsNumber(value));
}

void UGameHud::SetCurrentScore(const int32 value)
{
	ScoreCurrentTXT->SetText(FText::AsNumber(value));
	if (value > localHighscore )
	{
		LoadHighScore(value);
	}
}

void UGameHud::OnPauseClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	PauseToggle(true);
	PauseBtn->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PauseBtn->bIsEnabled = false; // avoid the pasue btn interaction once click
}

void UGameHud::OnResumeClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	PauseBtn->SetVisibility(ESlateVisibility::Visible);
	PauseToggle(false);
	PauseBtn->bIsEnabled = true;
}

void UGameHud::LoadHighScore(int32 value)
{
	//FText CustomText = FText::Format(FText::FromString(TEXT("High Score: {0}")), FText::AsNumber(value));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *CustomText.ToString());
	HighScoreTXT->SetText(FText::AsNumber(value));


}
