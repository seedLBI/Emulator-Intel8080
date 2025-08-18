#ifndef OPENGL_WINDOW_MANAGER_H
#define OPENGL_WINDOW_MANAGER_H

#include "Utils/OpenGL/Window/Window.h"
#include <string>
#include <memory>
#include <vector>


class OpenGL_WindowManager
{
public:
	OpenGL_WindowManager(const std::string& title, const int& width, const int& height, const int& posX, const int& posY);
	~OpenGL_WindowManager();

	Window* GetMainWindow();

	std::vector<std::string> GetListTitles();
	Window* GetWindowByTitle(const std::string& title);

	void AddWindow(std::unique_ptr<Window> window_ptr);
	void AddWindow(const std::string& title);
	void AddWindow(const std::string& title, const int& width,const int& height);
	void AddWindow(const std::string& title, const int& width, const int& height, const int& posX, const int& posY);

private:
	std::vector< std::unique_ptr<Window> > windows;
	std::unique_ptr<Window> MainWindow;

	void MakeMainWindow();

};






#endif