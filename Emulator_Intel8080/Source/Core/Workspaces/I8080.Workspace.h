#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "Config_Compilier.h"

#include "Core/Widget/I8080.WidgetManager.h"
#include "Core/SaveSystem/SaveSystem.h"

#include "Utils/Text/Text.h"

#include <vector>
#include <string>

class I8080_Workspace : SaveSystem
{
public:
	I8080_Workspace(const std::string& Name, const bool& LoadStyle, I8080_WidgetManager* WidgetManager);
	I8080_Workspace(const std::string& Data, I8080_WidgetManager* WidgetManager);
	~I8080_Workspace();

	void			SetAsCurrent();

	void			SetName(std::string newName);
	std::string		GetName();

	nlohmann::json	Save() override;
	void			Load(const nlohmann::json& Data) override;

	void			LoadCurrent(const std::string& Name, const bool& LoadStyle);


	void			Rewrite();

private:
	I8080_WidgetManager* WidgetManager = nullptr;

	bool LoadStyle = false;

	std::string Name = "";
	nlohmann::json Data_Widgets;
	std::string Data_INI = "";
};


#endif