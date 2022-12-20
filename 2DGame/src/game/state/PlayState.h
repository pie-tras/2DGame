#pragma once

#include "Global.h"
#include "game/Chunk.h"
#include "game/state/GameState.h"
#include "game/MapGen.h"
#include "main/WindowManager.h"
#include "render/RenderManager.h"
#include "util/Loader.h"
#include "main/Assets.h"
#include "textures/Texture.h"
#include "textures/TextureAtlas.h"
#include "textures/Animation.h"
#include "textures/AnimationManager.h"

#include <vector>

class PlayState : public GameState{
private:
	TextureAtlas* tileAtlas;

	const static int tileSize = 32;
	const static int chunkSize = 16;
	const static int mapSize = 100;
	const static int chunkDepth = 4;

	const float mapMax = ((mapSize - 1) * chunkSize * tileSize) - ((3 * tileSize) / 4);
	const float mapMin = (6 * (chunkSize * tileSize) / 4) - tileSize / 4;
	
	glm::vec2 target = glm::vec2(mapMax/2, mapMax/2), velocity = glm::vec2(0, 0);
	float speed = 12.0f;
	float zoom = 0.01f;

	MapGen* mapGen;
public:
	PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
	~PlayState();

	void init() override;
	void tick() override;
	void render() override;
	void stop() override;
};