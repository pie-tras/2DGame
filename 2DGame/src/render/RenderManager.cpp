#include "Global.h"

#include "RenderManager.h"

RenderManager::RenderManager(WindowManager* win_mgr) {
	this->win_mgr = win_mgr;
	genShader = new GenShader("gen");

	//loadModel();
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//glEnable(GL_DEPTH_TEST);
}

RenderManager::~RenderManager() {
	delete genShader;
}

void RenderManager::loadModel() {
}

void RenderManager::prepare(Shader* shader) {
	if (activeShader != shader) {
		if (activeShader != nullptr) {
			finish(activeShader);
		}
		activeShader = shader;
		shader->start();
	}
}

void RenderManager::finish(Shader* shader) {
	shader->stop();
}

void RenderManager::loadGenUniforms(const glm::vec3& position, const glm::vec3& rotation_deg, const glm::vec2& scale, const glm::vec4& color) {
	glm::mat4 projection = glm::mat4(1.0f);

	
	projection = glm::perspective(70.0f, ((float)win_mgr->getWindowWidth()) / ((float)win_mgr->getWindowHeight()), 0.1f, 1000.0f);
	//projection = glm::ortho(-(float)win_mgr->getWindowWidth() / 2, (float)win_mgr->getWindowWidth() / 2, -(float)win_mgr->getWindowHeight() / 2, (float)win_mgr->getWindowHeight() / 2, -1.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation_deg.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation_deg.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation_deg.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));

	genShader->loadM(model);
	//genShader->loadV(win_mgr->camera->getViewMatrix());
	genShader->loadP(projection);
	genShader->loadColor(color);
}

//void RenderManager::render(Texture* texture, const glm::vec3& position, const glm::vec3& rotation_deg, const glm::vec2& scale) {
//	prepare(genShader);
//
//	if (texture != nullptr) {
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
//		genShader->loadTextureType(TextureType::NORMAL);
//	} else {
//		genShader->loadTextureType(TextureType::NONE);
//	}
//
//	loadGenUniforms(position, rotation_deg, scale, glm::vec4(1, 1, 1, 1));
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//}