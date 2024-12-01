// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gems.generated.h"

UCLASS()
class ENDLESSRUNNER_API AGems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGems();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* GemCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URotatingMovementComponent* RotationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Sound")
	class USoundBase* GemCollectSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION()
	void CoinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
