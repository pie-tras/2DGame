#pragma once

#include "Global.h"
#include "render/shader.h"

class GenShader : public Shader {
private:
	unsigned int location_m = 0;
	unsigned int location_v = 0;
	unsigned int location_p = 0;
	unsigned int location_color = 0;
	unsigned int location_textureType = 0;
public:
	GenShader(const std::string& key);
	void getAllUniformLocations() override;
	void loadM(const glm::mat4& m);
	void loadV(const glm::mat4& v);
	void loadP(const glm::mat4& p);
	void loadColor(const glm::vec4& color);
	void loadTextureType(const int textureType);
};