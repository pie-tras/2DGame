#include "AnimationManager.h"

void AnimationManager::stopAnimation() {
	if (animationQueue[0]) {
		animationQueue[0]->stop(getDoLastFrame(animationQueue[0]->getAnimName(), NO_ANIM));
	}
}

void AnimationManager::queueAnimation(Animation* animation) {
	if (!animationQueue[0]) {
		animationQueue[0] = animation;
	} else if(animationQueue[0] != animation) {
		animationQueue[1] = animation;
		animationQueue[0]->stop(getDoLastFrame(animationQueue[0]->getAnimName(), animation->getAnimName()));
	} else if(animationQueue[0]->isStopping()) {
		animationQueue[0]->start();
		animationQueue[1] = 0;
	}
}

void AnimationManager::tick() {
	if (animationQueue[0]) {
		if (animationQueue[0]->isFinished()) {
			animationQueue[0] = animationQueue[1];
			animationQueue[1] = 0;
		} else {
			animationQueue[0]->tick();
		}
	}
}

void AnimationManager::addSwitchType(std::string before, std::string after, bool doLastFrame) {
	std::vector<std::string> switchType;

	switchType.push_back(before);
	switchType.push_back(after);

	if(doLastFrame)
		switchType.push_back(DO_LAST_FRAME);
	else
		switchType.push_back(NO_LAST_FRAME);

	switchTypes.push_back(switchType);
}

bool AnimationManager::getDoLastFrame(std::string before, std::string after) {
	for (auto list : switchTypes) {
		if (list[0] == before && list[1] == after) {
			if (list[2] == DO_LAST_FRAME) {
				return true;
			} else {
				return false;
			}
		}
	}

	return false;
}

Texture* AnimationManager::getCurrentFrame() {
	if (animationQueue[0]) {
		return animationQueue[0]->getCurrentFrame();
	} else {
		return 0;
	}
}

Animation* AnimationManager::getCurrentAnimation() {
	return animationQueue[0];
}