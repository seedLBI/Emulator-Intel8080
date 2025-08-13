#include "WindowManager.h"

WindowManager::WindowManager(const std::string& title, const int& width, const int& height, const int& posX, const int& posY) {
#ifdef _DEBUG
	std::cout << "WindowManager::WindowManager(const std::string& title, const int& width, const int& height, const int& posX, const int& posY)\n";
#endif // 
	MainWindow = std::make_unique<Window>(width, height, posX, posY, title);

}

WindowManager::~WindowManager() {
#ifdef _DEBUG
	std::cout << "WindowManager::~WindowManager()\n";
#endif // 
}

Window* WindowManager::GetMainWindow() {
	return MainWindow.get();
}


std::vector<std::string> WindowManager::GetListTitles() {
	std::vector<std::string> output;

	for (const std::unique_ptr<Window>& obj : windows) {
		output.push_back(obj.get()->GetTitle());
	}

	return output;
}
Window* WindowManager::GetWindowByTitle(const std::string& title) {

	for (int i = 0; i < windows.size(); i++) {
		if (windows[i].get()->GetTitle() == title) {
			return windows[i].get();
		}
	}

}


void WindowManager::AddWindow(std::unique_ptr<Window> window_ptr) {
	windows.push_back(std::move(window_ptr));
}

void WindowManager::AddWindow(const std::string& title) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(title);
	temp.get()->SetTitle(title);
	windows.push_back(std::move(temp));
}
void WindowManager::AddWindow(const std::string& title, const int& width, const int& height) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(width, height, title);

	windows.push_back(std::move(temp));
}
void WindowManager::AddWindow(const std::string& title, const int& width, const int& height, const int& posX, const int& posY) {
	std::unique_ptr<Window> temp = std::make_unique<Window>(width, height, posX, posY, title);

	windows.push_back(std::move(temp));
}