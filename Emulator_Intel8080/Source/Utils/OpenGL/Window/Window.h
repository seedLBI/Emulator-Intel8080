
#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <iostream>


#ifndef WINDOW_H
#define WINDOW_H



class Window
{
public:
	Window();
	Window(const std::string& title);
	Window(const int& width, const int& height, const std::string& title);
	Window(const int& width,const int& height,const int& posX,const int& posY,const std::string& title);
	~Window();


	void SetCurrentContext();
	void SetTitle(const std::string& title);
	void SetPosition(const glm::vec2& pos);
	void SetSize(const glm::vec2& size);

	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	std::string GetTitle();


	void Centerize();
	void Maximize();
	void Hide();
	void Close();

	bool IsShouldClose();

	GLFWwindow* GetHandle();

private:
	GLFWwindow* handleWindow = nullptr;

	void InitGlew();
};





#endif