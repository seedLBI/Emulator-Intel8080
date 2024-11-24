#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include "OpenglWindow\OpenglWindow.h"
#include "UI/Setting/ISettingObject.h"
#include "SaveSystem\SaveSystem.h"
#include "Utils/ImGui.Utils.h"

class WindowManager : public ISettingObject
{
public:
	WindowManager();
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
	std::string SaveSetting() override;
	void LoadSetting(const std::string& Data) override;


private:
	bool IsWindowed = true;
	int LastPos_x = 0, LastPos_y = 0, LastSize_x = 0, LastSize_y = 0;


	bool VSync_state = false;


	void CheckPosition(int& Position_X, int& Position_Y);
	void CheckSize(int& Size_X, int& Size_Y);
};




#endif // !WINDOW_MANAGER_H
