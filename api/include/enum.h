#ifndef ENUM_H
#define ENUM_H

enum class CursorType
{
	kBasic,
	kGauntlet,
	kLength
};

enum class Resource
{
	kWhiteButtonRedFrame,
	kTerrainForest,
	kTerrainForestCutDown,
	kHouse,
	//...
	kLength // or kMax Last value, used to get size of the enum
};
//
//enum class TileType
//{
//	kTerrainForest,
//	kTerrainForestCutDown,
//	kHouse,
//	kLength,
//};

enum class TileType
{
	kPlain,
	kForest,
	kOre,
	kHouse
	//...
};
#endif // ENUM_H
