// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WorkerUpgrader.h"
#include "ResourceTracker.h"
#include "ResourceSource.h"
#include "WorkeMoverCollector.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENG02_CHALLENGE1_API UWorkeMoverCollector: public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UWorkeMoverCollector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveActorTo(FVector targetPoint);

	AActor* RobotActor;

	UPROPERTY(EditAnywhere)
	AActor* Base;

	UPROPERTY(EditAnywhere)
	AActor* UpgraderPlate;

	UPROPERTY(EditAnywhere)
	AActor* Resource;

	UWorkerUpgrader* Upgrader;
	UResourceSource* ResourceSource;
	FTransform CollectionPoint;
	FTransform DropoffPoint;

	UPlayerResourceTracker* ResourceTracker;
	UPlayerResourceTracker::Resource carryingResource;

	FVector CollectVec;
	FVector DropoffVec;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.0f;

	float errorDist = 1.2f;
	bool isGoingToDropoff = false;
};
