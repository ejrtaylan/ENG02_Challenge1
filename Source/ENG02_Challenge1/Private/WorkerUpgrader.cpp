// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkerUpgrader.h"

// Sets default values
UWorkerUpgrader::UWorkerUpgrader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;	

}

// Called when the game starts or when spawned
void UWorkerUpgrader::BeginPlay()
{
	Super::BeginPlay();
	
	this->ResourceTracker = Cast<UPlayerResourceTracker>(GetWorld()->GetGameInstance());
	this->triggerVolume->SetWorldLocation(this->GetOwner()->GetActorLocation() + this->triggerVolume->GetRelativeLocation());
}

// Called every frame
void UWorkerUpgrader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* thePlayer = this->GetWorld()->GetFirstPlayerController()->GetPawn();
	if (this->triggerVolume->IsOverlappingActor(thePlayer)) {

		if (!this->WasInsideVolume && this->WorkerLevel < MAX_WORKER_LEVEL) {
			this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, -5.0f));
			this->WasInsideVolume = true;
			this->TryUpgradeWorker();
		}
	}
	else {
		if(this->WasInsideVolume)
			this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, 5.0f));
		this->WasInsideVolume = false;
	}

	if (this->WorkerLevel >= MAX_WORKER_LEVEL)
		this->DeactivateUpgrader();
}

bool UWorkerUpgrader::TryUpgradeWorker() {
	if (this->WorkerLevel >= MAX_WORKER_LEVEL)
		return false;

	if (
		this->ResourceTracker->CanSpend(nextUpgradeCostWood, UPlayerResourceTracker::Resource::WOOD) && 
		this->ResourceTracker->CanSpend(nextUpgradeCostStone, UPlayerResourceTracker::Resource::STONE)
	) {
		this->ResourceTracker->Spend(nextUpgradeCostWood, UPlayerResourceTracker::Resource::WOOD);
		this->ResourceTracker->Spend(nextUpgradeCostStone, UPlayerResourceTracker::Resource::STONE);

		this->WorkerLevel++;
		if (this->WorkerLevel == 0) this->ActivateWorker();
		this->UpdateUpgradeCosts();
		return true;
	}

	return false;
}

int UWorkerUpgrader::GetResourceCollected(UPlayerResourceTracker::Resource type) {
	if (this->WorkerLevel == 0) return 0;

	switch (type) {
	case UPlayerResourceTracker::Resource::WOOD:
		return 5 + (5 * this->WorkerLevel);
	case UPlayerResourceTracker::Resource::STONE:
		return 4 * this->WorkerLevel;
	}

	return 0;
}

float UWorkerUpgrader::GetWorkerSpeedMult() {
	if (this->WorkerLevel == 0) return -1.0f;
	if (this->WorkerLevel <= 2) return 0.0f;
	if (this->WorkerLevel == 3) return 0.05f;
	if (this->WorkerLevel == 4) return 0.1f;
	return 0.15f;
}

void UWorkerUpgrader::UpdateUpgradeCosts() {
	switch (this->WorkerLevel) {
	case 1:
		this->nextUpgradeCostWood = 10;
		this->nextUpgradeCostStone = 10;
		break;
	case 2:
		this->nextUpgradeCostWood = 15;
		this->nextUpgradeCostStone = 10;
		break;
	case 3:
		this->nextUpgradeCostWood = 20;
		this->nextUpgradeCostStone = 15;
		break;
	case 4:
		this->nextUpgradeCostWood = 30;
		this->nextUpgradeCostStone = 20;
		break;
	}
}

void UWorkerUpgrader::ActivateWorker() {
	this->ResourceTracker->AddWorker();
}

void UWorkerUpgrader::DeactivateUpgrader() {
	this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, -10.0f));
}