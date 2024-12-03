// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MainRunner.generated.h"

//EnhancedMovement Logic Setup Class
class UInputMappingContext;
class UInputAction;

// Self Feature 
class USpringArmComponent;
class UCameraComponent;
class AGMRunner;
class UAnimMontage;

//Start
UCLASS()
class ENDLESSRUNNER_API AMainRunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainRunner();
#pragma region Basic player Essential

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* MainCamera;

#pragma endregion

#pragma region NRCollection
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Movement")
	FName PlayerRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Movement")
	FName PlayerLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Movement")
	FName PlayerSlide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Movement")
	FName PlayerJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|PlayerStats")
	bool PlayerDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Lanes")
	int32 CurrentLane = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Movement")
	float MoveDown = -1000.0f;

	int32 NextLane = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|References")
	AGMRunner* MainGameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	UAnimMontage* SlideMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float PlayRate = 1.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float OriginalCapsuleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float SlideCapsuleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float CurrentMeshOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float DownMeshOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	float OriginMeshOffset;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Slide")
	FVector OriginalMeshLocation;*/

	float TargetCapsuleHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Powerup")
	int32 HighJumpPowerup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Powerup")
	int32 JumpForce;
	

	bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Sound")
	class USoundBase* DeathSound;

	
#pragma endregion
	//EnhancedMovement
#pragma region Enhanced Movement

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "@NRCollection|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "@NRCollection|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "@NRCollection|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

#pragma endregion

#pragma region Function

	UFUNCTION()
	void MoveForward();//float value);
	UFUNCTION()
	void MoveRightSide();
	UFUNCTION()
	void MoveLeftSide();
	UFUNCTION()
	void MoveSlideDown();
	UFUNCTION()
	void MoveJumpStart();
	UFUNCTION()
	void MoveJumpStop();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeLane();

	UFUNCTION(BlueprintCallable)
	void ChangeLaneUpdate(float value);

	UFUNCTION(BlueprintCallable)
	void ChangeLaneFinished();

	UFUNCTION()
	void PlayerDeathProcess();

	UFUNCTION()
	void AddCoins();

	UFUNCTION()
	void AddGems();

	UFUNCTION()
	void StartSlide();// Slide action binding

	UFUNCTION(BlueprintImplementableEvent)
	void CharacterSelected();

	UFUNCTION(BlueprintImplementableEvent)
	void TimeSlide(bool value);

	UFUNCTION(BlueprintCallable, Category = "Powerup")
	void HighJumpActive(bool value);

	UFUNCTION()
	void EndSlide(UAnimMontage* Montage, bool bInterrupted);	// Stop the slide (Montage finished)
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
