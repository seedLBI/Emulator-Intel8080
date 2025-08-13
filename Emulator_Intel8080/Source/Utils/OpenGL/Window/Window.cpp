#include "Window.h"

void Window::InitGlew() {

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-2);
	}

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

}

void Window::SetTitle(const std::string& title) {
	glfwSetWindowTitle(handleWindow, title.c_str());

}
void Window::SetPosition(const glm::vec2& pos) {
	glfwSetWindowPos(handleWindow, static_cast<int>(pos.x), static_cast<int>(pos.y));
}
void Window::SetSize(const glm::vec2& size) {
	glfwSetWindowSize(handleWindow, static_cast<int>(size.x), static_cast<int>(size.y));
	glViewport(0, 0, size.x, size.y);
}


glm::vec2 Window::GetSize() {
	int width, height;
	glfwGetWindowSize(handleWindow, &width, &height);
	return glm::vec2(width, height);
}
glm::vec2 Window::GetPosition() {
	int posX = 0, posY = 0;
	glfwGetWindowPos(handleWindow, &posX, &posY);
	return glm::vec2(posX, posY);
}
std::string Window::GetTitle() {
	return glfwGetWindowTitle(handleWindow);
}


void Window::Centerize() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	int currentWidth, currentHeight;
	glfwGetWindowSize(handleWindow, &currentWidth, &currentHeight);

	glfwSetWindowPos(handleWindow, (mode->width - currentWidth) / 2, (mode->height - currentHeight) / 2);
}

void Window::SetCurrentContext() {
	glfwMakeContextCurrent(handleWindow);
}

void Window::Maximize() {
	glfwMaximizeWindow(handleWindow);
}
void Window::Hide() {
	glfwHideWindow(handleWindow);
}

void Window::Close() {
	glfwSetWindowShouldClose(handleWindow, 1);
}

bool Window::IsShouldClose() {
	return glfwWindowShouldClose(handleWindow);
}

GLFWwindow* Window::GetHandle() {
	return handleWindow;
}

Window::Window(const int& width, const int& height, const int& PosX, const int& PosY, const std::string& Title) {
	handleWindow = glfwCreateWindow(width, height, Title.c_str(), NULL, NULL);
	if (handleWindow == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	SetCurrentContext();

	InitGlew();

	SetPosition({ PosX, PosY });
}

Window::Window(const int& width, const int& height, const std::string& Title) {
	handleWindow = glfwCreateWindow(width, height, Title.c_str(), NULL, NULL);
	if (handleWindow == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	SetCurrentContext();

	InitGlew();

	Centerize();
}

Window::Window(const std::string& title) {
	handleWindow = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	if (handleWindow == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	SetCurrentContext();

	InitGlew();

	Centerize();
}

Window::Window() {
	handleWindow = glfwCreateWindow(800, 600, "Unknown window...", NULL, NULL);
	if (handleWindow == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	SetCurrentContext();

	InitGlew();

	Centerize();

}

Window::~Window() {
#ifdef _DEBUG
	std::cout << "Window::~Window()\n";
#endif
	
	glfwDestroyWindow(handleWindow);
}