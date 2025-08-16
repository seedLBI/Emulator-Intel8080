#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"
#include "Utils/ImGui/Utils.ImGui.h"
#include "Utils/Timer/Timer.Framerate.h"


class WindowManager : public ISettingObject
{
public:
	WindowManager(GLFWwindow* window, FPS_Timer* fps_timer);
	~WindowManager();


	bool SetFullscreen();
	bool SetWindowed();
	void ToggleFullscreen();
	bool GetStateFullscreen();

	void SetMaximaze();

	void DisableVSync();
	void EnableVSync();
	void ToggleVSync();
	void SetVSync(bool flag);
	bool GetStateVSync();
	
	void SetPosition(const int& posX,const int& posY);
	void SetSize(const int& width,const int& height);


	// Put it in Settings
	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;


private:
	GLFWwindow* window;
	FPS_Timer* fps_timer;

	bool IsWindowed = true;
	int LastPos_x = 0, LastPos_y = 0, LastSize_x = 0, LastSize_y = 0;

	bool VSync_state = false;

	void CheckPosition(int& Position_X, int& Position_Y);
	void CheckSize(int& Size_X, int& Size_Y);
};




#endif // !WINDOW_MANAGER_H
