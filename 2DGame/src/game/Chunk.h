#pragma once

#include "Global.h"
#include "main/WindowManager.h"
#include "render/RenderManager.h"
#include "textures/TextureAtlas.h"
#include "PerlinNoise.hpp"

class Chunk {
private:
	WindowManager* win_mgr;
	RenderManager* renderer;
	TextureAtlas* tileAtlas;

	const static int size = 16;
	const float ROffset = (size * 1.5f) - 0.5f;
	int tileMap[size][size];

	glm::vec2 offset = {0, 0};

	const siv::PerlinNoise::seed_type seed1 = 232333u;
	const siv::PerlinNoise perlin1{ seed1 };
	const siv::PerlinNoise::seed_type seed2 = 342344u;
	const siv::PerlinNoise perlin2{ seed2 };

	void renderTile(int id, int x, int y);
public:
	Chunk(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas);
	~Chunk();

	glm::vec2 min;
	glm::vec2 max;

	void render();

	void loadTiles();
	bool inChunk(const glm::vec2& worldPos);
	int getSize();

	void moveOffset(const glm::vec2& delta);
	void setOffset(const glm::vec2& newOffset);
	glm::vec2& getOffset();
};