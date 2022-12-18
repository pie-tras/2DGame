#pragma once

#include "Global.h"
#include "main/WindowManager.h"
#include "game/state/GameState.h"
#include "render/RenderManager.h"

class SplashState : public GameState {
private:

public:
	SplashState(WindowManager* win_mgr, RenderManager* renderer);
	~SplashState();

	void init() override;
	void tick() override;
	void render() override;
	void stop() override;
};