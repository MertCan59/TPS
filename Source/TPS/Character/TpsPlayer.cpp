// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Character/TpsPlayer.h"

// Sets default values
ATpsPlayer::ATpsPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlayerRoot=CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRoot"));
	PlayerRoot->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerRoot)
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

