#pragma once

#include "textures/Animation.h"

#include <vector>

class AnimationManager {
private:
	Animation* animationQueue[2];
	std::vector<std::vector<std::string>> switchTypes;

	std::string DO_LAST_FRAME = "true", NO_LAST_FRAME = "false";

	bool getDoLastFrame(std::string before, std::string after);

public:
	std::string NO_ANIM;

	void stopAnimation();
	void queueAnimation(Animation* animation);
	void tick();
	Texture* getCurrentFrame();
	Animation* getCurrentAnimation();

	void addSwitchType(std::string before, std::string after, bool doLastFrame);
};

