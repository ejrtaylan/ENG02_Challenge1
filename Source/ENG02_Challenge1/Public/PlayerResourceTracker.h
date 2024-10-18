// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerResourceTracker.generated.h"

/**
 * 
 */
UCLASS()
class ENG02_CHALLENGE1_API UPlayerResourceTracker : public UGameInstance
{
	GENERATED_BODY()
	
private:
	const int INIT_WOOD_COUNT = 150;
	const int INIT_STONE_COUNT = 0;
	const int INIT_SILO_COUNT = 0;
	const int PER_SILO_WOOD = 100;
	const int PER_SILO_STONE = 25;

public:
	UPROPERTY(BlueprintReadWrite)
	int CurrWoodCount = INIT_WOOD_COUNT;
	UPROPERTY(BlueprintReadWrite)
	int CurrStoneCount = INIT_STONE_COUNT;
	UPROPERTY(BlueprintReadWrite)
	int CurrSiloCount = INIT_SILO_COUNT;
	UPROPERTY(BlueprintReadWrite)
	int CurrWorkerCount = 0;

	enum Resource {
		WOOD, STONE, NONE
	};

	bool CanSpend(int amount, Resource type);
	void Spend(int amount, Resource type);
	void Collect(int amount, Resource type);
	void SetResourceCount(int amount, Resource type);
	void AddSilo();
	void AddWorker();

	int GetWorkerCount();
	int GetSiloCount();
	int GetCurrResource(Resource type);
	int GetMaxResource(Resource type);
};
