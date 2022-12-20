#include "SplashState.h"

SplashState::SplashState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) : GameState(win_mgr, renderer, loader) {

}

SplashState::~SplashState() {
}

void SplashState::init() {
	Assets::beginLoadTextures(win_mgr, renderer, loader);

	bar_pos = glm::vec2(-(win_mgr->getWindowWidth() / 2) + 32,
		-(win_mgr->getWindowHeight() / 2) + 32);

	load_percent = 0;

	renderer->setRenderMode(RenderModes::GUI);
}

void SplashState::tick() {
	if (!Assets::isLoaded) {
		for (int i = 0; i < 10; i++) {
			Assets::continueLoadTextures(win_mgr, renderer, loader);

			if (Assets::isLoaded)
				break;
		}
		load_percent = (double)Assets::texturesLoaded / (double)Assets::texturesTotal;
	} else {
		load_percent = 1;

		if (isFinished) {
			nextState = States::PLAY;
		}
	}
}

void SplashState::render() {
	calculateLoadingBar();
	renderer->render(0, bar_pos, 0.0f, glm::vec2(load_width, 10), glm::vec4(1, 1, 1, 1));
}

void SplashState::calculateLoadingBar() {
	glm::vec2 target = glm::vec2((load_percent * (win_mgr->getWindowWidth() - 64)) / 2
		- win_mgr->getWindowWidth() / 2 + 32, -(win_mgr->getWindowHeight() / 2) + 32);

	bar_pos = maths::lerp(bar_pos, target, 0.5f);
	load_width = bar_pos.x - (-(win_mgr->getWindowWidth() / 2) + 32);

	if (Assets::isLoaded && bar_pos.x >= target.x - 0.01f) {
		isFinished = true;
	}
}

void SplashState::stop() {
	GameState::stop();
	renderer->setRenderMode(RenderModes::WORLD);
}