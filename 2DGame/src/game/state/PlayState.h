#pragma once

#include "Global.h"
#include "game/Chunk.h"
#include "game/state/GameState.h"
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
	
	glm::vec2 target = glm::vec2(0, 0), velocity = glm::vec2(0, 0);
	float speed = 12.0f;
	float zoom = 0.1f;

	Chunk* chunk[9];
	int activeChunk = 4;

	void setActiveChunk(const glm::vec2& playerPos);
	void loadAroundActive(const glm::vec2& playerPos);

public:
	PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
	~PlayState();

	void init() override;
	void tick() override;
	void render() override;
	void stop() override;
};