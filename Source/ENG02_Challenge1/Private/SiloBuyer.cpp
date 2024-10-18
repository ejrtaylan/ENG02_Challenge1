



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

	this->ResourceTracker = Cast<UPlayerResourceTracker>(this->GetWorld()->GetGameInstance());
	this->triggerVolume->SetWorldLocation(this->GetOwner()->GetActorLocation() + this->triggerVolume->GetRelativeLocation());

}

// Called every frame
void USiloBuyer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* thePlayer = this->GetWorld()->GetFirstPlayerController()->GetPawn();
	if (this->triggerVolume->IsOverlappingActor(thePlayer)) {
		if (!this->WasInsideVolume && !this->BoughtAlready) {
			this->WasInsideVolume = true;
			this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, -5.0f));
			if (this->TryBuySilo())
				this->DeactivateBuyer();
		}
	}
	else {
		if(this->WasInsideVolume)
			this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, 5.0f));
		this->WasInsideVolume = false;
	}
}

bool USiloBuyer::TryBuySilo(){
	if (this->BoughtAlready)
		return false;

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
	this->GetOwner()->SetActorRelativeLocation(this->GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, -20.0f));
	this->BoughtAlready = true;
}

