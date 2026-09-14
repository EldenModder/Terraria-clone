#pragma once

#include <vector>
#include <blocks.h>

struct GameMap
{
	int w = 0;
	int h = 0;

	std::vector<Block> mapData;


	void create(int w, int h);

	Block& getBlockUnsafe(int x, int y);
	//check if we didn't go outside the map boundaries and return a nullptr if so
	Block* getBlockSafe(int x, int y);
};