// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerResourceTracker.h"

bool UPlayerResourceTracker::CanSpend(int amount, Resource type) {
	return amount <= GetCurrResource(type);
}

void UPlayerResourceTracker::Spend(int amount, Resource type) {
	switch (type) {
	case Resource::WOOD:
		CurrWoodCount -= amount;
		break;
	case Resource::STONE:
		CurrStoneCount -= amount;
		break;
	}
}

void UPlayerResourceTracker::Collect(int amount, Resource type) {
	int newTotal = GetCurrResource(type) + amount;
	if (newTotal <= GetMaxResource(type)) {
		SetResourceCount(newTotal, type);
	}
	else SetResourceCount(GetMaxResource(type), type);
}

void UPlayerResourceTracker::SetResourceCount(int amount, Resource type) {
	switch (type) {
	case Resource::WOOD:
		CurrWoodCount = amount;
		break;
	case Resource::STONE:
		CurrStoneCount = amount;
		break;
	}
}

void UPlayerResourceTracker::AddSilo() {
	CurrSiloCount++;
}

void UPlayerResourceTracker::AddWorker() {
	CurrWorkerCount++;
}

int UPlayerResourceTracker::GetWorkerCount() {
	return CurrWorkerCount;
}

int UPlayerResourceTracker::GetSiloCount() {
	return CurrSiloCount;
}

int UPlayerResourceTracker::GetCurrResource(Resource type) {
	switch (type) {
	case Resource::WOOD:
		return CurrWoodCount;
	case Resource::STONE:
		return CurrStoneCount;
	}

	return -1;
}

int UPlayerResourceTracker::GetMaxResource(Resource type) {
	switch (type) {
	case Resource::WOOD:
		return CurrSiloCount * PER_SILO_WOOD;
	case Resource::STONE:
		return CurrSiloCount * PER_SILO_STONE;
	}

	return -1;
}