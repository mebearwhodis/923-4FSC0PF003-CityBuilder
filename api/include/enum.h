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

//enum class TileType
//{
//	kPlain, //2
//	kForest, //4
//	kPineForest, //4
//	kForestCutDown, //4
//	kHouse,
//	//...
//	kLength
//};

enum class TileType
{
	grass_centre,
	grass_U,
	grass_UR,
	grass_R,
	grass_DR,
	grass_D,
	grass_DL,
	grass_L,
	grass_UL,

	grass_groundUR,
	grass_groundDR,
	grass_groundDL,
	grass_groundUL,

	grass_waterUR,
	grass_waterDR,
	grass_waterDL,
	grass_waterUL,

	ground_centre,
	ground_U,
	ground_UR,
	ground_R,
	ground_DR,
	ground_D,
	ground_DL,
	ground_L,
	ground_UL,

	ground_grassU,
	ground_grassUR,
	ground_grassR,
	ground_grassDR,
	ground_grassD,
	ground_grassDL,
	ground_grassL,
	ground_grassUL,

	ground_waterUR,
	ground_waterDR,
	ground_waterDL,
	ground_waterUL,

	water01,

	kLength
};



enum class VillagerType
{
	kVillager,
	//..
	kLength
};
#endif // API_ENUM_H_