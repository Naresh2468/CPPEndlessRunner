// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunner/Public/Floorscape.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "components/boxcomponent.h"
#include "components/Arrowcomponent.h"
#include "GameFrameWork/Character.h"
#include "GMRunner.h"

// Sets default values
AFloorscape::AFloorscape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MainSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MainSceneRoot"));
	RootComponent = MainSceneRoot;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshGround"));
	FloorMesh->SetupAttachment(MainSceneRoot);

	SpawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnCollision"));
	SpawnCollision->SetupAttachment(MainSceneRoot);

	SpawnAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnAttachPoint"));
	SpawnAttachPoint->SetupAttachment(MainSceneRoot);

	LeftLaneRef = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLaneArrow"));
	LeftLaneRef->SetupAttachment(MainSceneRoot);

	RightLaneRef = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLaneArrow"));
	RightLaneRef->SetupAttachment(MainSceneRoot);

	MiddleLaneRef = CreateDefaultSubobject<UArrowComponent>(TEXT("MiddleLaneArrow"));
	MiddleLaneRef->SetupAttachment(MainSceneRoot);

	//Default Preset
	SpawnCollision->SetBoxExtent(FVector(40, 500, 300.F));
	SpawnCollision->SetCollisionProfileName(TEXT("OvelapOnlyPawn")); // Make sure this Thing Proper.
	SelfDestruction = 4.0f;
	BisObstacleSpawn = true;
}

// Called when the game starts or when spawned
void AFloorscape::BeginPlay()
{
	Super::BeginPlay();
	SpawnCollision->OnComponentBeginOverlap.AddDynamic(this, &AFloorscape::SpawnOverlap);
}

void AFloorscape::SpawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);   // Use ACharacter or your custom player class

	if (OtherActor == PlayerCharacter)
	{
		// If we cast successfully, it means the overlapped actor is the player character
		AGMRunner* GMRunner = Cast<AGMRunner>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GMRunner != nullptr)
		{
			GMRunner->AddFloor(BisObstacleSpawn); // Spawn the next tile
			GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorscape::FloorDestroy, SelfDestruction, false); // Start the tile self-destruction countdown
			UE_LOG(LogTemp, Warning, TEXT("GroundSpawn"));
		}
	}
	else
	{
		// Optionally log or handle cases where the overlapped actor is not the player
		UE_LOG(LogTemp, Warning, TEXT("[%s] Overlapped actor is not the player character!"), *FString(__FUNCTION__));
	}

}

void AFloorscape::FloorDestroy()
{
	DestroySpawnedItems();
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}
	this->Destroy();//Self Destroy
}


void AFloorscape::SpawnObstacle()
{
	int32 NumBigs = 0;
	SpawnObstacleOnLane(LeftLaneRef, NumBigs);
	SpawnObstacleOnLane(MiddleLaneRef, NumBigs);
	SpawnObstacleOnLane(RightLaneRef, NumBigs);
}

