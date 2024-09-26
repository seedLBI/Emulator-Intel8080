#include "I8080.WorkspaceManager.h"

I8080_WorkspaceManager::I8080_WorkspaceManager(I8080_WidgetManager* widget_manager):SaveSystem("Workspaces") {
	this->widget_manager = widget_manager;
}

I8080_WorkspaceManager::~I8080_WorkspaceManager() {

}

void I8080_WorkspaceManager::AddWorkspace(const std::string& Name, const bool& LoadStyle) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_WorkspaceManager::AddWorkspace(const std::string& Name, const bool& LoadStyle)\n";
#endif
	workspaces.emplace_back(I8080_Workspace(Name, LoadStyle,widget_manager));
}


std::string I8080_WorkspaceManager::Save() {
	std::string output;

	std::string Data_workspaces = "";
	for (int i = 0; i < workspaces.size(); i++)
		Data_workspaces += workspaces[i].Save();

	output += MakeBegin(GetCountLines(Data_workspaces) + 1);
	output += Data_workspaces;
	output += MakeSaveItem("IndexChoosed", std::to_string(IndexChoosed));


	return output;
}


void I8080_WorkspaceManager::Load(const std::string& Data) {

	PrintDebugInfoAboutData(Data);

	
	std::vector<std::string> Lines = split(Data, "\n");

	int index = 0;
	while (index <= Lines.size() - 1) {

		std::string CurrentLine = Lines[index];

		std::vector<std::string> info = SplitLine(CurrentLine);


		if (info[0] == "BEGIN") {

			auto begin = CurrentLine.find_first_of('(') + 1;
			auto end = CurrentLine.find_first_of(')');

			int countLine = std::stoi(CurrentLine.substr(begin, end - begin));

			std::string DataWorkspace = "";

			for (int i = index + 1; i < (index + 1) + countLine; i++)
				DataWorkspace += Lines[i] + "\n";


			//std::cout << DataWorkspace << std::endl;

			if (!DataWorkspace.empty()) {
				workspaces.emplace_back(I8080_Workspace(DataWorkspace, widget_manager));
			}
			else {
#ifdef WITH_DEBUG_OUTPUT
				std::cout << "Workspace data empty\n";
#endif
			}
			
			index += countLine;
		}
		else if (info[0] == "IndexChoosed") {
			if (stoi(info[1]) < 0) {
				IndexChoosed = 0;
			}
			else if (stoi(info[1]) > workspaces.size() - 1) {
				IndexChoosed = 0;
			}
			else {
				IndexChoosed = stoi(info[1]);
			}
			SetNeedLoad();
		}
		index++;

	}
	
}



std::string I8080_WorkspaceManager::GetNameCurrentWorkspace() {
	if (workspaces.size() == 0)
		return u8"Нет пространств";
	if (IndexChoosed > workspaces.size() - 1)
		return u8"Выбери!";
	return workspaces[IndexChoosed].GetName();
}

int I8080_WorkspaceManager::GetCount() {
	return workspaces.size();
}

int I8080_WorkspaceManager::GetIndexChoosed() {
	return IndexChoosed;
}
void I8080_WorkspaceManager::SetIndexChoosed(int indexToChoose) {
	IndexChoosed = indexToChoose;
}

bool I8080_WorkspaceManager::DrawPopupCreation(char* name, int name_size) {

	bool pressed = false;

	if (OpenedPopupCreation) {


		const ImGuiWindowFlags flagsWindow = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();

		ImVec2 size = ImGui::GetMainViewport()->WorkSize;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


		ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"Создание рабочего пространства              ").x, ImGui::GetFontSize()*8.f));

		if (ImGui::BeginPopupModal(u8"Создание рабочего пространства", &OpenedPopupCreation, flagsWindow))
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize());
			center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
			center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
			ImGui::GetCurrentWindow()->Pos = center;


			TextCenteredOnLine(u8"Название пространства", 0, 0);
			ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

			const float input_width = ImGui::CalcItemWidth();
			ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
			ImGui::InputText("1102", name, name_size, ImGuiInputTextFlags_NoLabel);
			


			ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

			pressed = ButtonCenteredOnLine(u8"Принять", 0.5f);

			if (ImGui::IsKeyPressed(ImGuiKey_Enter))
			{
				pressed = true;
			}

			if (pressed)
			{
				OpenedPopupCreation = false;
				//ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}

	return pressed;
}
bool I8080_WorkspaceManager::DrawPopupSetting(int index, char* name, int name_size) {
	bool pressed = false;

	if (OpenedPopupSetting) {


		const ImGuiWindowFlags flagsWindow = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();

		ImVec2 size = ImGui::GetMainViewport()->WorkSize;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


		ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"Изменение настроек рабочего пространства      ").x, ImGui::GetFontSize() * 10.f));

		if (ImGui::BeginPopupModal(u8"Изменение настроек рабочего пространства", &OpenedPopupSetting, flagsWindow))
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize());
			center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
			center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
			ImGui::GetCurrentWindow()->Pos = center;


			TextCenteredOnLine(u8"Название пространства", 0, 0);
			ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

			const float input_width = ImGui::CalcItemWidth();
			ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
			ImGui::InputText("1102", name, name_size, ImGuiInputTextFlags_NoLabel);



			ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

			pressed = ButtonCenteredOnLine(u8"Переименовать", 0.5f);

			ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

			if (ButtonCenteredOnLine(u8"Перезаписать", 0.5f)) {
				workspaces[index].Rewrite();
				OpenedPopupSetting = false;
			}


			if (ImGui::IsKeyPressed(ImGuiKey_Enter))
			{
				pressed = true;
			}

			if (pressed)
			{
				OpenedPopupSetting = false;
				//ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}

	return pressed;
}

