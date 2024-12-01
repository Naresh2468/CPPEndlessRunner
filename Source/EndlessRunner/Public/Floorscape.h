// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floorscape.generated.h"

class UBoxComponent;
class UArrowComponent;
UCLASS()
class ENDLESSRUNNER_API AFloorscape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorscape();

#pragma region Floor Essential

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* MainSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnCollision;

	UPROPERTY(EditAnywhere)
	UArrowComponent* SpawnAttachPoint;

	UPROPERTY(EditAnywhere)
	UArrowComponent* LeftLaneRef;

	UPROPERTY(EditAnywhere)
	UArrowComponent* RightLaneRef;

	UPROPERTY(EditAnywhere)
	UArrowComponent* MiddleLaneRef;


#pragma endregion

#pragma region NR Collection
	FTimerHandle DestroyHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection")
	float SelfDestruction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnItem")
	TArray<TSubclassOf<class AActor>> SmallObstaclesArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnItem")
	TArray<TSubclassOf<class AActor>> BigObstaclesArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnItem")
	TArray<TSubclassOf<class AActor>> SpawnCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnItem")
	TArray<TSubclassOf<class AActor>> SpawnGems;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|DebugTools")
	bool BisObstacleSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnItem")
	TArray<AActor*> SpawnedItemCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnPercent")
	float SpawnpercentSmallObstacles = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnPercent")
	float SpawnpercentSmallObstacles2 = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnPercent")
	float SpawnpercenGems = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@NRCollection|SpawnPercent")
	float SpawnCoinPercent = 0.5f;
#pragma endregion
#pragma region Floor Function
	//UFUNCTION()
	//void SpawnNextFloor();

	UFUNCTION()
	void SpawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnObstacle();
	UFUNCTION()
	void SpawnObstacleOnLane(UArrowComponent* Lanes,int32& NumBigs);

	UFUNCTION()
	void FloorDestroy();

	UFUNCTION()
	void DestroySpawnedItems();
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	

};
