// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Character/TpsPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ATpsPlayer::ATpsPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlayerRootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRootComponent"));
	SetRootComponent(PlayerRootComponent);
	
	PlayerSkeletalMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	PlayerSkeletalMesh->SetupAttachment(PlayerRootComponent);

	PlayerCapsuleCollider=CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsuleCollider"));
	PlayerCapsuleCollider->SetupAttachment(PlayerRootComponent);

	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(PlayerRootComponent);
	TargetArmLength=300.f;
	
	ViewCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}

void ATpsPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CameraBoom->TargetArmLength=this->TargetArmLength;
	CameraBoom->TargetOffset=FVector(0.0f,0.0f,CameraHeight);
}
// Called when the game starts or when spawned
void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerRootComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Game Started");
		}
	}
}

// Called every frame
void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

