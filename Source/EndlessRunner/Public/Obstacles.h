// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacles.generated.h"

UCLASS()
class ENDLESSRUNNER_API AObstacles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacles();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ObstacleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|Sound")
	class USoundBase* ObstacleSound;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void ObstacleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
