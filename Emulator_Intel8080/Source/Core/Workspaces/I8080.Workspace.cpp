#include "I8080.Workspace.h"


I8080_Workspace::I8080_Workspace(const std::string& Data, I8080_WidgetManager* WidgetManager) : SaveSystem("Workspace") {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_Workspace::I8080_Workspace(const std::string& Data, I8080_WidgetManager* WidgetManager) : SaveSystem(\"Workspace\")\n";
#endif // WITH_DEBUG_OUTPUT
	this->WidgetManager = WidgetManager;
	Load(Data);
}
I8080_Workspace::I8080_Workspace(const std::string& Name, const bool& LoadStyle, I8080_WidgetManager* WidgetManager) : SaveSystem("Workspace") {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_Workspace::I8080_Workspace(const std::string& Name, const bool& LoadStyle, I8080_WidgetManager* WidgetManager) : SaveSystem(\"Workspace\")\n";
#endif
	this->WidgetManager = WidgetManager;
	LoadCurrent(Name, LoadStyle);

#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Create workspace from current widgets\n";
#endif
}

I8080_Workspace::~I8080_Workspace() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_Workspace::~I8080_Workspace()\n";
#endif // !WITH_DEBUG_OUTPUT
}


void I8080_Workspace::SetAsCurrent() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_Workspace::SetAsCurrent()\n";

	if (WidgetManager == nullptr)
		std::cout << "Widget Manager = nullptr\n";

	if (Data_Widgets.empty())
		std::cout << "Data_Widgets is empty\n";

	if (Data_INI.empty())
		std::cout << "Data_INI is empty\n";
#endif

	if (!Data_Widgets.empty())
		WidgetManager->Load(Data_Widgets);

	if(!Data_INI.empty())
		ImGui::LoadIniSettingsFromMemory(Data_INI.data(), Data_INI.size());


}


void I8080_Workspace::LoadCurrent(const std::string& Name, const bool& LoadStyle) {
	Data_Widgets = WidgetManager->Save();
	Data_INI = ImGui::SaveIniSettingsToMemory();
	this->LoadStyle = LoadStyle;
	this->Name = Name;
}

void I8080_Workspace::Rewrite() {
	Data_Widgets = WidgetManager->Save();
	Data_INI = ImGui::SaveIniSettingsToMemory();

#ifdef WITH_DEBUG_OUTPUT
	std::cout << "REWRITING+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << Data_Widgets << std::endl << std::endl;
	std::cout << Data_INI << std::endl << std::endl;
#endif

}


void I8080_Workspace::Load(const nlohmann::json& Data) {

	Name = Data["name"].get<std::string>();
	LoadStyle = Data["flag_LoadStyle"].get<bool>();
	Data_Widgets = Data["widgets"];
	Data_INI = Data["imgui"].get<std::string>();

}

nlohmann::json I8080_Workspace::Save() {

	nlohmann::json result;

		result["name"] = Name;
		result["flag_LoadStyle"] = LoadStyle;
		result["widgets"] = Data_Widgets;
		result["imgui"] = Data_INI;

	return result;

}

void I8080_Workspace::SetName(std::string newName) {
	Name = newName;
}
std::string I8080_Workspace::GetName() {
	return Name;
}

