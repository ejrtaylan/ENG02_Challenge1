
// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceSource.h"

// Sets default values
AResourceSource::AResourceSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourceSource::BeginPlay()
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
void AResourceSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

