#include "Animation.h"

Animation::Animation(TextureAtlas* atlas, double animLength, std::string animName) 
	: animLength(animLength), animName(animName) {
	for (int i = 0; i < atlas->getLengthY(); i++) {
		for (int j = 0; j < atlas->getLengthX(); j++) {
			frames.push_back(atlas->getTile(j, i));
		}
	}
}

void Animation::start() {
	if (!playing) {
		frameTimer.setStopwatch();
	}
	shouldStop = false;
	playing = true;
}

void Animation::stop(bool doLastFrame) {
	if (doLastFrame)
		shouldStop = true;
	else
		finish();
}

void Animation::finish() {
	currentFrame = 0;

	shouldStop = false;
	finished = true;
	playing = false;
}

void Animation::tick() {
	if (frameTimer.getStopwatch() / 1000 > (float) animLength / (float) frames.size()) {
		currentFrame++;
		frameTimer.setStopwatch();

		if (shouldStop) {
			finish();
		} else if (currentFrame == frames.size()) {
			currentFrame = 0;
		}
	}
}

bool Animation::isFinished() {
	if (finished) {
		finished = false;
		return true;
	} else {
		return false;
	}
}

bool Animation::isStopping() {
	return shouldStop;
}

std::string Animation::getAnimName() {
	return animName;
}

Texture* Animation::getCurrentFrame() {
	return frames[currentFrame];
}