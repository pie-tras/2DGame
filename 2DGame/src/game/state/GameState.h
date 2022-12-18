#pragma once

#include "Global.h"
#include "main/WindowManager.h"
#include "render/RenderManager.h"
#include "util/Loader.h"
#include "game/States.h"

class GameState {
protected:
	WindowManager* win_mgr;
	RenderManager* renderer;
	Loader* loader;
public:
	GameState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
	~GameState();

	States nextState = States::NONE;

	virtual void init() = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void stop();
};