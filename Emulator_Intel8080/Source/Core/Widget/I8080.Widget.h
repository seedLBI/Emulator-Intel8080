#ifndef WIDGET_H
#define WIDGET_H

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include "Core/SaveSystem/SaveSystem.h"

#include "Utils/Text/Encoding/UTF8/UTF8.h"
#include "Utils/Timer/Timer.Framerate.h"

#include <string>

class I8080_Widget : public SaveSystem
{
public:
	I8080_Widget(const std::string& Name, const bool& flag = false);
	~I8080_Widget();
	void Init_FPS_Timer(FPS_Timer* fps_timer);

	void virtual Draw();
	void virtual Update();

	void UpdateActive();

	bool GetFlagShow();
	void SetFlagShow(const bool& value);
	bool* GetPtrFlagShow();

	void SetFocus();
	void UpdateFocus();

	void MakeActiveCurrentWidget();
	void SetActive();



	bool WindowIsVisiable();

	float GetTimerFocus();

	std::string GetName();
	const char* GetName_c_str();

	virtual std::string GetCommand();


	void Load(const nlohmann::json& Data) override;
	nlohmann::json Save() override;

protected:
	float TimerFocus = 0.f;
	bool flag_FocusSeted = false;

	nlohmann::json SaveDefaultParameters();
	void ReadDefaultParameters(const nlohmann::json& Data);

private:
	std::string Name;
	const char* Name_c_str;
	bool* Show;
	int countSet = 0;
	bool IsSettedActive;
	FPS_Timer* fps_timer = nullptr;

};

#endif // !WIDGET_H
