// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class ENDLESSRUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UButton* RestartGameBtn;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UButton* LobbyBtn;


	UFUNCTION(BlueprintImplementableEvent)
	void RestartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void BackToLobby();

	virtual void NativeConstruct() override;
	
};
