#ifndef API_ENUM_H_
#define API_ENUM_H_

enum class CursorType
{
	kBasic,
	kGauntlet,
	kLength
};

enum class UiTexture
{
	kWhiteButtonRedFrame,
	kLength
};

enum class TileType
{
	kPlain, //2
	kForest, //4
	kPineForest, //4
	kForestCutDown, //4
	kHouse,
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