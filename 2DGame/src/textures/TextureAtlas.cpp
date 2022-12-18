#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(Texture* texture, int tilesX, int tilesY)
	: baseTexture(texture), tilesX(tilesX), tilesY(tilesY) {

	for (int i = 0; i < tilesX; i++) {
		tiles.push_back(std::vector<Texture*>());
		for (int j = 0; j < tilesY; j++) {
			tiles[i].push_back(new Texture(baseTexture->getTextureID(), baseTexture->getWidth() / tilesX,
				baseTexture->getHeight() / tilesY, glm::vec2(i, j), glm::vec2(tilesX, tilesY)));
		}
	}
}

TextureAtlas::~TextureAtlas() {
	for (int i = 0; i < tilesX; i++) {
		for (int j = 0; j < tilesY; j++) {
			delete tiles[i][j];
		}
		tiles[i].clear();
	}

	tiles.clear();
}

Texture* TextureAtlas::getTile(int x, int y) {
	return tiles[x][y];
}

int TextureAtlas::getLengthX() {
	return tilesX;
}

int TextureAtlas::getLengthY() {
	return tilesY;
}