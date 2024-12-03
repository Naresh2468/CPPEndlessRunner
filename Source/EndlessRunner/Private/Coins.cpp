// Fill out your copyright notice in the Description page of Project Settings.


#include "Coins.h"
#include "MainRunner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
// Sets default values
ACoins::ACoins()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(SceneRoot);
	MainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CoinCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollision"));
	CoinCollision->SetupAttachment(SceneRoot);
	CoinCollision->SetCollisionProfileName("OverLapOnlyPawn");

	RotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotationComponent->RotationRate = FRotator(0, 180, 0);
}

// Called when the game starts or when spawned
void ACoins::BeginPlay()
{
	Super::BeginPlay();
	CoinCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoins::CoinOverlap);
}

void ACoins::CoinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		AMainRunner* MainPlayer = Cast<AMainRunner>(OtherActor);
		MainPlayer->AddCoins();
		if (CoinCollectSound)  // Make sure the sound is valid
		{
			UGameplayStatics::PlaySoundAtLocation(this, CoinCollectSound, MainMesh->GetComponentLocation());
		}
		Destroy();
	}
}


