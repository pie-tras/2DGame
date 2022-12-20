#include "PlayState.h"

PlayState::PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) : GameState(win_mgr, renderer, loader) {

}

PlayState::~PlayState() {
	delete mapGen;
	delete tileAtlas;
}

void PlayState::init() {
	std::cout << "Init playstate" << std::endl;
	std::cout << Assets::isLoaded << std::endl;
	tileAtlas = new TextureAtlas(Assets::findTexture("tilemap"), 8, 8);

	mapGen = new MapGen(win_mgr, renderer, tileAtlas, chunkSize, mapSize, chunkDepth, tileSize, 12356);
	mapGen->generate();

	win_mgr->camera->setPosition(target);
}

void PlayState::tick() {
	velocity = glm::vec2(0, 0);

	if (win_mgr->isKeyDown(GLFW_KEY_A)) {
		velocity.x = -speed;
	}
	if (win_mgr->isKeyDown(GLFW_KEY_W)) {
		velocity.y = speed;
	}
	if (win_mgr->isKeyDown(GLFW_KEY_S)) {
		velocity.y = -speed;
	}
	if (win_mgr->isKeyDown(GLFW_KEY_D)) {
		velocity.x = speed;
	}

	if (win_mgr->isKeyDown(GLFW_KEY_MINUS)) {
		zoom += 0.05f;
	}

	if (win_mgr->isKeyDown(GLFW_KEY_EQUAL)) {
		zoom -= 0.05f;
	}

	if (zoom > 2.0f) zoom = 2.0f;
	if (zoom < -2.0f) zoom = -2.0f;

	target += velocity;

	if (target.x > mapMax) {
		velocity.x = 0;
		target.x = mapMax;
	}

	if (target.y > mapMax) {
		velocity.y = 0;
		target.y = mapMax;
	}

	if (target.y < mapMin) {
		velocity.y = 0;
		target.y = mapMin;
	}

	if (target.x < mapMin) {
		velocity.x = 0;
		target.x = mapMin;
	}

	win_mgr->camera->setZoom(zoom);
	win_mgr->camera->move(target, 0.09f);
}

void PlayState::render() {
	mapGen->renderChunks(target);
	renderer->render(0, target, 0.0f, glm::vec2(8, 8), glm::vec4(1,0,1,1));
}

void PlayState::stop() {
	GameState::stop();
}