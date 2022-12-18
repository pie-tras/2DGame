#include "Loader.h"
#include <filesystem>
#include "main/Assets.h"

namespace fs = std::filesystem;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int Loader::findTextures(WindowManager* win_mgr, RenderManager* renderer) {
	for (const auto& p : fs::directory_iterator(res_path)) {
		std::string path = p.path().string();

		file_paths.push_back(path);
		file_names.push_back(path.substr(res_path.length() + 1, path.length() - res_path.length() - 5));
	}

	return (int)file_names.size();
}

void Loader::loadNextTexture(WindowManager* win_mgr, RenderManager* renderer, int nextTexture) {
	loadTexture(file_paths.at(nextTexture), file_names.at(nextTexture));
	std::cout << file_names.at(nextTexture) << std::endl;
}

void Loader::loadTexture(const std::string& file_path, const std::string& key) {
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture at: " << file_path << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	Assets::loaded_textures->insert({ key, new Texture(texID, width, height) });

	stbi_image_free(data);
}
