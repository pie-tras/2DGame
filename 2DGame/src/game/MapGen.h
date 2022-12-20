#pragma once

#include "Global.h"
#include "main/WindowManager.h"
#include "render/RenderManager.h"
#include "textures/TextureAtlas.h"
#include "game/Chunk.h"
#include "PerlinNoise.hpp"

class MapGen {
private:
	WindowManager* win_mgr;
	RenderManager* renderer;
	TextureAtlas* tileAtlas;

	long seed;
	siv::PerlinNoise heightPerlin;
	siv::PerlinNoise tempPerlin;

	int chunkSize;
	int mapSize;
	int chunkDepth;
	int tileSize;

	Chunk* chunk[9];
	glm::vec2 chunkPos = { 0, 0 };
	int activeChunk = -1;

	int getActiveChunk(const glm::vec2& playerPos);
	void loadAroundActive(const glm::vec2& playerPos);

	int getSurfaceTile(int x, int y);
	int getTile(int x, int y, int elevation);

	void loadChunk(int chunkId, int loadId);
	void writeChunk(int id);

public:
	MapGen(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas, int chunkSize, int mapSize, int chunkDepth, int tileSize, int seed);
	~MapGen();

	void generate();
	void renderChunks(const glm::vec2& playerPos);
};