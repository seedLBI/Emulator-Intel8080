
#include "Config_Compilier.h"

#include <imgui_internal.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SOIL.h"

#include <iostream>
#include <string>
#include "ImagesData\Image_LogoApplicationArrayPngBytes.h"
#include <unordered_map>
#include <chrono>
#include <thread>


#pragma once
#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

namespace OpenglWindow {

	namespace Vars {
		extern int FPS_target;
		extern float DeltaaTime;
		extern float Width;
		extern float Height;
		extern float lasttime;
		extern std::string Title;
		extern bool FrameBufferSizeWasChanged;
		extern float TimeRender;
		extern GLFWwindow* window;
	}
	namespace Functions {
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void UpdateTimer();
		void CenterWindow();
	}

	bool CheckOpenglError(std::string command);
	std::string GetFramebufferErrorMeaning(GLenum status);
	void SetTargetFPS(float FPS);


	float GetDeltaTime();
	void BeginDraw();
	void EndDraw();
	void Init();
};



#endif // !OPENGLWINDOW_H