bool I8080_WorkspaceManager::DrawEdit(ImGuiWindow* imgui_window, ImDrawList* draw_list, const int& index) {

	ImVec2 p = ImGui::GetCursorScreenPos();
	float size = ImGui::GetFontSize();
	float offset = size / 6.f;
	float offset_edge = size / 8.f;

	ImVec2 Edit_min = ImVec2(p.x, p.y);
	ImVec2 Edit_max = ImVec2(p.x + size, p.y + size);
	ImRect Edit_size = ImRect(Edit_min.x, Edit_min.y, Edit_max.x, Edit_max.y);


	ImGuiID id = imgui_window->GetID(std::string("workspace_edit_" + std::to_string(index)).c_str());
	ImGui::ItemAdd(Edit_size, id);

	bool hovered, held;
	bool pressed_Edit = ImGui::ButtonBehavior(Edit_size, id, &hovered, &held, 0);
	ImU32 coll = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

	ImGui::RenderFrame(Edit_min, Edit_max, coll, false);

	RenderCharacterInRect(ImGui::GetFont(), ImGui::GetWindowDrawList(), ImVec2(p.x + size / 5.f, p.y), ImVec2(size, size), ICON_FA_PEN, ColorForeground);

	p.x += size + offset_edge;
	ImGui::SetCursorScreenPos(p);
	return pressed_Edit;
}
bool I8080_WorkspaceManager::DrawDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const int& index) {
	ImVec2 p = ImGui::GetCursorScreenPos();
	float size = ImGui::GetFontSize();
	float offset = size / 6.f;
	float offset_edge = size / 8.f;

	ImVec2 Delete_min = ImVec2(p.x, p.y);
	ImVec2 Delete_max = ImVec2(p.x + size, p.y + size);
	ImRect Delete_size = ImRect(Delete_min.x, Delete_min.y, Delete_max.x, Delete_max.y);


	ImGuiID id = imgui_window->GetID(std::string("workspace_delete_" + std::to_string(index)).c_str());
	ImGui::ItemAdd(Delete_size, id);

	bool hovered, held;
	bool pressed_Delete = ImGui::ButtonBehavior(Delete_size, id, &hovered, &held, 0);
	ImU32 coll = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

	ImGui::RenderFrame(Delete_min, Delete_max, coll, false);

	RenderCharacterInRect(ImGui::GetFont(), ImGui::GetWindowDrawList(), ImVec2(p.x + size / 6.f, p.y), ImVec2(size, size), ICON_FA_TRASH, ColorForeground);

	p.x += size + 2.f * offset_edge;
	ImGui::SetCursorScreenPos(p);

	return pressed_Delete;
}
bool I8080_WorkspaceManager::DrawText(const int& index) {
	ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();

	ImVec2 p = ImGui::GetCursorScreenPos();
	float size = ImGui::GetFontSize();
	float offset = size / 6.f;
	float offset_edge = size / 8.f;

	

	ImVec2 Delete_min = ImVec2(p.x, p.y);
	ImVec2 Delete_max = ImVec2(p.x  + (ImGui::GetWindowWidth() - (p.x - (ImGui::GetWindowPos().x)) ) - size/4.f, p.y + size);
	ImRect Delete_size = ImRect(Delete_min.x, Delete_min.y, Delete_max.x, Delete_max.y);


	ImGuiID id = imgui_window->GetID(std::string("workspace_area_" + std::to_string(index)).c_str());
	ImGui::ItemAdd(Delete_size, id);

	bool hovered, held;
	bool pressed_Area = ImGui::ButtonBehavior(Delete_size, id, &hovered, &held, 0);
	ImU32 coll = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);


	if (held && Draging == false)
	{
		Draging = true;
		IndexDrag = index;
	}


	ImGui::RenderFrame(Delete_min, Delete_max, coll, false);

	p.x += 2.f * offset_edge;
	ImGui::SetCursorScreenPos(p);

	ImGui::Text(workspaces[index].GetName().c_str());

	return pressed_Area;
}
bool I8080_WorkspaceManager::DrawAddNewWorkspace(ImDrawList* draw_list) {
	ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();

	ImVec2 p = ImGui::GetCursorScreenPos();
	float size = ImGui::GetFontSize();
	float offset = size / 6.f;
	float offset_edge = size / 8.f;



	ImVec2 Add_min = ImVec2(p.x, p.y);
	ImVec2 Add_max = ImVec2(p.x + (ImGui::GetWindowWidth() - (p.x - (ImGui::GetWindowPos().x))) - size / 4.f, p.y + size);
	ImRect Add_size = ImRect(Add_min.x, Add_min.y, Add_max.x, Add_max.y);


	ImGuiID id = imgui_window->GetID(std::string("workspace_add_new").c_str());
	ImGui::ItemAdd(Add_size, id);

	bool hovered, held;
	bool pressed_Area = ImGui::ButtonBehavior(Add_size, id, &hovered, &held, 0);
	ImU32 coll = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);



	ImGui::RenderFrame(Add_min, Add_max, coll, false);

	p.x += 2.f * offset_edge;
	ImGui::SetCursorScreenPos(p);

	TextCenteredOnLine(u8"Добавить",0,0);
	//ImGui::Text("Добавить");

	return pressed_Area;
}


