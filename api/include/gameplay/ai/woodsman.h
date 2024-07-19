#ifndef API_GAMEPLAY_AI_WOODSMAN_H_
#define API_GAMEPLAY_AI_WOODSMAN_H_

#include "behaviour_tree/tree.h"
#include "walker.h"
#include "world_generation/tilemap.h"

class Woodsman : public Walker
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
	Status SeekWood();
	Status GatherWood();
	Status ReturnHomeOrStorage();

public:
	Woodsman(const float x, const float y, const float linear_speed, Tilemap& tilemap);
	Woodsman(const Woodsman& w);

	void ResetResourcesHeld() { resources_held_ = 0; }
	void InitiateBehaviourTree();
	void Tick();

	// Getters 
	bool can_deposit() const { return can_deposit_; }
	int resources_held() const { return resources_held_; }
};
#endif // API_GAMEPLAY_AI_WOODSMAN_H_
