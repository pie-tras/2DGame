#include "Global.h"
#include "WindowManager.h"
#include "render/RenderManager.h"
#include "game/GameStateManager.h"
#include "main/FPSManager.h"

#include "LeakCheck.h"

void cycle(GameStateManager* gsm, GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    gsm->update();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(void)
{
    WindowManager* win_mgr = new WindowManager();

    if (!win_mgr->getWindow()) {
        delete win_mgr;
        std::cout << "Window Failed to Load!" << std::endl;
        return -1;
    }

    RenderManager* renderer = new RenderManager(win_mgr);
    
    GameStateManager* gsm = new GameStateManager(win_mgr, renderer);
    FPSManager* fps_mgr = new FPSManager(60, true);

    gsm->setActiveState(States::SPLASH);

    while (!glfwWindowShouldClose(win_mgr->getWindow())) {
        fps_mgr->runCycle(cycle, gsm, win_mgr->getWindow());
    }

    glfwTerminate();
    delete win_mgr;
    delete renderer;
    delete gsm;
    delete fps_mgr;

    _CHECKLEAKS

    return 0;
}