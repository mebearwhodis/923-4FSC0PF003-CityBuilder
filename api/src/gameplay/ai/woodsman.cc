#include "gameplay/ai/woodsman.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

#include "sfml_utils.h"
#include "behaviour_tree/leaf.h"
#include "behaviour_tree/sequence.h"


Woodsman::Woodsman(float x, float y, float linear_speed, Tilemap& tilemap): tilemap_(tilemap), Walker(x, y, linear_speed)
{
	DefineTexture(static_cast<int>(VillagerType::kVillager));
	frame_.setPosition(sprite_.getGlobalBounds().getPosition());
	frame_.setSize(sprite_.getGlobalBounds().getSize());
	home_position_ = getPosition();
	InitiateBehaviourTree();

}

void Woodsman::InitiateBehaviourTree()
{
	Leaf* seek_wood = new Leaf([this]()
		{
			return SeekWood();
		});

	Leaf* gather_wood = new Leaf([this]()
		{
			return GatherWood();
		});

	Leaf* return_home = new Leaf([this]()
		{
			return ReturnHome();
		});

	// Creating the sequence
	Sequence* woodsman_sequence = new Sequence();

	// Adding the nodes to the sequence using std::move and static_cast
	woodsman_sequence->AddNode(seek_wood);
	woodsman_sequence->AddNode(gather_wood);
	woodsman_sequence->AddNode(return_home);

	bt_tree_.AttachNode(woodsman_sequence);
	std::cout << "Behavior tree initialized for Woodsman" << std::endl;
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

Status Woodsman::SeekWood()
{
	sf::Vector2f closestTree = tilemap_.GetClosestTree(getPosition());
	sf::Vector2f pathDestination = path_.final_destination();

	if(squaredMagnitude(closestTree - pathDestination) > std::numeric_limits<float>::epsilon())
	{
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkableTiles(), GetLastDestination(), closestTree, 64);
		if (p.is_available())
		{
			set_path(p);
		}
		else
		{
			std::cout << "Path unavailable" << std::endl;
			return Status::kFailure;
		}
	}

	if (squaredMagnitude(getPosition() - pathDestination) > std::numeric_limits<float>::epsilon())
	{
		std::cout << "On its way to wood" << std::endl;
		return Status::kRunning;
	}
	else
	{
		std::cout << "Arrived at wood" << std::endl;
		return Status::kSuccess;
	}
}

Status Woodsman::GatherWood()
{
	if(tilemap_.GatherTree(getPosition()))
	{
		//TODO (peut-être barre de progression), Running pendant qu'il coupe, succès une fois fini
		std::cout << "Cutting wood" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		std::cout << "Not cutting wood" << std::endl;
		return Status::kFailure;
	}
}

behaviour_tree::Status Woodsman::ReturnHome()
{
	sf::Vector2f pathDestination = path_.final_destination();

	if (squaredMagnitude(home_position_ - pathDestination) > std::numeric_limits<float>::epsilon())
	{
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkableTiles(), GetLastDestination(), home_position_, 64);
		if (p.is_available())
		{
			set_path(p);
		}
		else
		{
			std::cout << "Path unavailable" << std::endl;
			return Status::kFailure;
		}
	}

	//TODO c'est pas un todo, ici j'avais (getPosition() - pathDestination) au lieu de (getPosition() - home_position)
	if (squaredMagnitude(getPosition() - home_position_) > std::numeric_limits<float>::epsilon())
	{
		std::cout << "On its way to home" << std::endl;
		return Status::kRunning;
	}
	else
	{
		std::cout << "Arrived at home" << std::endl;
		return Status::kSuccess;
	}
}