void AFloorscape::SpawnObstacleOnLane(UArrowComponent* Lanes , int32& NumBigs)
{
	const float SpawnChances = FMath::FRandRange(0.0f, 1.0f);
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FVector& SpawnLocation = Lanes->GetComponentLocation();
	
	if (UKismetMathLibrary::InRange_FloatFloat(SpawnChances, SpawnpercentSmallObstacles, SpawnpercentSmallObstacles2))
	{
		if (BisObstacleSpawn && SmallObstaclesArray.Num() > 0)
		{
			int IndexToSpawn = FMath::RandHelper(SmallObstaclesArray.Num()); // Get a random index from the obstaclesArray
			if (SmallObstaclesArray[IndexToSpawn])// Check if the class at the random index is valid before spawning
			{
				// Spawn the actor at the specified location and rotation (you can adjust rotation if needed)
				FRotator SpawnRotation = FRotator(0, 0, 0); // Modify this if you need dynamic rotation
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SmallObstaclesArray[IndexToSpawn], SpawnLocation, SpawnRotation, spawnParameters);
				if (SpawnedActor) SpawnedItemCollection.Add(SpawnedActor);  // Add to the spawned obstacles array
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("obstaclesArray is empty or else BisObstacleSpawn is false check !"));
		}

	}
	else if (UKismetMathLibrary::InRange_FloatFloat(SpawnChances, SpawnpercentSmallObstacles2, 0.6F))
	{
		if (NumBigs <= 2)
		{
			if (BisObstacleSpawn && BigObstaclesArray.Num() > 0)
			{
				int IndexToSpawn = FMath::RandHelper(BigObstaclesArray.Num()); // Get a random index from the obstaclesArray
				if (BigObstaclesArray[IndexToSpawn])// Check if the class at the random index is valid before spawning
				{
					// Spawn the actor at the specified location and rotation (you can adjust rotation if needed)
					FRotator SpawnRotation = FRotator(0, 0, 0); // Modify this if you need dynamic rotation
					AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BigObstaclesArray[IndexToSpawn], SpawnLocation, SpawnRotation, spawnParameters);
					if (SpawnedActor) SpawnedItemCollection.Add(SpawnedActor);
				}
			}
			NumBigs += 1;

		}
		else
		{
			if (BisObstacleSpawn && SmallObstaclesArray.Num() > 0)
			{
				int IndexToSpawn = FMath::RandHelper(SmallObstaclesArray.Num()); // Get a random index from the obstaclesArray
				if (SmallObstaclesArray[IndexToSpawn])// Check if the class at the random index is valid before spawning
				{
					// Spawn the actor at the specified location and rotation (you can adjust rotation if needed)
					FRotator SpawnRotation = FRotator(0, 0, 0); // Modify this if you need dynamic rotation
					AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SmallObstaclesArray[IndexToSpawn], SpawnLocation, SpawnRotation, spawnParameters);
					if (SpawnedActor) SpawnedItemCollection.Add(SpawnedActor);
				}
			}

		}
	}
	else if (UKismetMathLibrary::InRange_FloatFloat(SpawnChances, SpawnCoinPercent, 1.0F))
	{
		const float SpawnGemsChances = FMath::FRandRange(0.0f, 1.0f);
		if (SpawnGemsChances < SpawnpercenGems)
		{
			int IndexToSpawn = FMath::RandHelper(SpawnGems.Num());
			if (SpawnGems[IndexToSpawn]) // Check if the class at the random index is valid before spawning
			{
				//Gems spawn rare
				FVector NewSpawnLocation = SpawnLocation; // Adjust the X-axis for distance between spawns
				FRotator SpawnRotation = FRotator(0, 0, 0); // Modify this if you need dynamic rotation
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnGems[IndexToSpawn], NewSpawnLocation, SpawnRotation, spawnParameters);
				if (SpawnedActor) SpawnedItemCollection.Add(SpawnedActor);
			}
		}
		else
		{
			if (BisObstacleSpawn && SpawnCoins.Num() > 0)
			{
				const int NumSpawns = 3;
				const float SpawnDistance = 200.0f; // Adjust this to set the distance between spawns

				for (int i = 0; i < NumSpawns; ++i)
				{
					int IndexToSpawn = FMath::RandHelper(SpawnCoins.Num()); // Get a random index from the SpawnCoins array

					if (SpawnCoins[IndexToSpawn]) // Check if the class at the random index is valid before spawning
					{
						// Calculate the new spawn location with some distance offset
						FVector NewSpawnLocation = SpawnLocation + FVector(SpawnDistance * i, 0.0f, 0.0f); // Adjust the X-axis for distance between spawns

						// Spawn the actor at the new location and with no rotation (you can adjust rotation if needed)
						FRotator SpawnRotation = FRotator(0, 0, 0); // Modify this if you need dynamic rotation
						AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnCoins[IndexToSpawn], NewSpawnLocation, SpawnRotation, spawnParameters);
						if (SpawnedActor) SpawnedItemCollection.Add(SpawnedActor);
					}
				}
			}
		}
	}
}

void AFloorscape::DestroySpawnedItems()
{
	// Iterate through the spawned items
	for (int32 i = SpawnedItemCollection.Num() - 1; i >= 0; --i)
	{
		AActor* SpawnedActor = SpawnedItemCollection[i];

		// Check if the actor is valid before destroying
		if (IsValid(SpawnedActor))
		{
			SpawnedActor->Destroy();  // Destroy the actor
			SpawnedItemCollection.RemoveAt(i);  // Optionally remove from array
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid"));
			SpawnedItemCollection.RemoveAt(i);  // Remove invalid (destroyed) actor from the array
		}
	}
	SpawnedItemCollection.Empty();  // Optionally clear the array after destroying all actors
}


	////if (UKismetMathLibrary::RandomBoolWithWeight(0.5))
	////{
	////	//if (UKismetMathLibrary::RandomBoolWithWeight(0.6))
	////	//{
	//		int indextospawn = FMath::RandHelper(obstaclesArray.Num());

	//		if (obstaclesArray[indextospawn])
	//		{
	//			GetWorld()->SpawnActor<AActor>(obstaclesArray[indextospawn], Location, FRotator(0, 0, 0));

	//		}


	//	//}
	//	//else
	//	//{
	//		//GetWorld()->SpawnActor<Aobstacles>(obstaclesArray[1], Location, FRotator(0, 0, 0));

	//	//}
	////}