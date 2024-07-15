#include "gameplay/ai/gatherer.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

#include "utils.h"
#include "behaviour_tree/leaf.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/sequence.h"


Gatherer::Gatherer(float x, float y, float linear_speed, Tilemap& tilemap) : tilemap_(tilemap), Walker(x, y, linear_speed)
{
	DefineTexture(static_cast<int>(VillagerType::kGatherer));
	frame_.setPosition(sprite_.getGlobalBounds().getPosition());
	frame_.setSize(sprite_.getGlobalBounds().getSize());
	home_position_ = getPosition();
	InitiateBehaviourTree();

}

Gatherer::Gatherer(const Gatherer& w) : Walker(w), tilemap_(w.tilemap_)
{
	stamina_ = w.stamina_;
	home_position_ = w.getPosition();
	InitiateBehaviourTree();
}

void Gatherer::InitiateBehaviourTree()
{
	Leaf* check_stamina = new Leaf([this]()
		{
			if (stamina_ >= 0) { return Status::kSuccess; }
			else { return Status::kFailure; }
		});
	Leaf* seek_berry = new Leaf([this]()
		{
			return SeekBerry();
		});

	Leaf* gather_berry = new Leaf([this]()
		{
			return GatherBerry();
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
	gathering_sequence->AddNode(seek_berry);
	gathering_sequence->AddNode(gather_berry);

	home_sequence->AddNode(return_home);
	home_sequence->AddNode(refill_stamina);

	bt_tree_.Attach(main_selector);
}

void Gatherer::Tick()
{
	Walker::Tick();
	bt_tree_.Tick();
}

void Gatherer::DefineTexture(int type)
{
	const auto& textures = ResourceManager::Get().GetCharacterTextures(static_cast<VillagerType>(type));
	if (textures.Size() > 0) {
		const sf::Texture& texture = textures[std::rand() % textures.Size()];
		sprite_.setTexture(texture);
	}
}

Status Gatherer::SeekBerry()
{
	sf::Vector2f closestBerry = tilemap_.GetClosest(getPosition(), TileType::kBerryFull);

	return GoToNearest(tilemap_, closestBerry, stamina_, true);
}

Status Gatherer::GatherBerry()
{
	if (tilemap_.Gather(getPosition(), TileType::kBerryFull))
	{
		//TODO (peut-être barre de progression), Running pendant qu'il coupe, succès une fois fini
		//std::cout << "Cutting wood" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not cutting wood" << std::endl;
		return Status::kFailure;
	}
}

Status Gatherer::ReturnHome()
{
	//TODO: compare magnitudes of here to home_pos and here to closest storage, go the nearest
	return GoToNearest(tilemap_, home_position_, stamina_, false);
}
