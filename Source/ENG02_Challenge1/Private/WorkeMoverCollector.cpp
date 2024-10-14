// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkeMoverCollector.h"

// Sets default values
AWorkeMoverCollector::AWorkeMoverCollector()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorkeMoverCollector::BeginPlay()
{
	Super::BeginPlay();

	this->ResourceTracker = Cast<UPlayerResourceTracker>(GetGameInstance());

	this->DropoffVec = this->DropoffPoint.GetLocation();
	this->CollectVec = this->CollectionPoint.GetLocation();

	this->carryingResource = this->ResourceSource->ResourceType;

}

// Called every frame
void AWorkeMoverCollector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->isGoingToDropoff) {
		this->MoveActorTo(this->DropoffVec);
		if (this->RobotActor->GetTransform().GetLocation() == this->DropoffVec) {
			this->ResourceTracker->Collect(this->Upgrader->GetResourceCollected(this->carryingResource), this->carryingResource);
			this->isGoingToDropoff = false;
		}
	}
	else {
		this->MoveActorTo(this->CollectVec);
		if (this->RobotActor->GetTransform().GetLocation() == this->CollectVec) {
			this->isGoingToDropoff = true;
		}
	}
}

void AWorkeMoverCollector::MoveActorTo(FVector targetPoint) {
	FVector currentPosition = this->RobotActor->GetTransform().GetLocation();

	if (FVector::Distance(currentPosition, targetPoint) <= errorDist)
		currentPosition = targetPoint;
	else {
		currentPosition = FMath::Lerp(currentPosition, targetPoint,
			(this->MoveSpeed * (1 + this->Upgrader->GetWorkerSpeedMult())) /
			FVector::Distance(currentPosition, targetPoint)
		);
	}

	this->RobotActor->SetActorLocation(currentPosition);
}

