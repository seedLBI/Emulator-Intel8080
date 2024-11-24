#include "OpenglWindow\OpenglWindow.h"

#ifndef WIDGET_H
#define WIDGET_H

#include "imgui.h"
#include "SaveSystem\SaveSystem.h"
#include "Utils/UTF8.h"
#include <string>

class I8080_Widget : public SaveSystem
{
public:
	I8080_Widget(const std::string& Name, const bool& flag = false);
	~I8080_Widget();

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


	void Load(const std::string& Data) override;
	std::string Save() override;

protected:
	float TimerFocus = 0.f;
	bool flag_FocusSeted = false;

private:
	std::string Name;
	const char* Name_c_str;
	bool* Show;
	int countSet = 0;
	bool IsSettedActive;

};

#endif // !WIDGET_H
