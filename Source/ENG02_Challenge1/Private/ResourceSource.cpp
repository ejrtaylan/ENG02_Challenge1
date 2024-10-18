
// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceSource.h"

// Sets default values
UResourceSource::UResourceSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UResourceSource::BeginPlay()
{
	Super::BeginPlay();
	
	if (isStone) {
		this->ResourceType = UPlayerResourceTracker::Resource::STONE;
	}
	else {
		this->ResourceType = UPlayerResourceTracker::Resource::WOOD;
	}
}

// Called every frame
void UResourceSource::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

