#include "Setting.h"


Setting::Setting(FontManager* font, WindowManager* window, NotificationManager* notification, EmulationThread* emulation) : SaveSystem("Setting") {
	this->font = font;
	this->window = window;
	this->notification = notification;
	this->emulation = emulation;
}

Setting::~Setting() {

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
	ImGui::SetNextWindowSize(ImVec2(size.x / 2.f, size.y / 2.f));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::BeginPopupModal(u8"Настройки", &Popup_Open, flagsWindow)) {

		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 avail_size = ImGui::GetContentRegionAvail();

		pos.y += 7.f;
		float x_without_padding = pos.x;

		ImGui::Columns(2, NULL, false);

		static int selected_setting_type = 0;
		const char* names_setting_types[4] = { u8" Изображение",u8" Менеджер цветов",u8" Управление",u8" Эмуляция" };

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 17.0f));

		ImGui::SetColumnWidth(0, ImGui::CalcTextSize(names_setting_types[0]).x * 1.5f);
		ImGui::SetCursorScreenPos(pos);

		for (int i = 0; i < 4; i++) {

			if (ImGui::Selectable(names_setting_types[i], selected_setting_type == i, ImGuiSelectableFlags_DontClosePopups))
				selected_setting_type = i;
			ImGui::SetCursorScreenPos(ImVec2(x_without_padding, ImGui::GetCursorScreenPos().y));
		}
		ImGui::PopStyleVar();
		ImGui::NextColumn();


		ImVec2 avail_size_temp = ImGui::GetContentRegionAvail();
		ImVec2 pos_temp = ImGui::GetCursorScreenPos();

		ImGui::SetCursorScreenPos(ImVec2(pos_temp.x, pos_temp.y + 10));
		string Selected = "";

		switch (selected_setting_type) {
		case 0:
			font->Draw();
			window->Draw();

			ImGui::SeparatorText(u8"Уведомления");

			if (ImGui::RadioButton(u8"Показывать", notification->GetFlag_Enable())) {
				notification->ToggleFlag_Enabled();
			}

			ImGui::SeparatorText(u8"Эмуляция");



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


			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}






		string WaterMark = "seedLBI 2024";
		ImGui::SetCursorScreenPos(ImVec2((pos.x + avail_size.x) - ImGui::CalcTextSize(WaterMark.c_str()).x - 2.f, (pos.y + avail_size.y) - ImGui::CalcTextSize(WaterMark.c_str()).y - 7.f - 2.f));
		ImGui::TextColored(ImVec4(1, 1, 1, 0.2), WaterMark.c_str());

		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

}

void Setting::Open() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "Open setting" << std::endl;
#endif

	Popup_Open = true;
	ImGui::OpenPopup(u8"Настройки");
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
		}

	}


}


