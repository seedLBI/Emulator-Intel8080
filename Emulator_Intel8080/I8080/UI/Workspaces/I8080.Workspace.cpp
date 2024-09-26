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
}


void I8080_Workspace::Load(const std::string& Data) {
	// Input first line not equal [BEGIN] [Workspace] (count lines) !!!!
	
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");

	int index = 0;
	while (index <= Lines.size() - 1) {

		std::string CurrentLine = Lines[index];

		std::vector<std::string> info = SplitLine(CurrentLine);

		if (info[0] == "Name")
			Name = info[1];
		else if (info[0] == "LoadStyle")
			LoadStyle = stoi(info[1]);
		else if (info[0] == "BEGIN") {

			auto begin = CurrentLine.find_first_of('(') + 1;
			auto end = CurrentLine.find_first_of(')');

			int countLine = std::stoi(CurrentLine.substr(begin, end - begin));

			std::string someData = "";
			if (info[1] == "Widgets") {
				someData = Lines[index] + "\n";
			}
			for (int i = index + 1; i < (index + 1) + countLine; i++)
				someData += Lines[i] + "\n";

			if (info[1] == "Widgets")
				Data_Widgets = someData;
			if (info[1] == "INI")
				Data_INI = someData;

			index += countLine;
		}
		index++;

	}

	//std::cout << "Data_Widget_Loaded:\n" + Data_Widgets;
	//std::cout << "Data_INI_Loaded:\n" + Data_INI;


}

std::string I8080_Workspace::Save() {
	std::string output = "";

	output += MakeBegin(GetCountLines(Data_INI) + GetCountLines(Data_Widgets) + 3);

	output += MakeSaveItem("Name", Name);
	output += MakeSaveItem("LoadStyle", std::to_string(LoadStyle));

	output += Data_Widgets;

	output += MakeBegin("INI", GetCountLines(Data_INI));
	output += Data_INI;

	return output;
}

void I8080_Workspace::SetName(std::string newName) {
	Name = newName;
}
std::string I8080_Workspace::GetName() {
	return Name;
}

