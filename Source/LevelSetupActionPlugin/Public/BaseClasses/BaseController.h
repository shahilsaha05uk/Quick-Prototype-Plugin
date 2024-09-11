// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "BaseController.generated.h"

UCLASS()
class LEVELSETUPACTIONPLUGIN_API ABaseController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
