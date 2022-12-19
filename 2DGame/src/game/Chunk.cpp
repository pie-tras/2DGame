#include "Chunk.h"

Chunk::Chunk(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas) : 
	win_mgr(win_mgr), renderer(renderer), tileAtlas(tileAtlas) {
}

Chunk::~Chunk() {}

void Chunk::loadTiles() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			int x = i + (offset.x * size);
			int y = j + (offset.x * size);
			const double height = perlin1.octave2D_01((x * 0.005), (y * 0.005), 4);
			const double temp = perlin2.octave2D_01((x * 0.05), (y * 0.05), 4);

			float water = 0.5;
			float shore = 0.51;
			float ice = 0.95;

			int land[6] = { 0, 1, 2, 3, 4, 6 };

			int tile = 0;

			if (height <= water) {
				tile = 5;
			} else if (height > water && height <= shore) {
				tile = 4;
			} else if (height > shore && height <= ice) {
				tile = land[int(temp * 5)];
			} else {
				tile = 7;
			}

			tileMap[i][j] = tile; //xy to height func
		}
	}
}

void Chunk::renderTile(int id, int x, int y) {
	glm::vec2 pos = { (x - ROffset) * 32, (y - ROffset) * 32 };
	if (win_mgr->onScreen(pos))
		renderer->render(tileAtlas->getTile(id % 8, (int)(id / 8)), pos, 0.0f, glm::vec2(16, 16));
}
void Chunk::render() {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			int id = tileMap[x][y];
			renderTile(id, x + (offset.x * size), y + (offset.y * size));
		}
	}
}

bool Chunk::inChunk(const glm::vec2& worldPos) {
	if (worldPos.x > max.x || worldPos.y > max.y || worldPos.x < min.x || worldPos.y < min.y) {
		return false;
	}
	return true;
}

int Chunk::getSize() {
	return size;
}

void Chunk::moveOffset(const glm::vec2& delta) {
	setOffset(glm::vec2(offset.x + delta.x, offset.y + delta.y));
}

void Chunk::setOffset(const glm::vec2& newOffset) {
	offset = newOffset;
	min = { ((offset.x * size) - ROffset) * 32, ((offset.y * size) - ROffset) * 32 };
	max = { min.x + size * 32, min.y + size * 32 };
}

glm::vec2& Chunk::getOffset() {
	return offset;
}