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

//TODO TileTexture rather than Resource, to divide things

//enum class TileType
//{
//	kTerrainForest,
//	kTerrainForestCutDown,
//	kHouse,
//	kLength,
//};

//TODO make TileType and TileTexture the same
enum class TileType
{
	kPlain,
	kForest,
	kForestCutDown,
	kHouse
	//...
};
#endif // ENUM_H
