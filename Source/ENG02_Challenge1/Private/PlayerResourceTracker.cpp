// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerResourceTracker.h"

bool UPlayerResourceTracker::TrySpend(int amount, Resource type) {
	if (amount <= GetCurrResource(type)) {
		switch (type) {
		case Resource::WOOD:
			CurrWoodCount -= amount;
			break;
		case Resource::STONE:
			CurrStoneCount -= amount;
			break;
		}

		return true;
	} 

	return false;
}

void UPlayerResourceTracker::Collect(int amount, Resource type) {
	int newTotal = GetCurrResource(type) + amount;
	if (newTotal <= GetMaxResource(type)) {
		SetResourceCount(newTotal, type);
	}
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