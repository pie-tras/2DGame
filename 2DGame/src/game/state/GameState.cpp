#include "GameState.h"

GameState::GameState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) :
	win_mgr(win_mgr), renderer(renderer), loader(loader) {

}

GameState::~GameState() {
}

inline void init() {}
inline void tick() {}
inline void render() {}
 
void GameState::stop() {
	nextState = States::NONE;
}