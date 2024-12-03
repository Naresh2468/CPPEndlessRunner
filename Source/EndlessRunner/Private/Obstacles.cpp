// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunner/Public/Obstacles.h"
#include "MainRunner.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
// Sets default values
AObstacles::AObstacles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(SceneRoot);
	MainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ObstacleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollision"));
	ObstacleCollision->SetupAttachment(SceneRoot);
	ObstacleCollision->SetCollisionProfileName("OverLapOnlyPawn");
}

// Called when the game starts or when spawned
void AObstacles::BeginPlay()
{
	Super::BeginPlay();
	ObstacleCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacles::ObstacleOverlap);
}

void AObstacles::ObstacleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		AMainRunner* MainPlayer = Cast<AMainRunner>(OtherActor);
		if (ObstacleSound)  // Make sure the sound is valid
		{
			UGameplayStatics::PlaySoundAtLocation(this, ObstacleSound, MainMesh->GetComponentLocation());
		}
		MainPlayer->PlayerDeathProcess();
	}
}

