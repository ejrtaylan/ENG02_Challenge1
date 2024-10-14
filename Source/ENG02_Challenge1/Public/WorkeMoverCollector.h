// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WorkerUpgrader.h"
#include "ResourceTracker.h"
#include "ResourceSource.h"
#include "WorkeMoverCollector.generated.h"

UCLASS()
class ENG02_CHALLENGE1_API AWorkeMoverCollector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorkeMoverCollector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveActorTo(FVector targetPoint);

	UPROPERTY(EditAnywhere);
	AActor* RobotActor;

	UPROPERTY(EditAnywhere)
	FTransform CollectionPoint;

	UPROPERTY(EditAnywhere)
	FTransform DropoffPoint;

	UPROPERTY(EditAnywhere)
	AWorkerUpgrader* Upgrader;

	UPROPERTY(EditAnywhere)
	AResourceSource* ResourceSource;

	UPlayerResourceTracker* ResourceTracker;
	UPlayerResourceTracker::Resource carryingResource;

	FVector CollectVec;
	FVector DropoffVec;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;

	float errorDist = 1.2f;
	bool isGoingToDropoff = false;
};
