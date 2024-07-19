#ifndef API_GAMEPLAY_ECONOMY_MANAGER_H_
#define API_GAMEPLAY_ECONOMY_MANAGER_H_
#include <nlohmann/json.hpp>

class EconomyManager
{
	//TODO: END tweak default values
	int food_ = 10000;
	int wood_ = 50000;
	int stone_ = 50000;
	int current_population_ = 0;
	int total_population_ = 100;

	int current_house_cost_ = 10;
	int current_forge_cost_ = 10;
	int current_sawmill_cost_ = 10;
	int current_storage_cost_ = 10;
	float cost_multiplier_ = 1.2f;

	bool text_to_update_ = true;

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
	[[nodiscard]] float cost_multiplier() const;
	void ClearAll();

	bool text_to_update() const { return text_to_update_; }
	void set_text_to_update(bool value) { text_to_update_ = value; }
};
#endif // API_GAMEPLAY_ECONOMY_MANAGER_H_
