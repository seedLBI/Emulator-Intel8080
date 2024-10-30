#include "Setting.h"


Setting::Setting(FontManager* font, WindowManager* window, I8080_WorkspaceManager* WorkspaceManager, NotificationManager* notification, EmulationThread* emulation, KeyCombinationHandler* keyCombinationHandler, ProjectManager* projectManager) : SaveSystem("Setting") {
	this->font = font;
	this->window = window;
	this->notification = notification;
	this->emulation = emulation;
	this->keyCombinationHandler = keyCombinationHandler;
	this->projectManager = projectManager;
	this->WorkspaceManager = WorkspaceManager;
}

Setting::~Setting() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Setting::~Setting()\n";
#endif // !WITH_DEBUG_OUTPUT
}


void Setting::Draw() {
	if (Popup_Open == false)
		return;


	ImGui::OpenPopup(u8"Настройки");

	static const ImGuiWindowFlags flagsWindow = 
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar;

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;
	ImGui::SetNextWindowSize(ImVec2(size.x / 1.5f, size.y / 1.5f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginPopupModal(u8"Настройки", &Popup_Open, flagsWindow)) {


		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImVec2 pos = ImGui::GetCursorScreenPos();


		static int selected_setting_type = 0;
		const char* names_setting_types[2] = { u8"Общие",u8"Управление" };


		ImGui::BeginChild("left pane", ImVec2(ImGui::CalcTextSize(u8"  Управление  ").x, 0));

		for (int i = 0; i < 2; i++) {
			if (ImGui::Selectable(names_setting_types[i], selected_setting_type == i, ImGuiSelectableFlags_Centered, ImVec2(0, ImGui::GetTextLineHeight() * 2.f)))
				selected_setting_type = i;
		}



		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("right pane");

		switch (selected_setting_type) {
		case 0:
			font->Draw();
			window->Draw();
			DrawNotificationSetting();
			DrawEmulationSetting();
			projectManager->DrawSetting();
			WorkspaceManager->DrawSetting();

			ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight()));

			break;
		case 1:
			keyCombinationHandler->DrawSetting();
			break;
		default:
			break;
		}


		ImGui::EndChild();







		/*
		string WaterMark = "seedLBI 2024";
		ImGui::SetCursorScreenPos(ImVec2((pos.x + avail_size.x) - ImGui::CalcTextSize(WaterMark.c_str()).x - 2.f, (pos.y + avail_size.y) - ImGui::CalcTextSize(WaterMark.c_str()).y - 7.f - 2.f));
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2), WaterMark.c_str());
		*/


		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

}


void Setting::DrawNotificationSetting() {

	ImGui::SeparatorText(u8"Уведомления");

	if (ImGui::RadioButton(u8"Показывать", notification->GetFlag_Enable())) {
		notification->ToggleFlag_Enabled();
	}
}
void Setting::DrawEmulationSetting() {
	ImGui::SeparatorText(u8"Эмуляция");

	string Selected = "";

	if (emulation->GetSpeedMode() == SpeedMode::Infinity)
		Selected = u8"Неограниченная";
	if (emulation->GetSpeedMode() == SpeedMode::Intel8080)
		Selected = u8"Intel8080 (3 Мгц)";
	if (emulation->GetSpeedMode() == SpeedMode::Intel8085)
		Selected = u8"Intel8085 (6 Мгц)";

	if (ImGui::BeginCombo(u8"Скорость", Selected.c_str(), ImGuiComboFlags_WidthFitPreview)) {


		bool selected = Selected == u8"Неограниченная";

		if (ImGui::Selectable(u8"Неограниченная", &selected)) {
			emulation->SetSpeedMode(SpeedMode::Infinity);
		}
		if (selected)
			ImGui::SetItemDefaultFocus();

		selected = Selected == u8"Intel8080 (3 Мгц)";

		if (ImGui::Selectable(u8"Intel8080 (3 Мгц)", &selected)) {
			emulation->SetSpeedMode(SpeedMode::Intel8080);
		}
		if (selected)
			ImGui::SetItemDefaultFocus();

		selected = Selected == u8"Intel8085 (6 Мгц)";

		if (ImGui::Selectable(u8"Intel8085 (6 Мгц)", &selected)) {
			emulation->SetSpeedMode(SpeedMode::Intel8085);
		}
		if (selected)
			ImGui::SetItemDefaultFocus();


		ImGui::EndCombo();
	}
}



void Setting::Open() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Open setting" << std::endl;
#endif

	Popup_Open = true;
}


void Setting::Toggle() {
	Popup_Open = !Popup_Open;
}


bool Setting::isOpen() {
	return Popup_Open;
}

std::string Setting::Save() {

	std::string data = "";
	data += font->Save();
	data += window->Save();
	data += notification->Save();
	data += emulation->Save();
	data += keyCombinationHandler->Save();
	data += projectManager->Save();

	std::string output = MakeBegin(GetCountLines(data));

	output += data;


	return output;

}

void Setting::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);


	std::vector<std::string> Lines = split(Data, "\n");

	int index_line = -1;
	while (index_line != Lines.size() - 1) {
		index_line++;
		string line = Lines[index_line];

		auto begin = line.find_first_of('[') + 1;
		auto end = line.find_first_of(']');

		std::string FirstArgument = line.substr(begin, end - begin);
#ifdef WITH_DEBUG_OUTPUT
		std::cout << FirstArgument << std::endl;
#endif
		if (FirstArgument == "BEGIN") {

			begin = line.find_last_of('[') + 1;
			end = line.find_last_of(']');

			std::string Name_Object = line.substr(begin, end - begin);

			begin = line.find_last_of('(') + 1;
			end = line.find_last_of(')');
			int CountLines = stoi(line.substr(begin, end - begin));

			std::string Data_save_object = "";


			for (int i = 0; i < CountLines; i++) {
				index_line++;
				line = Lines[index_line];

				if (i == CountLines-1)
					Data_save_object += line;
				else
					Data_save_object += line + '\n';
			}

			if (Name_Object == font->GetName()){
				font->Load(Data_save_object);
			}
			else if (Name_Object == window->GetName()){
				window->Load(Data_save_object);
			}
			else if (Name_Object == emulation->GetName()) {
				emulation->Load(Data_save_object);
			}
			else if (Name_Object == notification->GetName()) {
				notification->Load(Data_save_object);
			}
			else if (Name_Object == projectManager->GetName()) {
				projectManager->Load(Data_save_object);
			}
			else if (Name_Object == keyCombinationHandler->GetName()) {
				keyCombinationHandler->Load(Data_save_object);
			}
		}

	}


}


