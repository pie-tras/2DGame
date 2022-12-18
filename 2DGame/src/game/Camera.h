#pragma once

#include "Global.h"

class Camera {
private:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	float zoom = 1.0f;
public:
	void move(const glm::vec2& target, const float t);
	glm::mat4 getViewMatrix();
	glm::vec2 getPosition();
	void setZoom(float zoom);
	float getZoom();
};