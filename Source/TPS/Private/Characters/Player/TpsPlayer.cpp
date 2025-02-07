// Fill out your copyright notice in the Description page of Project Settings.

#include "TPS/Public/Characters/Player/TpsPlayer.h"
#include "EnhancedInputComponent.h"
#include "Animations/PlayerAnimations/PlayerAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "TPS/Public/Controller/PlayerDefaultController.h"
#include "TPS/Public/Characters/Player/Movement/Movement.h"
#include "Characters/Player/Movement/Jump.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapon/Flashlight.h"
#include "Items/Weapon/WeaponBase.h"
#include "Kismet/KismetMathLibrary.h"

ATpsPlayer::ATpsPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
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

void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();
	PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this,&ATpsPlayer::OnSphereOverlap);
}

void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bIsGrounded=!GetCharacterMovement()->IsFalling();
	
	if (GetCharacterGrounded())
	{
		auto VelocityXY=GetVelocity();
		float Speed=UKismetMathLibrary::VSizeXY(VelocityXY);
		if (Speed > 0.1f)
		{
			SetCharacterState(ECharacterState::ECS_MovementState);
		}else
		{
			SetCharacterState(ECharacterState::ECS_Idle);
		}
	}
}

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
		EnhancedInputComponent->BindAction(NewController->GetRunningAction(),ETriggerEvent::Triggered,Movement,&UMovement::SprintStart);
		EnhancedInputComponent->BindAction(NewController->GetRunningAction(),ETriggerEvent::Completed,Movement,&UMovement::SprintStop);
		
		EnhancedInputComponent->BindAction(NewController->GetLookAction(),ETriggerEvent::Triggered,Movement,&UMovement::Look);
		
		EnhancedInputComponent->BindAction(NewController->GetJumpAction(),ETriggerEvent::Started,Jump,&UJump::PlayMontage);
		//EnhancedInputComponent->BindAction(NewController->GetJumpAction(),ETriggerEvent::Completed,Jump,&UJump::StopJump);
	}
}

void ATpsPlayer::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWeaponBase* OverlappingWeapon=Cast<AWeaponBase>(OtherActor);
	if(OverlappingWeapon)
	{
		if (OverlappingWeapon->IsA<AFlashlight>())
		{
			OverlappingWeapon->Equip(GetMesh(),FName("LeftHandSocket"),this,this);
			bLeftHandIsFull=true;
		}else
		{
			OverlappingWeapon->Equip(GetMesh(),FName("RightHandSocket"),this,this);
			bHasWeapon=true;	
		}
		OverlappingWeapon->SetOwner(this);
		OverlappingWeapon->SetInstigator(this);
		EquippedWeapon = OverlappingWeapon;
		CharacterIdleState=ECharacterIdleState::ECS_OneHandedEquipped;
		EquippedWeapon->GetWeaponOverlapSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		EquippedWeapon->GetWeaponOverlapSphere()->SetCollisionResponseToAllChannels(ECR_Ignore);
		EquippedWeapons.AddUnique(EquippedWeapon);
		OverlappingWeapon = nullptr;
	}
}