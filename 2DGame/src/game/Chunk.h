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

	int depth;
	int size;
	int tileSize;

	const float ROffset = (size * 1.5f) - 0.5f;

	glm::vec2 offset = {0, 0};

	void renderTile(int id, int x, int y);
public:
	Chunk(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas, int depth, int size, int tileSize);
	~Chunk();
	
	int*** data;

	void render();

	void moveOffset(const glm::vec2& delta);
	void setOffset(const glm::vec2& newOffset);
	glm::vec2& getOffset();
};