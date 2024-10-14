// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerResourceTracker.h"
#include "Engine/TriggerVolume.h"
#include "WorkerUpgrader.generated.h"

UCLASS()
class ENG02_CHALLENGE1_API AWorkerUpgrader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkerUpgrader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const int MAX_WORKER_LEVEL = 5;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* triggerVolume;

	UPROPERTY(EditAnywhere)
	AActor* targetWorker;

	UPlayerResourceTracker* ResourceTracker;

	int WorkerLevel = 0;
	
	int nextUpgradeCostWood = 20;
	int nextUpgradeCostStone = 0;

	bool WasInsideVolume = false;

	bool TryUpgradeWorker();
	int GetResourceCollected(UPlayerResourceTracker::Resource type);
	float GetWorkerSpeedMult();

	void UpdateUpgradeCosts();
	void ActivateWorker();
	void DeactivateUpgrader();
};
