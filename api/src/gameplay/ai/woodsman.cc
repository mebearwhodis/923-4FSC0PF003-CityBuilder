#include "gameplay/ai/woodsman.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

#include "behaviour_tree/leaf.h"


Woodsman::Woodsman(float x, float y, float linear_speed, Tilemap& tilemap): tilemap_(tilemap), Walker(x, y, linear_speed)
{
	DefineTexture(static_cast<int>(VillagerType::kVillager));
	frame_.setPosition(sprite_.getGlobalBounds().getPosition());
	frame_.setSize(sprite_.getGlobalBounds().getSize());

	InitiateBehaviourTree();

}

void Woodsman::InitiateBehaviourTree()
{
	behaviour_tree::Leaf* seek_wood = new behaviour_tree::Leaf([this]()
	{
			return SeekWood();
	});
		bt_tree_.AttachNode(seek_wood);
}

void Woodsman::Tick()
{
	Walker::Tick();
	bt_tree_.Tick();
}

//sprite_.setPosition(x, y);
void Woodsman::DefineTexture(int type)
{
	const auto& textures = ResourceManager::Get().GetCharacterTextures(static_cast<VillagerType>(type));
	if (textures.Size() > 0) {
		const sf::Texture& texture = textures[std::rand() % textures.Size()];
		sprite_.setTexture(texture);
	}
}

behaviour_tree::Status Woodsman::SeekWood()
{
	//TODO Use CLOSESTTREE as destination, I guess + checks pour pas SeekWood tout le temps
	//TODO Failure if no close tree, running while moving, success when arrived
	//Path p = Pathfinder::CalculatePath(tilemap_.GetWalkableTiles(), GetLastDestination(), destination, 64);
	//set_path(p);
	//std::cout << "Execute seek wood behaviour" << std::endl;
	return behaviour_tree::Status::kSuccess;
}