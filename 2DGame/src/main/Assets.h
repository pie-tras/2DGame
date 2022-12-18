#pragma once

#include <unordered_map>
#include <string>

#include "Global.h"
#include "render/RenderManager.h"
#include "main/WindowManager.h"
#include "util/Loader.h"
#include "textures/Texture.h"

class Assets {
public:
    static inline bool isLoaded;
    static inline std::unordered_map<std::string, Texture*>* loaded_textures;
    static inline int texturesLoaded = 0;
    static inline int texturesTotal = 0;

    static void init();
    static void beginLoadTextures(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
    static void continueLoadTextures(WindowManager* win_mgr, RenderManager* renderer, Loader* loader);
    static Texture* findTexture(std::string textureName);
    static void cleanUp();

private:
};

