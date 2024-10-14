



// Fill out your copyright notice in the Description page of Project Settings.


#include "SiloBuyer.h"

// Sets default values
USiloBuyer::USiloBuyer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void USiloBuyer::BeginPlay()
{
	Super::BeginPlay();

	this->ResourceTracker = Cast<UPlayerResourceTracker>(GetGameInstance());
}

// Called every frame
void USiloBuyer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

bool USiloBuyer::TryBuySilo(){
	if (
		this->ResourceTracker->CanSpend(SILO_COST, costType)
	) {
		this->ResourceTracker->Spend(SILO_COST, costType);

		ResourceTracker->AddSilo();
		this->ActivateSilo();
		return true;
	} 

	return false;
}

void USiloBuyer::ActivateSilo() {

}

void USiloBuyer::DeactivateBuyer() {

}

