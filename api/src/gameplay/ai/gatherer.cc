#include "behaviour_tree/leaf.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/sequence.h"
#include "gameplay/ai/gatherer.h"
#include "utils.h"

Gatherer::Gatherer(const float x, const float y, const float linear_speed, Tilemap& tilemap) : tilemap_(tilemap), Walker(x, y, linear_speed)
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
	home_position_ = w.home_position_;
	InitiateBehaviourTree();
}

void Gatherer::InitiateBehaviourTree()
{
	Leaf* check_stamina = new Leaf([&]()
		{
			if (stamina_ >= 0) { return Status::kSuccess; }
			else { return Status::kFailure; }
		});
	Leaf* seek_berry = new Leaf([&]()
		{
			can_deposit_ = false;
			return SeekBerry();
		});

	Leaf* gather_berry = new Leaf([&]()
		{
			return GatherBerry();
		});

	Leaf* return_home = new Leaf([&]()
		{
			return ReturnHomeOrStorage();
		});

	Leaf* refill_stamina = new Leaf([&]()
		{
			can_deposit_ = true;
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

	check_stamina = nullptr;
	seek_berry = nullptr;
	gather_berry = nullptr;
	return_home = nullptr;
	refill_stamina = nullptr;
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
	const sf::Vector2f closest_berry = tilemap_.GetClosest(getPosition(), TileType::kBerryFull);

	return GoToNearest(tilemap_, closest_berry, stamina_, true);
}

Status Gatherer::GatherBerry()
{
	if (tilemap_.Gather(getPosition(), TileType::kBerryFull))
	{

		resources_held_ += (std::rand() % 5) + 1;
		return Status::kSuccess;
	}
	else
	{
		return Status::kFailure;
	}
}

Status Gatherer::ReturnHomeOrStorage()
{
	const sf::Vector2f closest_storage = tilemap_.GetClosest(getPosition(), TileType::kStorage);
	const float magnitude_to_storage = squaredMagnitude(closest_storage - getPosition());
	const float magnitude_to_home = squaredMagnitude(home_position_ - getPosition());

	return (magnitude_to_home < magnitude_to_storage) ? 
		GoToNearest(tilemap_, home_position_, stamina_, false) : GoToNearest(tilemap_, closest_storage, stamina_, false);
}
