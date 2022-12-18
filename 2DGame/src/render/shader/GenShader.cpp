#include "GenShader.h"

GenShader::GenShader(const std::string& key) : Shader(key) {
	getAllUniformLocations();
}

void GenShader::getAllUniformLocations() {
	location_m = glGetUniformLocation(programID, "u_m");
	location_v = glGetUniformLocation(programID, "u_v");
	location_p = glGetUniformLocation(programID, "u_p");
	location_color = glGetUniformLocation(programID, "u_color");
	location_textureType = glGetUniformLocation(programID, "u_textureType");
}

void GenShader::loadM(const glm::mat4& m) {
	loadMat4f(location_m, m);
}

void GenShader::loadV(const glm::mat4& v) {
	loadMat4f(location_v, v);
}

void GenShader::loadP(const glm::mat4& p) {
	loadMat4f(location_p, p);
}

void GenShader::loadColor(const glm::vec4& color) {
	loadVec4f(location_color, color);
}

void GenShader::loadTextureType(const int textureType) {
	loadInt(location_textureType, textureType);
}