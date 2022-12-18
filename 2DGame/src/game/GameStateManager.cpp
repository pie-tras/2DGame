#include "GameStateManager.h"
#include "States.h"

GameStateManager::GameStateManager(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) :
	win_mgr(win_mgr), renderer(renderer), loader(loader) {

	splashState = new SplashState(win_mgr, renderer, loader);
	menuState = new MenuState(win_mgr, renderer, loader);
	playState = new PlayState(win_mgr, renderer, loader);
}

GameStateManager::~GameStateManager() {
	delete splashState;
	delete menuState;
	delete playState;
}

void GameStateManager::update() {
	activeState->tick();
	activeState->render();
	win_mgr->updateWindow();
	if ( activeState->nextState != States::NONE ) {
		setActiveState(activeState->nextState);
	}
}

void GameStateManager::setActiveState(States state) {
	if (activeState != nullptr) {
		activeState->stop();
	}

	switch (state) {
		case States::SPLASH:
			activeState = splashState;
			break;
		case States::MENU:
			activeState = menuState;
			break;
		case States::PLAY:
			activeState = playState;
			break;
		default:
			break;
	}

	activeState->init();
}