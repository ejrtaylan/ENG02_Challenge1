// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkeMoverCollector.h"

// Sets default values
UWorkeMoverCollector::UWorkeMoverCollector()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UWorkeMoverCollector::BeginPlay()
{
	Super::BeginPlay();

	this->ResourceTracker = Cast<UPlayerResourceTracker>(GetWorld()->GetGameInstance());

	this->Upgrader = this->UpgraderPlate->GetComponentByClass<UWorkerUpgrader>();
	this->ResourceSource = this->Resource->GetComponentByClass<UResourceSource>();
	this->CollectionPoint = this->Resource->GetTransform();
	this->DropoffPoint = this->Base->GetTransform();

	this->DropoffVec = this->DropoffPoint.GetLocation();
	this->CollectVec = this->CollectionPoint.GetLocation();

	this->carryingResource = this->ResourceSource->ResourceType;
	this->errorDist = this->MoveSpeed * 1.1;

	this->RobotActor = this->GetOwner();

}

// Called every frame
void UWorkeMoverCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

void UWorkeMoverCollector::MoveActorTo(FVector targetPoint) {
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

