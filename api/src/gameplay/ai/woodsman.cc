#include "gameplay/ai/woodsman.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

#include "sfml_utils.h"
#include "behaviour_tree/leaf.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/sequence.h"


Woodsman::Woodsman(float x, float y, float linear_speed, Tilemap& tilemap) : tilemap_(tilemap), Walker(x, y, linear_speed)
{
	DefineTexture(static_cast<int>(VillagerType::kVillager));
	frame_.setPosition(sprite_.getGlobalBounds().getPosition());
	frame_.setSize(sprite_.getGlobalBounds().getSize());
	home_position_ = getPosition();
	InitiateBehaviourTree();

}

void Woodsman::InitiateBehaviourTree()
{
	Leaf* check_stamina = new Leaf([this]()
		{
			if (stamina_ >= 0) { return Status::kSuccess; }
			else { return Status::kFailure; }
		});
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

	Leaf* refill_stamina = new Leaf([this]()
		{
			stamina_ = 15;
			return Status::kFailure;
		});


	// Creating the selector
	std::unique_ptr<Selector> main_selector = std::make_unique<Selector>();

	// Creating the sequences
	Sequence* gathering_sequence = new Sequence();
	Sequence* home_sequence = new Sequence();

	// Adding the nodes to the sequence using std::move and static_cast
	main_selector->AddNode(gathering_sequence);
	main_selector->AddNode(home_sequence);

	gathering_sequence->AddNode(check_stamina);
	gathering_sequence->AddNode(seek_wood);
	gathering_sequence->AddNode(gather_wood);

	home_sequence->AddNode(return_home);
	home_sequence->AddNode(refill_stamina);

	bt_tree_.Attach(main_selector);
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

//TODO factorize SeekWood & ReturnHome
Status Woodsman::SeekWood()
{
	sf::Vector2f closestTree = tilemap_.GetClosestTree(getPosition());


	if (squaredMagnitude(closestTree - path_.final_destination()) > std::numeric_limits<float>::epsilon())
	{
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkableTiles(), GetLastDestination(), closestTree, 64);
		if (p.is_available())
		{
			set_path(p);
			stamina_ -= p.GetSteps().size();
		}
		else
		{
			std::cout << "Path unavailable" << std::endl;
			return Status::kFailure;
		}
	}

	if (squaredMagnitude(getPosition() - path_.final_destination()) > std::numeric_limits<float>::epsilon())
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
	if (tilemap_.GatherTree(getPosition()))
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

	if (squaredMagnitude(home_position_ - path_.final_destination()) > std::numeric_limits<float>::epsilon())
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

	if (squaredMagnitude(getPosition() - path_.final_destination()) > std::numeric_limits<float>::epsilon())
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
