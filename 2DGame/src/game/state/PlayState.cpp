#include "PlayState.h"

PlayState::PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) : GameState(win_mgr, renderer, loader) {

}

PlayState::~PlayState() {
	for (int i = 0; i < 9; i++) {
		delete chunk[i];
	}
	delete tileAtlas;
}

void PlayState::init() {
	std::cout << "Init playstate" << std::endl;
	std::cout << Assets::isLoaded << std::endl;
	tileAtlas = new TextureAtlas(Assets::findTexture("tilemap"), 8, 8);

	for (int i = 0; i < 9; i++) {
		chunk[i] = new Chunk(win_mgr, renderer, tileAtlas);
		chunk[i]->setOffset(glm::vec2(int(i / 3), i % 3));
		chunk[i]->loadTiles();
	}

	std::cout << chunk[0]->min.x << "," << chunk[0]->min.y << " : " << chunk[0]->max.x << "," << chunk[0]->max.y << std::endl;
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
	if (zoom < 0.05f) zoom = 0.05f;

	target += velocity;

	win_mgr->camera->setZoom(zoom);
	win_mgr->camera->move(target, 0.09f);
	
	setActiveChunk(target);
	//std::cout << activeChunk << ": " << chunk[activeChunk]->getOffset().x << "," << chunk[activeChunk]->getOffset().y << std::endl;
}

void PlayState::setActiveChunk(const glm::vec2& playerPos) {
	for (int i = 0; i < 9; i++) {
		if (chunk[i]->inChunk(target)) {
			if (activeChunk != i) {
				activeChunk = i;
				loadAroundActive(playerPos);
			}
		}
	}
}

void PlayState::loadAroundActive(const glm::vec2& playerPos) {
	glm::vec2 chunkPos = chunk[activeChunk]->getOffset();
	glm::vec2 delta = { 1 - chunkPos.x, 1 - chunkPos.y };

	for (int i = 0; i < 9; i++) {
		chunk[i]->setOffset(glm::vec2(int(i / 3) - delta.x, (i % 3) - delta.y));
		chunk[i]->loadTiles();
	}
}

void PlayState::render() {
	for (int i = 0; i < 9; i++) {
		chunk[i]->render();
	}

	renderer->render(0, target, 0.0f, glm::vec2(8, 8), glm::vec4(1,0,1,1));
}

void PlayState::stop() {
	GameState::stop();
}