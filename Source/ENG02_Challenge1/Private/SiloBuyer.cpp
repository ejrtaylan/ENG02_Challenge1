



// Fill out your copyright notice in the Description page of Project Settings.


#include "SiloBuyer.h"

// Sets default values
ASiloBuyer::ASiloBuyer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASiloBuyer::BeginPlay()
{
	Super::BeginPlay();

	this->ResourceTracker = Cast<UPlayerResourceTracker>(GetGameInstance());
}

// Called every frame
void ASiloBuyer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* thePlayer = this->GetWorld()->GetFirstPlayerController()->GetPawn();
	if (this->triggerVolume->IsOverlappingActor(thePlayer)) {
		if (!this->WasInsideVolume) {
			this->WasInsideVolume = true;
			if (this->TryBuySilo())
				this->DeactivateBuyer();
		}
	}
	else {
		this->WasInsideVolume = false;
	}
}

bool ASiloBuyer::TryBuySilo(){
	if (
		this->ResourceTracker->CanSpend(SILO_COST, costType)
	) {
		this->ResourceTracker->Spend(SILO_COST, costType);

		this->ActivateSilo();
		return true;
	} 

	return false;
}

void ASiloBuyer::ActivateSilo() {

}

void ASiloBuyer::DeactivateBuyer() {

}

