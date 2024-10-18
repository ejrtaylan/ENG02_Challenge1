// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerResourceTracker.h"
#include "SiloBuyer.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENG02_CHALLENGE1_API USiloBuyer : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USiloBuyer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const int SILO_COST = 50;
	UPlayerResourceTracker::Resource costType = UPlayerResourceTracker::Resource::WOOD;

	bool WasInsideVolume = false;
	bool BoughtAlready = false;

	UPlayerResourceTracker* ResourceTracker;

	UPROPERTY(EditAnywhere)
	UBoxComponent* triggerVolume;

	UPROPERTY(EditAnywhere)
	AActor* targetSilo;

	bool TryBuySilo();
	void ActivateSilo();
	void DeactivateBuyer();
};
