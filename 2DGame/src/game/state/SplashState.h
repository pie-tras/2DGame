#pragma once

#include "Global.h"
#include "game/state/GameState.h"
#include "main/WindowManager.h"
#include "render/RenderManager.h"
#include "util/Loader.h"
#include "main/Assets.h"
#include "game/States.h"
#include "render/RenderModes.h"

class SplashState : public GameState {
private:
	double load_percent = 0;

	glm::vec2 bar_pos = glm::vec2(0);
	float load_width = 0;

	int render_step = 16;
	int step = 0;

	bool isFinished = false;

	void calculateLoadingBar();

public:
	SplashState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
	~SplashState();

	void init() override;
	void tick() override;
	void render() override;
	void stop() override;
};