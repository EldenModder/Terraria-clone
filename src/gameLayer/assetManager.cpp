#include "assetManager.h"

void AssetManager::LoadAll()
{
	dirt = LoadTexture(RESOURCES_PATH "dirt.png");

	textures = LoadTexture(RESOURCES_PATH "textures.png");

	frame = LoadTexture(RESOURCES_PATH "frame.png");

	wood = LoadTexture(RESOURCES_PATH "treetextures.png");
}