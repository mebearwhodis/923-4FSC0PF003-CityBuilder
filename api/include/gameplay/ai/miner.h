#ifndef API_GAMEPLAY_AI_MINER_H_
#define API_GAMEPLAY_AI_MINER_H_
#include "walker.h"
#include "behaviour_tree/tree.h"
#include "pathfinding/pathfinder.h"
#include "world_generation/tilemap.h"

class Miner : public Walker
{
private:
	Tilemap& tilemap_;
	sf::Vector2f home_position_;
	int stamina_ = 15;
	bool can_deposit_ = false;
	int resources_held_ = 0;

	Tree bt_tree_;
protected:
	void DefineTexture(int type) override;
	Status SeekStone();
	Status GatherStone();
	Status ReturnHomeOrStorage();

public:
	Miner(const float x, const float y, const float linear_speed, Tilemap& tilemap);
	Miner(const Miner& w);

	bool can_deposit() { return can_deposit_; }
	int resources_held() { return resources_held_; }
	void ResetResourcesHeld() { resources_held_ = 0; }

	void InitiateBehaviourTree();
	void Tick();
};
#endif // API_GAMEPLAY_AI_MINER_H_
