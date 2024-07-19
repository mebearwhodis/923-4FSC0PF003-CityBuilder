#ifndef API_GAMEPLAY_AI_GATHERER_H_
#define API_GAMEPLAY_AI_GATHERER_H_

#include "behaviour_tree/tree.h"
#include "walker.h"
#include "world_generation/tilemap.h"

class Gatherer : public Walker
{
private:
	Tilemap& tilemap_;
	sf::Vector2f home_position_;
	int stamina_ = 15;
	int resources_held_ = 0;
	bool can_deposit_ = false;
	Tree bt_tree_;

protected:
	void DefineTexture(int type) override;
	Status SeekBerry();
	Status GatherBerry();
	Status ReturnHomeOrStorage();

public:
	Gatherer(const float x, const float y, const float linear_speed, Tilemap& tilemap);
	Gatherer(const Gatherer& w);

	void ResetResourcesHeld() { resources_held_ = 0; }
	void InitiateBehaviourTree();
	void Tick();

	// Getters 
	bool can_deposit() const { return can_deposit_; }
	int resources_held() const { return resources_held_; }
};
#endif