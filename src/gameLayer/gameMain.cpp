#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>
#include <assetManager.h>
#include <gameMap.h>
#include <helpers.h>
#include <raymath.h>

struct GameData
{
	GameMap gameMap;
	Camera2D camera;
}gameData;

AssetManager assetManager;

float cameraSpeed = 7.0f;
int blockIndex = 0;
bool initGame()
{
	assetManager.LoadAll();

	gameData.gameMap.create(30, 10);

	gameData.gameMap.getBlockUnsafe(0, 7).type = Block::grassBlock;
	gameData.gameMap.getBlockUnsafe(1, 7).type = Block::grassBlock;
	gameData.gameMap.getBlockUnsafe(2, 7).type = Block::grassBlock;
	gameData.gameMap.getBlockUnsafe(3, 7).type = Block::grassBlock;
	gameData.gameMap.getBlockUnsafe(4, 7).type = Block::grassBlock;

	gameData.camera.target = { 0.0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;
	
	return true;
}

bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	ClearBackground({75, 75, 150, 255});

	BeginMode2D(gameData.camera);
	

#pragma region Camera movement

	if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= cameraSpeed * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += cameraSpeed * deltaTime;
	if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= cameraSpeed * deltaTime;
	if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += cameraSpeed * deltaTime;

#pragma endregion

	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldPos.x);
	int blockY = (int)floor(worldPos.y);
	
	blockIndex = Clamp(blockIndex, 0, Block::BLOCKS_COUNT);
	if (blockIndex == Block::BLOCKS_COUNT) blockIndex = 0;
	float wheel = GetMouseWheelMove();
	if (wheel < 0)
	{
		blockIndex++;
	}
	else if (wheel > 0)
	{
		blockIndex--;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b) *b = {};
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
		if (b) b->type = blockIndex;
		
	}
#pragma region ViewLimit

	Vector2 topLeftView = GetScreenToWorld2D({ 0, 0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.x - 1);
	int endYView = (int)ceilf(bottomRightView.x + 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);
	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);

#pragma endregion

	for (int y = 0; y < endYView; y++)
	{
		for (int x = 0; x < endXView; x++)
		{
			auto& b = gameData.gameMap.getBlockUnsafe(x, y);

			if (b.type != Block::air)
			{
				float size = 1;
				float posX = x * size;
				float posY = y * size;

				DrawTexturePro(
					assetManager.textures,
					getTextureAtlas(b.type, 0, 32, 32),
					{ posX, posY, size, size },
					{0, 0},
					0,
					WHITE
				);
			}
		}
	}
	//draw selected block
	DrawTexturePro(
		assetManager.frame,
		{ 0,0,(float)assetManager.frame.width, (float)assetManager.frame.height },
		{ (float)blockX, (float)blockY, 1, 1 },
		{ 0,0 },
		0.0f,
		WHITE
	);

	EndMode2D();
	DrawText(TextFormat("current block index: %i", blockIndex), 2, 2, 20, RED);
	if (blockIndex == 0)
	{
		DrawText("Air", 2, 20, 20, RED);
	}
	else
	{
		DrawTexturePro(
			assetManager.textures,
			getTextureAtlas(blockIndex, 0, 32, 32),
			{ 2, 20, 32, 32 },
			{ 0, 0 },
			0,
			WHITE
		);
	}
	
	return true;
}

void closeGame()
{


	CloseWindow();
}
