#pragma once

#include "Global.h"
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
	Texture* playerTexture;
	Texture* tileTexture;
	TextureAtlas* tileAtlas;
	TextureAtlas* sheepAtlas;
	Animation* sheepAnim;
	AnimationManager* animManager;

	const static int worldSize = 20;
	int tileMap[worldSize][worldSize];

	std::vector<glm::vec2> placedObjects;

	glm::vec2 target = glm::vec2(0, 0), velocity = glm::vec2(0, 0);
	float speed = 5.0f;
	float zoom = 1.0f;

public:
	PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
	~PlayState();

	void init() override;
	void tick() override;
	void render() override;
	void stop() override;
};