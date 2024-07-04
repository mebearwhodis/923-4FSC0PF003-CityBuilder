#ifndef API_GAMEPLAY_AI_WOODSMAN_H_
#define API_GAMEPLAY_AI_WOODSMAN_H_
#include "walker.h"
#include "behaviour_tree/tree.h"
#include "pathfinding/pathfinder.h"
#include "world_generation/tilemap.h"

class Woodsman : public Walker
{
private:
	Tilemap& tilemap_;

	behaviour_tree::Tree bt_tree_;
protected:
	void DefineTexture() override;
	behaviour_tree::Status SeekWood();
public:
	Woodsman(const float x, const float y, const float linear_speed, Tilemap& tilemap);
	void InitiateBehaviourTree();
	void Tick();

};
#endif // API_GAMEPLAY_AI_WOODSMAN_H_
