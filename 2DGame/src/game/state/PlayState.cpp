#include "PlayState.h"

PlayState::PlayState(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) : GameState(win_mgr, renderer, loader) {

}

PlayState::~PlayState() {
	delete tileAtlas;
	delete sheepAtlas;
	delete sheepAnim;
	delete animManager;
}

void PlayState::init() {
	std::cout << "Init playstate" << std::endl;
	std::cout << Assets::isLoaded << std::endl;
	playerTexture = Assets::findTexture("sheep");
	tileTexture = Assets::findTexture("tile");

	tileAtlas = new TextureAtlas(Assets::findTexture("tiles"), 2, 2);

	sheepAtlas = new TextureAtlas(Assets::findTexture("sheepAnim"), 2, 2);
	sheepAnim = new Animation(sheepAtlas, 2000, "walk");

	animManager = new AnimationManager();
	animManager->addSwitchType("walk", animManager->NO_ANIM, true);

	for (int i = 0; i < worldSize; i++) {
		for (int j = 0; j < worldSize; j++) {
			tileMap[i][j] = rand() % 4;
		}
	}
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

	if (win_mgr->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		placedObjects.push_back(win_mgr->getMouseWorldPosition());
	}

	if (zoom > 2.0f) zoom = 2.0f;
	if (zoom < 0.4f) zoom = 0.4f;

	target += velocity;

	win_mgr->camera->setZoom(zoom);
	win_mgr->camera->move(target, 0.09f);

	if (velocity.x == 0 && velocity.y == 0) {
		animManager->stopAnimation();
	} else {
		animManager->queueAnimation(sheepAnim);
	}

	animManager->tick();
}

void PlayState::render() {
	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			int i = tileMap[x][y];
			renderer->render(tileAtlas->getTile(i % 2, (int)(i / 2)), glm::vec2(x * 32, y * 32), 0.0f, glm::vec2(16, 16));
		}
	}

	for (glm::vec2 obj : placedObjects) {
		renderer->render(0, obj, 0, glm::vec2(2, 2), glm::vec4(1, 0, 1, 1));
	}
	if(animManager->getCurrentFrame())
		renderer->render(animManager->getCurrentFrame(), target, 0.0f, glm::vec2(16, 16));
	else
		renderer->render(playerTexture, target, 0.0f, glm::vec2(16, 16));
}

void PlayState::stop() {
	GameState::stop();
}