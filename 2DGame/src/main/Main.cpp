#include "Global.h"

#include "WindowManager.h"
#include "render/RenderManager.h"
#include "util/Loader.h"
#include "main/Assets.h"
#include "game/GameStateManager.h"
#include "main/FPSManager.h"

#ifdef _DEBUG
size_t allocated = 0;

void* operator new(size_t size) { 
    allocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    allocated -= size;
    free(memory);
}

#define _CHECKLEAKS if (allocated) { std::cout << "[MEMORY LEAK!]: " << allocated << " bytes of allocated memory still remain!" << std::endl; }

#else

#define _CHECKLEAKS

#endif

void cycle(GameStateManager* gsm, GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    gsm->update();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(void) {
    WindowManager* win_mgr = new WindowManager();
    GLFWwindow* window = win_mgr->getWindow();

    if (!window) {
        delete win_mgr;
        std::cout << "Window Failed to Load!" << std::endl;
        return -1;
    }

    RenderManager* renderer = new RenderManager(win_mgr);
    Loader* loader = new Loader();
    Assets::init();
    GameStateManager* gsm = new GameStateManager(win_mgr, renderer, loader);
    FPSManager* fps_mgr = new FPSManager(60, true);

    gsm->setActiveState(States::SPLASH);

    while (!glfwWindowShouldClose(window)) {
        fps_mgr->runCycle(cycle, gsm, window);
    }

    glfwTerminate();
    delete win_mgr;
    delete renderer;
    delete loader;
    delete gsm;
    delete fps_mgr;
    Assets::cleanUp();

    _CHECKLEAKS

    return 0;
}