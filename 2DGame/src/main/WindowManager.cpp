#include <format>

#include "Global.h"
#include "WindowManager.h"

WindowManager::WindowManager() {
	createWindow();

	std::cout << "Init Window Manager" << std::endl;
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keys[i] = false;
	}

	for (int i = 0; i < 3; i++) {
		buttons[i] = false;
	}
}

WindowManager::~WindowManager() {
}

bool WindowManager::isKeyDown(int key) {
	return glfwGetKey(window, key);
}

bool WindowManager::isKeyPressed(int key) {
	return isKeyDown(key) && !keys[key];
}

bool WindowManager::isKeyReleased(int key) {
	return !isKeyDown(key) && keys[key];
}

bool WindowManager::isMouseButtonDown(int button) {
	return glfwGetMouseButton(window, button);
}

bool WindowManager::isMouseButtonPressed(int button) {
	return isMouseButtonDown(button) && !buttons[button];
}

bool WindowManager::isMouseButtonReleased(int button) {
	return !isMouseButtonDown(button) && buttons[button];
}

void WindowManager::updateWindow() {
	updateWindowFunctions();
	updateInput(); // Must be last
}

void WindowManager::updateWindowFunctions() {
	if (isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (isKeyPressed(GLFW_KEY_F11)) {
		if (!fullscreen) {
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			fullscreen = true;
		}
		else {
			glfwSetWindowMonitor(window, NULL, (mode->width / 2) - window_width / 2, (mode->height / 2) - window_height / 2,
				window_width, window_height, mode->refreshRate);
			fullscreen = false;
		}
	}

	if (!fullscreen) {
		glfwGetWindowSize(window, &window_width, &window_height);
	}
}

void WindowManager::updateInput() {
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keys[i] = isKeyDown(i);
	}

	for (int i = 0; i < 3; i++) {
		buttons[i] = isMouseButtonDown(i);
	}
}

void updateViewport(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void WindowManager::createWindow() {
	if (!glfwInit()) {
		glfwTerminate();
	}

	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	window = glfwCreateWindow(window_width, window_height,
		std::format("{} v{}", TITLE, VERSION).c_str(), NULL, NULL);

	if (!window) {
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); //vsync off
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetFramebufferSizeCallback(window, updateViewport);
}

GLFWwindow* WindowManager::getWindow() {
	return window;
}

int WindowManager::getWindowWidth() {
	return fullscreen ? mode->width : window_width;
}

int WindowManager::getWindowHeight() {
	return fullscreen ? mode->height : window_height;
}