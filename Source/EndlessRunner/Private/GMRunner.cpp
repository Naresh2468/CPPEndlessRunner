// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunner/Public/GMRunner.h"
#include "components/Arrowcomponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameWork/Character.h"
#include "Floorscape.h"
#include "TimerManager.h"
#include "WidgetSecetion/GameHud.h"



void AGMRunner::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);
	GameHud->AddToViewport();
	CreateInitialFloor();
	GetWorld()->GetTimerManager().SetTimer(ScoreUpdateTime, this, &AGMRunner::ScoreHighUdate, ScoreUpdateRate, true);
	LoadHighscoreCall();
	GameHud->InitializeHUD(this);
}
void AGMRunner::CreateInitialFloor()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		FloorSpawnLocation = PlayerCharacter->GetActorLocation() - FVector(100, 0, 100);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player character is null!"));
		return; // Exit early to avoid further crashes
	}
	for ( int i = 0; i < NumberOfFloorSpawn; i++)
	{
		AddFloor(false);
	}
	AFloorscape* CurrentFloorRef = GetWorld()->SpawnActor<AFloorscape>(Floorclass, FloorSpawnLocation, FRotator(0, 0, 0));
	FloorSpawnLocation = CurrentFloorRef->SpawnAttachPoint->GetComponentLocation();

	LaneLocationPlayer.Add(CurrentFloorRef->LeftLaneRef->GetComponentLocation().Y);
	LaneLocationPlayer.Add(CurrentFloorRef->MiddleLaneRef->GetComponentLocation().Y);
	LaneLocationPlayer.Add(CurrentFloorRef->RightLaneRef->GetComponentLocation().Y);
	for (float val : LaneLocationPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lane Value:- %f"),val);
	}
}
void AGMRunner::AddFloor(const bool SpawnObstacle)
{
	AFloorscape* FloorSpawnerInstance = GetWorld()->SpawnActor<AFloorscape>(Floorclass, FloorSpawnLocation, FRotator(0, 0, 0));

	FloorSpawnLocation = FloorSpawnerInstance->SpawnAttachPoint->GetComponentLocation();
	if (SpawnObstacle)FloorSpawnerInstance->SpawnObstacle();
}

void AGMRunner::AddCoin()
{
	TotalCoins++;
	//UE_LOG(LogTemp, Warning, TEXT("Coin Value:- %d"), TotalCoins);
	OnCoinCountChanged.Broadcast(TotalCoins);

}

void AGMRunner::AddGems()
{
	TotalGems++;
	//UE_LOG(LogTemp, Warning, TEXT("Coin Value:- %d"), TotalCoins);
	OnGemsCountChanged.Broadcast(TotalGems);

}

void AGMRunner::ScoreHighUdate()
{
	TotalCurrentScore++;
	OnCurrentScoreChanged.Broadcast(TotalCurrentScore);

}
void AGMRunner::StopUpdateScore()
{
	GetWorld()->GetTimerManager().ClearTimer(ScoreUpdateTime);
}

void AGMRunner::GameOver()
{
	if (IsValid(GameOverClass))
	{
		UUserWidget* GameOver = CreateWidget(GetWorld(), GameOverClass);
		if (GameOver)
		{
			GameOver->AddToViewport();
			StopUpdateScore();
			SaveGameCall();
		}
	}
}


//void AScoreManager::SaveScore()
//{
//	// Create a save game instance
//	UScoreSaveGame* SaveGameInstance = Cast<UScoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UScoreSaveGame::StaticClass()));
//
//	// Set current and high scores
//	SaveGameInstance->CurrentScore = CurrentScore;
//	SaveGameInstance->HighScore = HighScore;
//
//	// Save the game
//	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerScoreSlot"), 0);
//}
//
//void AScoreManager::LoadScore()
//{
//	// Try to load the saved game data
//	UScoreSaveGame* LoadedGame = Cast<UScoreSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerScoreSlot"), 0));
//
//	if (LoadedGame)
//	{
//		// If the game data is loaded, set the current and high scores
//		CurrentScore = LoadedGame->CurrentScore;
//		HighScore = LoadedGame->HighScore;
//	}
//}