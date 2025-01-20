// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TpsPlayer.generated.h"

class USceneComponent;
UCLASS()
class TPS_API ATpsPlayer : public APawn
{
	GENERATED_BODY()


public:
	ATpsPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	virtual void BeginPlay() override;

public:

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PlayerRoot;
	
};
