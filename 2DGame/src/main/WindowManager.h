#pragma once

#include "Global.h"

class WindowManager {
private:
    GLFWwindow* window;
    GLFWmonitor* monitor;
    const GLFWvidmode* mode;

    int window_width = 800;
    int window_height = 600;
    const std::string TITLE = "2D Game";
    const double VERSION = 0.1;

    bool keys[GLFW_KEY_LAST];
    bool buttons[3];

    bool fullscreen = false;

    void updateInput();
    void updateWindowFunctions();
public:
    WindowManager();
    ~WindowManager();

    bool isKeyDown(int key);
    bool isKeyPressed(int key);
    bool isKeyReleased(int key);

    bool isMouseButtonDown(int button);
    bool isMouseButtonPressed(int button);
    bool isMouseButtonReleased(int button);

    void updateWindow();

    void createWindow();
    GLFWwindow* getWindow();

    int getWindowWidth();
    int getWindowHeight();
};