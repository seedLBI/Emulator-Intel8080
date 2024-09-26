#include "OpenglWindow\OpenglWindow.h"

#ifndef WIDGET_H
#define WIDGET_H

#include "SaveSystem\SaveSystem.h"
#include <string>

class I8080_Widget : public SaveSystem
{
public:
	I8080_Widget(const std::string& Name, const bool& flag = false);
	~I8080_Widget();

	void virtual Draw();
	void virtual Update();

	bool GetFlagShow();
	void SetFlagShow(const bool& value);
	bool* GetPtrFlagShow();

	std::string GetName();
	const char* GetName_c_str();

	void Load(const std::string& Data) override;
	std::string Save() override;

private:
	std::string Name;
	const char* Name_c_str;
	bool* Show;
};

#endif // !WIDGET_H
