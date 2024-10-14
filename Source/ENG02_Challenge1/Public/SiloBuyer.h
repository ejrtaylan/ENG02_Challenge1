// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "PlayerResourceTracker.h"
#include "SiloBuyer.generated.h"

UCLASS()
class ENG02_CHALLENGE1_API ASiloBuyer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASiloBuyer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const int SILO_COST = 50;
	UPlayerResourceTracker::Resource costType = UPlayerResourceTracker::Resource::WOOD;

	bool WasInsideVolume = false;

	UPlayerResourceTracker* ResourceTracker;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* triggerVolume;

	UPROPERTY(EditAnywhere)
	AActor* targetSilo;

	bool TryBuySilo();
	void ActivateSilo();
	void DeactivateBuyer();
};
