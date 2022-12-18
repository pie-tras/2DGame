#pragma once

#include <vector>
#include <string>

#include "textures/Texture.h"
#include "textures/TextureAtlas.h"
#include "util/Timer.h"

class Animation {
private:
	int currentFrame = 0, timer = 0;
	double animLength; //ms
	bool shouldStop = false, finished = false, playing = false;
	std::string animName;
	Timer frameTimer;
	std::vector<Texture*> frames;

	void finish();

public:
	Animation(TextureAtlas* atlas, double animLength, std::string animName);

	void start();
	void stop(bool doLastFrame);
	void tick();

	bool isFinished();
	bool isStopping();

	std::string getAnimName();

	Texture* getCurrentFrame();
};

