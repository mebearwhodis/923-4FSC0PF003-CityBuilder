#ifndef WFC_H
#define WFC_H
#include <vector>
#include <map>
#include <random>
#include <set>
#include <algorithm>
#include <queue>
#include "enum.h" 


class WFC {
public:
    WFC(unsigned int width, unsigned int height);

    void generate(std::vector<TileType>& output);

private:
    unsigned int width_;
    unsigned int height_;
    std::vector<std::set<TileType>> wave_;

    bool isCollapsed() const;

    int findCellWithLeastEntropy(std::mt19937& gen) const;

    void collapseCell(int idx, std::mt19937& gen);

    void propagate(int startIdx, std::queue<std::pair<int, int>>& propagationQueue, std::mt19937& gen);
};


struct AdjacencyRules
{
	std::vector<TileType> top;
	std::vector<TileType> right;
	std::vector<TileType> bottom;
	std::vector<TileType> left;
};

inline std::map<TileType, AdjacencyRules> adjacencyRules = {
	// Grass tiles
	{TileType::grass_centre, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_UL, {
		{TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::water01},
		{TileType::grass_U, TileType::grass_UR, TileType::grass_waterUL},
		{TileType::grass_L, TileType::grass_DL, TileType::grass_waterUL},
		{TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::water01}}},

	{TileType::grass_U, {
		{TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::water01},
		{TileType::grass_U, TileType::grass_UR, TileType::grass_waterUL},
		{TileType::grass_centre,TileType::grass_D, TileType::grass_groundDR,TileType::grass_groundDL,TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_U, TileType::grass_UL, TileType::grass_waterUR}}},

	{TileType::grass_UR, {
		{TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::water01},
		{TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::water01},
		{TileType::grass_R, TileType::grass_groundDR, TileType::grass_waterUR},
		{TileType::grass_U, TileType::grass_UL, TileType::grass_waterUR}}},

	{TileType::grass_L, {
		{TileType::grass_UL, TileType::grass_L, TileType::grass_waterDL},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundDR, TileType::grass_groundUR, TileType::grass_waterDR, TileType::grass_waterUR, TileType::ground_grassL},
		{TileType::grass_L, TileType::grass_groundDL, TileType::grass_waterUL},
		{TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::water01}}},

	{TileType::grass_R, {
		{TileType::grass_UR, TileType::grass_R, TileType::grass_waterDR},
		{TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::water01},
		{TileType::grass_R, TileType::grass_groundDR, TileType::grass_waterUR},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_DL, {
		{TileType::grass_L, TileType::grass_UL, TileType::grass_waterDL},
		{TileType::grass_D, TileType::grass_DR, TileType::grass_waterDL},
		{TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::water01},
		{TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::water01}}},

	{TileType::grass_D, {
		{TileType::grass_centre,TileType::grass_U, TileType::grass_groundUR,TileType::grass_groundUL,TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_D, TileType::grass_DR, TileType::grass_waterDL},
		{TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::water01},
		{TileType::grass_D, TileType::grass_DL, TileType::grass_waterDR}}},

	{TileType::grass_DR, {
		{TileType::grass_R, TileType::grass_UR, TileType::grass_waterDR},
		{TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::water01},
		{TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::water01},
		{TileType::grass_D, TileType::grass_DL, TileType::grass_waterDR}}},

	{TileType::grass_groundUR, {
		{TileType::grass_groundDR, TileType::ground_grassL},
		{TileType::grass_groundUL, TileType::ground_grassD},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_groundDR, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_groundDL, TileType::ground_grassU},
		{TileType::grass_groundUR, TileType::ground_grassL},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_groundDL, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::grass_groundUL, TileType::ground_grassR},
		{TileType::grass_groundDR, TileType::ground_grassU}}},

	{TileType::grass_groundUL, {
		{TileType::grass_groundDL, TileType::ground_grassR},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_groundUR, TileType::ground_grassD}}},

	{TileType::grass_waterUR, {
		{TileType::grass_waterDR, TileType::grass_R},
		{TileType::grass_waterUL, TileType::grass_U},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_waterDR, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_waterDL, TileType::grass_D},
		{TileType::grass_waterUR, TileType::grass_R},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{TileType::grass_waterDL, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::grass_waterUL, TileType::grass_L},
		{TileType::grass_waterDR, TileType::grass_D}}},

	{TileType::grass_waterUL, {
		{TileType::grass_waterDL, TileType::grass_L},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::grass_waterUR, TileType::grass_U}}},

	{ TileType::ground_centre, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_UL, {
		{TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::water01},
		{TileType::ground_U, TileType::ground_UR, TileType::ground_waterUL},
		{TileType::ground_L, TileType::ground_DL, TileType::ground_waterUL},
		{TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::water01}} },

	{ TileType::ground_U, {
		{TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::water01},
		{TileType::ground_U, TileType::ground_UR, TileType::ground_waterUL},
		{TileType::ground_centre,TileType::ground_D, TileType::ground_grassDR,TileType::ground_grassDL,TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_U, TileType::ground_UL, TileType::ground_waterUR}} },

	{ TileType::ground_UR, {
		{TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::water01},
		{TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::water01},
		{TileType::ground_R, TileType::ground_grassDR, TileType::ground_waterUR},
		{TileType::ground_U, TileType::ground_UL, TileType::ground_waterUR}} },

	{ TileType::ground_L, {
		{TileType::ground_UL, TileType::ground_L, TileType::ground_waterDL},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassDR, TileType::ground_grassUR, TileType::ground_waterDR, TileType::ground_waterUR, TileType::ground_grassR},
		{TileType::ground_L, TileType::ground_grassDL, TileType::ground_waterUL},
		{TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::water01}} },

	{ TileType::ground_R, {
		{TileType::ground_UR, TileType::ground_R, TileType::ground_waterDR},
		{TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::water01},
		{TileType::ground_R, TileType::ground_grassDR, TileType::ground_waterUR},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_DL, {
		{TileType::ground_L, TileType::ground_UL, TileType::ground_waterDL},
		{TileType::ground_D, TileType::ground_DR, TileType::ground_waterDL},
		{TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::water01},
		{TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::water01}} },

	{ TileType::ground_D, {
		{TileType::ground_centre,TileType::ground_U, TileType::ground_grassUR,TileType::ground_grassUL,TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_D, TileType::ground_DR, TileType::ground_waterDL},
		{TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::water01},
		{TileType::ground_D, TileType::ground_DL, TileType::ground_waterDR}} },

	{ TileType::ground_DR, {
		{TileType::ground_R, TileType::ground_UR, TileType::ground_waterDR},
		{TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::water01},
		{TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::water01},
		{TileType::ground_D, TileType::ground_DL, TileType::ground_waterDR}} },

	{TileType::ground_grassU, {
		{TileType::grass_centre, TileType::grass_U, TileType::grass_groundUR, TileType::grass_groundUL, TileType::grass_waterUR, TileType::grass_waterUL, TileType::ground_grassD},
		{TileType::ground_grassUL, TileType::ground_grassU},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_grassUR, TileType::ground_grassU}}},

	{TileType::ground_grassR, {
		{TileType::ground_grassDR, TileType::ground_grassR},
		{TileType::grass_centre, TileType::grass_R, TileType::grass_groundUR, TileType::grass_groundDR, TileType::grass_waterUR, TileType::grass_waterDR, TileType::ground_grassL},
		{TileType::ground_grassUR, TileType::ground_grassR},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}}},

	{TileType::ground_grassD, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_grassDL, TileType::ground_grassD},
		{TileType::grass_centre, TileType::grass_D, TileType::grass_groundDR, TileType::grass_groundDL, TileType::grass_waterDR, TileType::grass_waterDL, TileType::ground_grassU},
		{TileType::ground_grassDR, TileType::ground_grassD}}},

	{TileType::ground_grassL, {
		{TileType::ground_grassDL, TileType::ground_grassL},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_grassUL, TileType::ground_grassL},
		{TileType::grass_centre, TileType::grass_L, TileType::grass_groundDL, TileType::grass_groundUL, TileType::grass_waterDL, TileType::grass_waterUL, TileType::ground_grassR}}},

	{ TileType::ground_grassUR, {
		{TileType::ground_grassDR, TileType::ground_grassR},
		{TileType::ground_grassUL, TileType::ground_grassU},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_grassDR, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_grassDL, TileType::ground_grassD},
		{TileType::ground_grassUR, TileType::ground_grassR},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_grassDL, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_grassUL, TileType::ground_grassL},
		{TileType::ground_grassDR, TileType::ground_grassD}} },

	{ TileType::ground_grassUL, {
		{TileType::ground_grassDL, TileType::ground_grassL},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_grassUR, TileType::ground_grassU}} },

	{ TileType::ground_waterUR, {
		{TileType::ground_waterDR, TileType::ground_R},
		{TileType::ground_waterUL, TileType::ground_U},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_waterDR, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_waterDL, TileType::ground_D},
		{TileType::ground_waterUR, TileType::ground_R},
		{TileType::ground_centre, TileType::ground_L, TileType::ground_grassDL, TileType::ground_grassUL, TileType::ground_waterDL, TileType::ground_waterUL, TileType::ground_grassL}} },

	{ TileType::ground_waterDL, {
		{TileType::ground_centre, TileType::ground_U, TileType::ground_grassUR, TileType::ground_grassUL, TileType::ground_waterUR, TileType::ground_waterUL, TileType::ground_grassU},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_waterUL, TileType::ground_L},
		{TileType::ground_waterDR, TileType::ground_D}} },

	{ TileType::ground_waterUL, {
		{TileType::ground_waterDL, TileType::ground_L},
		{TileType::ground_centre, TileType::ground_R, TileType::ground_grassUR, TileType::ground_grassDR, TileType::ground_waterUR, TileType::ground_waterDR, TileType::ground_grassR},
		{TileType::ground_centre, TileType::ground_D, TileType::ground_grassDR, TileType::ground_grassDL, TileType::ground_waterDR, TileType::ground_waterDL, TileType::ground_grassD},
		{TileType::ground_waterUR, TileType::ground_U}} },

	{TileType::water01, {
		{TileType::grass_DR, TileType::grass_D, TileType::grass_DL, TileType::ground_DR, TileType::ground_D, TileType::ground_DL, TileType::water01},
		{TileType::grass_DL, TileType::grass_L, TileType::grass_UL, TileType::ground_DL, TileType::ground_L, TileType::ground_UL, TileType::water01},
		{TileType::grass_UR, TileType::grass_U, TileType::grass_UL, TileType::ground_UR, TileType::ground_U, TileType::ground_UL, TileType::water01},
		{TileType::grass_DR, TileType::grass_R, TileType::grass_UR, TileType::ground_DR, TileType::ground_R, TileType::ground_UR, TileType::water01}}}
};
#endif // WFC_H
