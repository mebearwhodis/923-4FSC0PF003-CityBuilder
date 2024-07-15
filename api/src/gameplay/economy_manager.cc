#include "gameplay/economy_manager.h"

void EconomyManager::AddFood(int amount)
{
	food_ += amount;
}

void EconomyManager::AddWood(int amount)
{
	wood_ += amount;
}

void EconomyManager::AddStone(int amount)
{
	stone_ += amount;
}

void EconomyManager::AddPopulation(int amount)
{
	current_population_ += amount;
}

void EconomyManager::AddTotalPopulation(int amount)
{
	total_population_ += amount;
}

void EconomyManager::set_current_house_cost(int amount)
{
	current_house_cost_ = amount;
}

void EconomyManager::set_current_forge_cost(int amount)
{
	current_forge_cost_ = amount;
}

void EconomyManager::set_current_sawmill_cost(int amount)
{
	current_sawmill_cost_ = amount;
}

void EconomyManager::set_current_storage_cost(int amount)
{
	current_storage_cost_ = amount;
}

int EconomyManager::food() const
{
	return food_;
}

int EconomyManager::wood() const
{
	return wood_;
}

int EconomyManager::stone() const
{
	return stone_;
}

int EconomyManager::current_population() const
{
	return current_population_;
}

int EconomyManager::total_population() const
{
	return total_population_;
}

int EconomyManager::current_house_cost() const
{
	return current_house_cost_;
}

int EconomyManager::current_forge_cost() const
{
	return current_forge_cost_;
}

int EconomyManager::current_sawmill_cost() const
{
	return current_sawmill_cost_;
}

int EconomyManager::current_storage_cost() const
{
	return current_storage_cost_;
}

