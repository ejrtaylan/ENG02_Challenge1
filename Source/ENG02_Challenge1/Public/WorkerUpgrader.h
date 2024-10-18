// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerResourceTracker.h"	
#include "Components/BoxComponent.h"
#include "WorkerUpgrader.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENG02_CHALLENGE1_API UWorkerUpgrader : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UWorkerUpgrader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const int MAX_WORKER_LEVEL = 5;

	UPROPERTY(EditAnywhere)
	UBoxComponent* triggerVolume = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* targetWorker = nullptr;

	UPlayerResourceTracker* ResourceTracker = nullptr;

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
