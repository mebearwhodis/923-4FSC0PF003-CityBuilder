#ifndef API_GAMEPLAY_AI_GATHERER_H_
#define API_GAMEPLAY_AI_GATHERER_H_
#include "walker.h"
#include "behaviour_tree/tree.h"
#include "pathfinding/pathfinder.h"
#include "world_generation/tilemap.h"

class Gatherer : public Walker
{
private:
	Tilemap& tilemap_;
	sf::Vector2f home_position_;
	int stamina_ = 15;

	Tree bt_tree_;
protected:
	void DefineTexture(int type) override;
	Status SeekBerry();
	Status GatherBerry();
	Status ReturnHomeOrStorage();

public:
	Gatherer(const float x, const float y, const float linear_speed, Tilemap& tilemap);
	Gatherer(const Gatherer& w);

	void InitiateBehaviourTree();
	void Tick();
};
#endif