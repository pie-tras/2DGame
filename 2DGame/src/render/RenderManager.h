#pragma once

#include "Global.h"
#include "main/WindowManager.h"
#include "render/shader/GenShader.h"

class RenderManager {
private:
	WindowManager* win_mgr;
	Shader* activeShader;

	GenShader* genShader;

	void loadModel();
	void prepare(Shader* shader);
	void finish(Shader* shader);
	void loadGenUniforms(const glm::vec3& position, const glm::vec3& rotation_deg, const glm::vec2& scale, const glm::vec4& color);

public:
	RenderManager(WindowManager* win_mgr);
	~RenderManager();
};