#include "OpenGL.WindowManager.h"

OpenGL_WindowManager::OpenGL_WindowManager(const std::string& title, const int& width, const int& height, const int& posX, const int& posY) {
#ifdef _DEBUG
	std::cout << "OpenGL_WindowManager::OpenGL_WindowManager(const std::string& title, const int& width, const int& height, const int& posX, const int& posY)\n";
#endif // 
	MainWindow = std::make_unique<Window>(width, height, posX, posY, title);

}

OpenGL_WindowManager::~OpenGL_WindowManager() {
#ifdef _DEBUG
	std::cout << "OpenGL_WindowManager::~OpenGL_WindowManager()\n";
#endif // 
}

Window* OpenGL_WindowManager::GetMainWindow() {
	return MainWindow.get();
}


std::vector<std::string> OpenGL_WindowManager::GetListTitles() {
	std::vector<std::string> output;

	for (const std::unique_ptr<Window>& obj : windows) {
		output.push_back(obj.get()->GetTitle());
	}

	return output;
}
Window* OpenGL_WindowManager::GetWindowByTitle(const std::string& title) {

	for (int i = 0; i < windows.size(); i++) {
		if (windows[i].get()->GetTitle() == title) {
			return windows[i].get();
		}
	}

}


void OpenGL_WindowManager::AddWindow(std::unique_ptr<Window> window_ptr) {
	windows.push_back(std::move(window_ptr));
}

void OpenGL_WindowManager::AddWindow(const std::string& title) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(title);
	temp.get()->SetTitle(title);
	windows.push_back(std::move(temp));
}
void OpenGL_WindowManager::AddWindow(const std::string& title, const int& width, const int& height) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(width, height, title);

	windows.push_back(std::move(temp));
}
void OpenGL_WindowManager::AddWindow(const std::string& title, const int& width, const int& height, const int& posX, const int& posY) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(width, height, posX, posY, title);

	windows.push_back(std::move(temp));
}