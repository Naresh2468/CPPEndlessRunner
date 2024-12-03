// Fill out your copyright notice in the Description page of Project Settings.


#include "Gems.h"
#include "MainRunner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
// Sets default values
AGems::AGems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(SceneRoot);
	MainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GemCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleCollision"));
	GemCollision->SetupAttachment(SceneRoot);
	GemCollision->SetCollisionProfileName("OverLapOnlyPawn");

	RotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotationComponent->RotationRate = FRotator(0, 180, 0);
}

// Called when the game starts or when spawned
void AGems::BeginPlay()
{
	Super::BeginPlay();
	GemCollision->OnComponentBeginOverlap.AddDynamic(this, &AGems::CoinOverlap);
}
void AGems::CoinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		AMainRunner* MainPlayer = Cast<AMainRunner>(OtherActor);
		if (GemCollectSound)  // Make sure the sound is valid
		{
			UGameplayStatics::PlaySoundAtLocation(this, GemCollectSound, MainMesh->GetComponentLocation());
		}
		MainPlayer->AddGems();
		Destroy();
	}
}

