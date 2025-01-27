	// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS/Public/Characters/Player/TpsPlayer.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "TPS/Public/Controller/PlayerDefaultController.h"
#include "TPS/Public/Characters/Player/Movement/Movement.h"
#include "Characters/Player/Movement/Jump.h"

// Sets default values
ATpsPlayer::ATpsPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerRootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRootComponent"));
	SetRootComponent(PlayerRootComponent);

	PlayerCapsule=GetCapsuleComponent();
	PlayerCapsule->SetupAttachment(GetRootComponent());
	
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(PlayerCapsule);
	TargetArmLength=300.f;
	
	ViewCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	MovementController=CreateDefaultSubobject<UMovement>(TEXT("MovementController"));
	JumpController=CreateDefaultSubobject<UJump>(TEXT("JumpController"));
}
void ATpsPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ATpsPlayer::PostInitProperties()
{
	Super::PostInitProperties();
	CameraBoom->TargetArmLength=this->TargetArmLength;
	CameraBoom->SocketOffset=FVector(0.0f,CameraYOffset,CameraHeight);
}

// Called when the game starts or when spawned
void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();
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
	
	APlayerDefaultController* NewController = Cast<APlayerDefaultController>(GetController());
	UMovement* Movement = Cast<UMovement>(MovementController);
	UJump* Jump=Cast<UJump>(JumpController);
	
	checkf(NewController,TEXT("Controller has not been set"));
	checkf(Movement,TEXT("Movement controller has not been found"));
	checkf(Jump,TEXT("Jump controller has not been found"));
	
	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(NewController->GetMovementAction(),ETriggerEvent::Triggered,Movement,&UMovement::Move);
		EnhancedInputComponent->BindAction(NewController->GetLookAction(),ETriggerEvent::Triggered,Movement,&UMovement::Look);
		
		EnhancedInputComponent->BindAction(NewController->GetJumpAction(),ETriggerEvent::Started,Jump,&UJump::Jump);
		EnhancedInputComponent->BindAction(NewController->GetJumpAction(),ETriggerEvent::Completed,Jump,&UJump::StopJumping);
	}
}
void ATpsPlayer::SetCharacterState(ECharacterState NewState)
{
	CharacterState=NewState;
}
