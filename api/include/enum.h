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
	kLength
};

enum class TileType
{
	kPlain, //2
	kForest, //4
	kPineForest, //4
	kForestCutDown, //4
	kHouse,
	kForge,
	kSawmill,
	//...
	kLength
};

enum class VillagerType
{
	kVillager,
	//..
	kLength
};
#endif // API_ENUM_H_