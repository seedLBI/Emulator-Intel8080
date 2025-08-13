#ifndef APPLICATION_H
#define APPLICATION_H
#define WIN32_LEAN_AND_MEAN


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dwmapi.lib")

#include <Windows.h>
#include <stb_image.h>
#include <dwmapi.h>
#include <windowsx.h>
#include <string>
#include <unordered_map>


#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"
#include "ThirdParty/ImGui/imgui_impl_glfw.h"
#include "ThirdParty/ImGui/imgui_impl_opengl3.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/OpenGL/Window/Manager/WindowManager.h"
#include "Utils/Timer/Timer.Framerate.h"
#include "Core/FontManager/FontManager.h"


#include "Utils/File/File.h"

#include "GUI/MainMenuBar/MainMenuBar.h"

static WNDPROC orig_wndproc = nullptr;
static std::unordered_map<HWND, GLFWwindow*> g_hwnd_to_window;

enum BufferBit {
	COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
	DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
	STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT,
};

class Application {
private:
	const std::string Title = u8"Ёмул€тор Intel8080";
public:
	Application();
	~Application();

	void Run();
	MainMenuBar* GetPTR_MainMenuBar();
private:

	FPS_Timer* fps_limiter = nullptr;
	WindowManager* windowManager = nullptr;
	MainMenuBar* mainMenuBar = nullptr;
	FontManager* fontManager = nullptr;


	void Draw();

	void BeginDraw();
	void EndDraw();

	void Update();

	void Init_OpenGL();
	void Init_BorderWindow();
	void Init_ImGui();
};



#endif