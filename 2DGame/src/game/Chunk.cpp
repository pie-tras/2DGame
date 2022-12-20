#include "Chunk.h"

Chunk::Chunk(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas, int depth, int size, int tileSize) : 
	win_mgr(win_mgr), renderer(renderer), tileAtlas(tileAtlas), depth(depth), size(size), tileSize(tileSize) {

	data = new int** [depth + 1];

	for (int i = 0; i < depth + 1; i++) {
		data[i] = new int* [size];
		for (int j = 0; j < size; j++) {
			data[i][j] = new int[size];
		}
	}
}

Chunk::~Chunk() {
	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < size; j++) {
			delete[] data[i][j];
		}
		delete[] data[i];
	}
	delete[] data;

}

void Chunk::renderTile(int id, int x, int y) {
	glm::vec2 pos = { (x) * tileSize, (y) * tileSize };
	renderer->render(tileAtlas->getTile(id % 8, (int)(id / 8)), pos, 0.0f, glm::vec2(tileSize/2, tileSize/2));
}

void Chunk::render() {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			int elevation = data[depth][x][y];
			int id = data[elevation][x][y];
			renderTile(id, x + (offset.x * size), y + (offset.y * size));
		}
	}
}

void Chunk::moveOffset(const glm::vec2& delta) {
	setOffset(glm::vec2(offset.x + delta.x, offset.y + delta.y));
}

void Chunk::setOffset(const glm::vec2& newOffset) {
	offset = newOffset;
}

glm::vec2& Chunk::getOffset() {
	return offset;
}