#pragma once

#include <unordered_map>
#include <string>

#include "Global.h"
#include "render/RenderManager.h"
#include "main/WindowManager.h"
#include "textures/Texture.h";

class Loader {
private:
    const std::string res_path = "res/textures";

    std::vector<std::string> file_paths;
    std::vector<std::string> file_names;

    void loadTexture(const std::string& file_path, const std::string& key);
 
public:
    int findTextures(WindowManager* win_mgr, RenderManager* renderer);
    void loadNextTexture(WindowManager* win_mgr, RenderManager* renderer, int nextTexture);
};