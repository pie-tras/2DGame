#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "MapGen.h"

MapGen::MapGen(WindowManager* win_mgr, RenderManager* renderer, TextureAtlas* tileAtlas, int chunkSize, int mapSize, int chunkDepth, int tileSize, int seed) :
    win_mgr(win_mgr), renderer(renderer), tileAtlas(tileAtlas), chunkSize(chunkSize), mapSize(mapSize), chunkDepth(chunkDepth), tileSize(tileSize), seed(seed) {

    srand(seed);

    const siv::PerlinNoise::seed_type seed1 = 12345u;
    const siv::PerlinNoise::seed_type seed2 = rand() % 9999;

    heightPerlin = siv::PerlinNoise{ seed1 };
    tempPerlin = siv::PerlinNoise{ seed2 };
}


MapGen::~MapGen() {
    for (int i = 0; i < 9; i++) {
        delete chunk[i];
    }
}

void MapGen::generate() {

    for (int i = 0; i < mapSize*mapSize; i++) {
        writeChunk(i);
    }

    for (int i = 0; i < 9; i++) {
        chunk[i] = new Chunk(win_mgr, renderer, tileAtlas, chunkDepth, chunkSize, tileSize);
        chunk[i]->setOffset(glm::vec2(int(i / 3), i % 3));
    }

    getActiveChunk(glm::vec2(200, 200));

}

void MapGen::renderChunks(const glm::vec2& playerPos) {
    getActiveChunk(playerPos);
    for (int i = 0; i < 9; i++) {
        chunk[i]->render();
    }
}

void MapGen::loadAroundActive(const glm::vec2& playerPos) {
    for (int i = 0; i < 9; i++) {
       glm::vec2 pos = { int(i / 3) + chunkPos.x - 1, (i % 3) + chunkPos.y - 1 };
       chunk[i]->setOffset(pos);
       int id = (pos.x * mapSize) + pos.y;
       if (id < 0) id = 0;
       if (id > mapSize * mapSize) id = mapSize;
       loadChunk(id, i); 
    }
}

int MapGen::getActiveChunk(const glm::vec2& playerPos) {
    chunkPos = { floor(playerPos.x / (chunkSize * tileSize)), floor(playerPos.y / (chunkSize * tileSize)) };
    if (chunkPos.x > (mapSize - 1) || chunkPos.y > (mapSize - 1) || chunkPos.x < 0 || chunkPos.y < 0) return activeChunk;
    int next = (chunkPos.x * mapSize) + chunkPos.y;
    if (next != activeChunk) {
        activeChunk = next;
        loadAroundActive(playerPos);
    }
    return activeChunk;
}

int MapGen::getSurfaceTile(int x, int y) {
    const double height = heightPerlin.octave2D_01((x * 0.01), (y * 0.01), 4);
    const double tempNoise = tempPerlin.octave2D_01((x * 0.007), (y * 0.007), 4);

    double north = 1 - (y / double (mapSize * chunkSize));
    double temp = north + (tempNoise / 10.0);

    double water = 0.5;
    double shore = 0.55;

    double freezing = 0.2;
    double hot = 0.8;

    int tile = 0;

    if (height <= water) {
        if (temp < freezing) {
            tile = 7;
        } else if (temp > hot) {
            tile = 4;
        } else {
            tile = 5;
        }
    } else if (height > water && height <= shore) {
        tile = 4;
    } else {
        if (temp < freezing) {
            tile = 2;
        } else if (temp > hot) {
            tile = 4;
        } else {
            tile = 0;
        }
    }

    return tile;
}

int MapGen::getTile(int x, int y, int depth) {
    switch (depth) {
        case 0:
            return getSurfaceTile(x, y);
        case 1:
            return 1;
        default:
            return 3;
    }
}

void MapGen::writeChunk(int id) {
    std::string path = "data/map/chunk/" + std::to_string(id) + ".chunk";
    std::ofstream chunkStream(path);

    for (int i = 0; i < chunkDepth; i++) {
        for (int y = 0; y < chunkSize; y++) {
            for (int x = 0; x < chunkSize; x++) {
                int worldX = (int(id / mapSize) * chunkSize) + x;
                int worldY = ((id % mapSize) * chunkSize) + y;
                chunkStream << getTile(worldX, worldY, i);
                if (x != chunkSize - 1) {
                    chunkStream << ",";
                }
            }
            chunkStream << "\n";
        }
        chunkStream << "###\n";
    }

    for (int y = 0; y < chunkSize; y++) {
        for (int x = 0; x < chunkSize; x++) {
            chunkStream << 0;
            if (x != chunkSize - 1) {
                chunkStream << ",";
            }
        }
        chunkStream << "\n";
    }

    chunkStream.close();
}

void MapGen::loadChunk(int chunkId, int loadId) {
    std::string path = "data/map/chunk/" + std::to_string(chunkId) + ".chunk";
    std::ifstream chunkStream(path);
    std::string line;

    int currentDepth = 0;
    int row = 0;

    while (getline(chunkStream, line)) {
        if (line == "###") {
            currentDepth++;
            row = 0;
        } else {
            std::stringstream splitStream(line);
            std::string val;
            std::vector<std::string> values;
            values.reserve(std::count_if(line.begin(), line.end(), [&](char c) { return c == ','; }) + (line.empty() ? 1 : 0));

            while (std::getline(splitStream, val, ',')) {
                values.push_back(val);
            }
            
            for (int i = 0; i < values.size(); i++) {
                chunk[loadId]->data[currentDepth][i][row] = stoi(values.at(i));
            }
            row++;
        }
    }

    chunkStream.close();
}