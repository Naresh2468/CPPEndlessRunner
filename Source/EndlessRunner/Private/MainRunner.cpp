// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunner/Public/MainRunner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"
#include "GMRunner.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//#include "InputActionValue.h"
// Sets default values
AMainRunner::AMainRunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	bUseControllerRotationYaw = false;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraArm);


	///Component Default Values Preset
	CameraArm->TargetArmLength = 350.f;
	CameraArm->SocketOffset = FVector(0,0,100.f);
	CameraArm->bUsePawnControlRotation = true;

	MainCamera->bUsePawnControlRotation = false;
	bIsSliding = false;

}

// Called when the game starts or when spawned
void AMainRunner::BeginPlay()
{
	Super::BeginPlay();
	CharacterSelected();
	MainGameMode = Cast<AGMRunner>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AMainRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerDeath)
	{
		MoveForward();
	}

}

void AMainRunner::MoveForward()//float value)
{
	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch = 0.0f;
	CurrentRotation.Roll = 0.0f;
	AddMovementInput(CurrentRotation.Vector());

}
void AMainRunner::MoveRightSide()
{
	NextLane = UKismetMathLibrary::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
}
void AMainRunner::MoveLeftSide()
{
	NextLane = UKismetMathLibrary::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
}
void AMainRunner::MoveSlideDown()
{
	static FVector Impusle = FVector(0, 0, MoveDown);
	GetCharacterMovement()->AddImpulse(Impusle, true);

}
void AMainRunner::MoveJumpStart()
{
	Jump();
}
void AMainRunner::MoveJumpStop()
{
	StopJumping();
}


void AMainRunner::ChangeLaneUpdate(const float value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(MainGameMode->LaneLocationPlayer[CurrentLane], MainGameMode->LaneLocationPlayer[NextLane], value);
	SetActorLocation(Location);
}
void AMainRunner::ChangeLaneFinished()
{
	CurrentLane = NextLane;
	UE_LOG(LogTemp, Warning, TEXT("Lane Value:- %d"), CurrentLane);
}

void AMainRunner::PlayerDeathProcess()
{
	const FVector location = GetActorLocation();
	UWorld* world = GetWorld();
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(world, DeathSound,location);
	}
	PlayerDeath = true; 
	GetCharacterMovement()->DisableMovement();
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	if (PlayerMesh)
	{
		// Set the mesh to simulate physics for ragdoll effect
		PlayerMesh->SetSimulatePhysics(true);
		PlayerMesh->WakeAllRigidBodies(); // Wake up the rigid bodies for the physics simulation to take effect
		// Optionally, you can apply an impulse to the mesh to add force at death location
		//FVector Impulse = FVector(0, 0, 1000); // Modify impulse as needed
		//PlayerMesh->AddImpulse(Impulse);
		// 
		//->Note : - mesh shoudl have the physics assets assign. or else it would not work.

		MainGameMode->GameOver(); // Game over screen.
	}
}

void AMainRunner::AddCoins()
{
	MainGameMode->AddCoin();
}
void AMainRunner::AddGems()
{
	MainGameMode->AddGems();
}

void AMainRunner::StartSlide()
{
	
	if (bIsSliding || GetCharacterMovement()->IsFalling())
	{
		MoveSlideDown();
		return;
	}
	bIsSliding = true;
	if (SlideMontage)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AMainRunner::EndSlide);
			AnimInstance->Montage_Play(SlideMontage, PlayRate); // You can modify the speed (1.0f is normal speed)
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate);
		}	
		TimeSlide(true);
		//SmoothCapsuleAndMeshChange(SlideCapsuleHeight, MeshOffset);
	}
}


void AMainRunner::EndSlide(UAnimMontage* Montage,bool bInterrupted)
{
	bIsSliding = false;
	TimeSlide(false);
}

// Called to bind functionality to input
void AMainRunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(PlayerRight, IE_Pressed, this, &AMainRunner::MoveRightSide);
	PlayerInputComponent->BindAction(PlayerLeft, IE_Pressed, this, &AMainRunner::MoveLeftSide);

	PlayerInputComponent->BindAction(PlayerJump, IE_Pressed, this, &AMainRunner::MoveJumpStart);
	PlayerInputComponent->BindAction(PlayerJump, IE_Released, this, &AMainRunner::MoveJumpStop);

	PlayerInputComponent->BindAction(PlayerSlide, IE_Pressed, this, &AMainRunner::StartSlide);

}

