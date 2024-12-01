// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
UCLASS()
class ENDLESSRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* HighScoreTXT;

	UPROPERTY(BlueprintReadWrite,Meta = (BindWidget))
	UTextBlock* CoinsCountTXT;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* GemsCountTXT;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* ScoreCurrentTXT;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UButton* PauseBtn;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UButton* ResumeBtn;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UButton* RestartGameBtn;

	int32 localHighscore;

	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AGMRunner* GMRunner);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(int32 value);

	UFUNCTION(BlueprintCallable)
	void SetGemsCount(int32 value);

	UFUNCTION(BlueprintCallable)
	void SetCurrentScore(int32 value);

	UFUNCTION(BlueprintImplementableEvent)
	void PauseToggle(bool value);

	UFUNCTION(BlueprintImplementableEvent)
	void RestartGame();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void MagnetPowerupupdates(float value);



	UFUNCTION()
	void OnPauseClick();

	UFUNCTION()
	void OnResumeClick();

	UFUNCTION(BlueprintCallable, Category = "NRCustomLoad")
	void LoadHighScore(int32 value);

	virtual void NativeConstruct() override;
	
};
