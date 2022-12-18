#include "Assets.h"

void Assets::init() {
	Assets::isLoaded = false;
	Assets::loaded_textures = new std::unordered_map<std::string, Texture*>();
}

void Assets::beginLoadTextures(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) {
	Assets::texturesTotal = loader->findTextures(win_mgr, renderer);
}

void Assets::continueLoadTextures(WindowManager* win_mgr, RenderManager* renderer, Loader* loader) {
	loader->loadNextTexture(win_mgr, renderer, Assets::texturesLoaded);
	Assets::texturesLoaded++;

	if (Assets::texturesLoaded == Assets::texturesTotal) {
		Assets::isLoaded = true;
	}
}

Texture* Assets::findTexture(std::string textureName) {
	if (Assets::loaded_textures->contains(textureName)) {
		return Assets::loaded_textures->find(textureName)->second;
	} else {
		std::cout << "Texture " << textureName << " could not be found!" << std::endl;
		return 0;
	}
}

void Assets::cleanUp() {
	for (auto texture : *Assets::loaded_textures) {
		delete texture.second;
	}

	Assets::loaded_textures->clear();
	delete Assets::loaded_textures;
}