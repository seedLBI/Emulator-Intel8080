#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include "OpenglWindow\OpenglWindow.h"
#include "SaveSystem\SaveSystem.h"
#include "Utils/ImGui.Utils.h"

class WindowManager : public SaveSystem
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
	void Draw();

	std::string Save() override;
	void Load(const std::string& Data) override;


private:
	bool IsWindowed = true;
	int LastPos_x = 0, LastPos_y = 0, LastSize_x = 0, LastSize_y = 0;


	bool VSync_state = false;
};




#endif // !WINDOW_MANAGER_H