/// Into Combo Box
void I8080_WorkspaceManager::Draw() {
	static char NameForSettingWorkspace[120];
	static char NameForNewWorkspace[120];


	ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();
	ImDrawList* draw_list = ImGui::GetForegroundDrawList();

	for (int i = 0; i < workspaces.size(); i++){

		if (Draging && i == IndexDrag)
		{
			ImVec2 p = ImGui::GetCursorScreenPos();

			if (ImGui::GetMousePos().y < p.y - ImGui::GetFontSize() * 0.1f && i != 0){
				std::swap(workspaces[i], workspaces[i - 1]);
				IndexDrag--;
				//break;
			}

			if (ImGui::GetMousePos().y > p.y + ImGui::GetFontSize()*1.1f && i + 1 <= workspaces.size()-1) {
				std::swap(workspaces[i], workspaces[i + 1]);
				IndexDrag++;
				//break;
			}
		}

		if (DrawEdit(imgui_window, draw_list, i)) {

			IndexSetting = i;

			for (int i = 0; i < 120; i++)
				NameForSettingWorkspace[i] = 0;
			for (int i = 0; i < workspaces[IndexSetting].GetName().size(); i++)
				NameForSettingWorkspace[i] = workspaces[IndexSetting].GetName()[i];



			ImGui::OpenPopup(u8"Изменение настроек рабочего пространства");
			OpenedPopupSetting = true;

		}
		if (DrawDelete(imgui_window, draw_list, i)) {
			workspaces.erase(workspaces.begin() + i);
			IndexChoosed = 200000;
		}
		if (DrawText(i)) {
			IndexChoosed = i;
			NeedLoadIni = true;
		}




		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) == false)
		{
			Draging = false;
		}

		//ImGui::Dummy(ImVec2(ImGui::GetFontSize(), ImGui::GetFontSize()));
	}

	if (DrawAddNewWorkspace(draw_list)) {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "true" << std::endl;
#endif
		OpenedPopupCreation = true;
		ImGui::OpenPopup(u8"Создание рабочего пространства");
	}



	if (DrawPopupCreation(NameForNewWorkspace, 120)) {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Name for new workspace: [" << NameForNewWorkspace << "]\n";
#endif
		AddWorkspace(NameForNewWorkspace,false);


		for (int i = 0; i < 60; i++)
		{
			NameForNewWorkspace[i] = 0;
		}
	}




	if (DrawPopupSetting(IndexSetting, NameForSettingWorkspace, 120)) {
		std::string result = "";
		for (int i = 0; i < 120; i++)
		{
			if (NameForSettingWorkspace[i] == 0){
				break;
			}
			result += NameForSettingWorkspace[i];
		}
		workspaces[IndexSetting].SetName(result);
	}

}



void I8080_WorkspaceManager::Update() {
	if (NeedLoadIni){
		LoadChoosed();
		NeedLoadIni = false;
	}
}
void I8080_WorkspaceManager::SetNeedLoad() {
	NeedLoadIni = true;
}
void I8080_WorkspaceManager::LoadNext() {
	IndexChoosed = (IndexChoosed + 1) % workspaces.size();
	LoadChoosed();
}

void I8080_WorkspaceManager::LoadChoosed() {
	if (!workspaces.empty())
	{
		if (IndexChoosed <0 || IndexChoosed > workspaces.size() - 1) {
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "Index workspaces out of array\n";
#endif
		} else {
			workspaces[IndexChoosed].SetAsCurrent();
		}
	}
	else {
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "array workspaces empty\n";
#endif
	}
}
	