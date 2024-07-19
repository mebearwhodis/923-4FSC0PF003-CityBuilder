#include "behaviour_tree/leaf.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/sequence.h"
#include "gameplay/ai/woodsman.h"
#include "utils.h"

Woodsman::Woodsman(const float x, const float y, const float linear_speed, Tilemap& tilemap) : Walker(x, y, linear_speed), tilemap_(tilemap)
{
	DefineTexture(static_cast<int>(VillagerType::kWoodsman));
	frame_.setPosition(sprite_.getGlobalBounds().getPosition());
	frame_.setSize(sprite_.getGlobalBounds().getSize());
	home_position_ = getPosition();
	InitiateBehaviourTree();
}

Woodsman::Woodsman(const Woodsman& w) : Walker(w), tilemap_(w.tilemap_)
{
	stamina_ = w.stamina_;
	home_position_ = w.home_position_;
	InitiateBehaviourTree();
}

void Woodsman::InitiateBehaviourTree()
{
	Leaf* check_stamina = new Leaf([&]()
		{
			if (stamina_ >= 0)
			{
				return Status::kSuccess;
			}
			else { return Status::kFailure; }
		});
	Leaf* seek_wood = new Leaf([&]()
		{
			can_deposit_ = false;
			return SeekWood();
		});

	Leaf* gather_wood = new Leaf([&]()
		{
			return GatherWood();
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


	std::unique_ptr<Selector> main_selector = std::make_unique<Selector>();

	Sequence* gathering_sequence = new Sequence();
	Sequence* home_sequence = new Sequence();

	main_selector->AddNode(gathering_sequence);
	main_selector->AddNode(home_sequence);

	gathering_sequence->AddNode(check_stamina);
	gathering_sequence->AddNode(seek_wood);
	gathering_sequence->AddNode(gather_wood);

	home_sequence->AddNode(return_home);
	home_sequence->AddNode(refill_stamina);

	bt_tree_.Attach(main_selector);

	check_stamina = nullptr;
	seek_wood = nullptr;
	gather_wood = nullptr;
	return_home = nullptr;
	refill_stamina = nullptr;
}

void Woodsman::Tick()
{
	Walker::Tick();
	bt_tree_.Tick();
}

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
	const sf::Vector2f closest_tree = tilemap_.GetClosest(getPosition(), TileType::kForest);

	return GoToNearest(tilemap_, closest_tree, stamina_, true);
}

Status Woodsman::GatherWood()
{
	if (tilemap_.Gather(getPosition(), TileType::kForest))
	{

		resources_held_ += (std::rand() % 5) + 1;
		return Status::kSuccess;
	}
	else
	{
		return Status::kFailure;
	}
}

Status Woodsman::ReturnHomeOrStorage()
{
	const sf::Vector2f closest_storage = tilemap_.GetClosest(getPosition(), TileType::kStorage);
	const float magnitude_to_storage = squaredMagnitude(closest_storage - getPosition());
	const float magnitude_to_home = squaredMagnitude(home_position_ - getPosition());

	return (magnitude_to_home < magnitude_to_storage) ?
		GoToNearest(tilemap_, home_position_, stamina_, false) : GoToNearest(tilemap_, closest_storage, stamina_, false);
}
