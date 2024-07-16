#ifndef API_ GAMEPLAY_ECONOMY_MANAGER_H_
#define API_ GAMEPLAY_ECONOMY_MANAGER_H_

class EconomyManager
{
	int food_ = 500;
	int wood_ = 500;
	int stone_ = 500;
	int current_population_ = 0;
	int total_population_ = 10;

	int current_house_cost_ = 100;
	int current_forge_cost_ = 100;
	int current_sawmill_cost_ = 100;
	int current_storage_cost_ = 100;

public:
	EconomyManager() = default;
	void AddFood(int amount);
	void AddWood(int amount);
	void AddStone(int amount);
	void AddPopulation(int amount);
	void AddTotalPopulation(int amount);

	void set_current_house_cost(int amount);
	void set_current_forge_cost(int amount);
	void set_current_sawmill_cost(int amount);
	void set_current_storage_cost(int amount);

	[[nodiscard]] int food() const;
	[[nodiscard]] int wood() const;
	[[nodiscard]] int stone() const;
	[[nodiscard]] int current_population() const;
	[[nodiscard]] int total_population() const;
	[[nodiscard]] int current_house_cost() const;
	[[nodiscard]] int current_forge_cost() const;
	[[nodiscard]] int current_sawmill_cost() const;
	[[nodiscard]] int current_storage_cost() const;
};
#endif // API_ GAMEPLAY_ECONOMY_MANAGER_H_
