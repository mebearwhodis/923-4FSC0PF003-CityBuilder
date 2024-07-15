#ifndef API_ENUM_H_
#define API_ENUM_H_

enum class CursorType
{
	kArrow,
	kBuild,
	kPan,
	kLength
};

enum class UiTexture
{
	kMenuUp,
	kMenuDown,
	kHouseUp,
	kHouseDown,
	kForgeUp,
	kForgeDown,
	kSawmillUp,
	kSawmillDown,
	kStorageUp,
	kStorageDown,
	kGameplayResourcesUp,
	kGameplayResourcesDown,
	kLength
};

enum class TileType
{
	kPlain, //2
	kForest, //4
	kPineForest, //4
	kForestCutDown, //4
	kStone,
	kBerryFull,
	kBerryEmpty,
	kHouse,
	kForge,
	kSawmill,
	kStorage,
	kCastleBase,
	kCastleRoof,
	//...
	kLength
};

enum class VillagerType
{
	kVillager,
	kWoodsman,
	kMiner,
	kGatherer,
	//..
	kLength
};
#endif // API_ENUM_H_