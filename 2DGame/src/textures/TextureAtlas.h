#pragma once

#include <vector>
#include "textures/Texture.h"

class TextureAtlas {
private:
	int tilesX, tilesY;
	Texture* baseTexture;

	std::vector<std::vector<Texture*>> tiles;

public:
	TextureAtlas(Texture* texture, int tilesX, int tilesY);
	~TextureAtlas();

	Texture* getTile(int x, int y);
	int getLengthX();
	int getLengthY();
};

