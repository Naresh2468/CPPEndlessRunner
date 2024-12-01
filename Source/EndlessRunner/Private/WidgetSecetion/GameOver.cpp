// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetSecetion/GameOver.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UGameOver::NativeConstruct()
{
	RestartGameBtn->OnClicked.AddDynamic(this, &UGameOver::RestartGame);
	LobbyBtn->OnClicked.AddDynamic(this, &UGameOver::BackToLobby);
}
