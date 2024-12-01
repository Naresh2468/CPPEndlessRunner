// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GMRunner.generated.h"

/**
 * 
 */
class UUserWidget;
class UGameHud;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGemsCountChanged, int32, GemsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentScoreChanged, int32, CurrentScore);


UCLASS()
class ENDLESSRUNNER_API AGMRunner : public AGameModeBase
{
	GENERATED_BODY()
public:

#pragma region GameMode Vairaible

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Widget")
	TSubclassOf<UUserWidget> GameHudClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Widget")
	TSubclassOf<UUserWidget> GameOverClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Widget")
	 UGameHud* GameHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Floor")
	TArray<float>LaneLocationPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "@NRCollection|Floor")
	TSubclassOf<class AFloorscape> Floorclass;
	
	FVector FloorSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Floor")
	int32 NumberOfFloorSpawn = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|UI")
	int32 TotalCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|UI")
	int32 TotalGems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|UI")
	int32 TotalCurrentScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|UI")
	int32 TotalHighScore;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "@NRCollection|Delegate")
	FOnCoinsCountChanged OnCoinCountChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "@NRCollection|Delegate")
	FOnGemsCountChanged OnGemsCountChanged;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Score")
	float ScoreUpdateRate = 0.1f;

	FTimerHandle ScoreUpdateTime;

	FOnCurrentScoreChanged OnCurrentScoreChanged;

#pragma endregion

#pragma region Function
	UFUNCTION()
	void CreateInitialFloor();

	UFUNCTION()
	void AddFloor(const bool SpawnObstacle);

	UFUNCTION()
	void AddCoin();

	UFUNCTION()
	void AddGems();

	UFUNCTION()
	void GameOver();

	UFUNCTION()
	void ScoreHighUdate();

	UFUNCTION()
	void StopUpdateScore();

	UFUNCTION(BlueprintImplementableEvent, Category = "NRSaveGame")
	void SaveGameCall();

	UFUNCTION(BlueprintImplementableEvent, Category = "NRSaveGame")
	void LoadHighscoreCall();

	UFUNCTION()
	virtual void BeginPlay() override;
#pragma endregion
};
