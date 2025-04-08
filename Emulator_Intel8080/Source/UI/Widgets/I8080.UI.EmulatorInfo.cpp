#include "I8080.UI.EmulatorInfo.h"


Widget_EmulatorInfo::Widget_EmulatorInfo(I8080* processor) :I8080_Widget(u8"Быстродействие") {
	this->processor = processor;
	processor->InitPointer2State(current_state);
}
Widget_EmulatorInfo::~Widget_EmulatorInfo() {

}


std::string Widget_EmulatorInfo::ConvertToSI(const uint64_t& value, const char* unit) {
	int Kilo = value / (uint64_t)1'000;
	int Mega = value / (uint64_t)1'000'000;
	int Giga = value / (uint64_t)1'000'000'000;
	int Tera = value / (uint64_t)1'000'000'000'000;

	std::string output;
	std::string AfterDot;

	if (Tera > 0) {
		output = std::to_string(Tera);
		AfterDot = std::to_string(value).substr(output.size());
		if (AfterDot.size() > 3)
			AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
		return output + "," + AfterDot + u8" Т" + unit;
	}
	if (Giga > 0) {
		output = std::to_string(Giga);
		AfterDot = std::to_string(value).substr(output.size());
		if (AfterDot.size() > 3)
			AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
		return output + "," + AfterDot + u8" Г" + unit;
	}
	if (Mega > 0) {
		output = std::to_string(Mega);
		AfterDot = std::to_string(value).substr(output.size());
		if (AfterDot.size() > 3)
			AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
		return output + "," + AfterDot + u8" М" + unit;
	}
	if (Kilo > 0) {
		output = std::to_string(Kilo);
		AfterDot = std::to_string(value).substr(output.size());
		if (AfterDot.size() > 3)
			AfterDot.erase(AfterDot.begin() + 3, AfterDot.end());
		return output + "," + AfterDot + u8" К" + unit;
	}




	return std::to_string(value) + u8" " + unit;

}


void Widget_EmulatorInfo::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::SetWindowFontScale(1.1f);
		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders;
		if (ImGui::BeginTable("table_speed", 2, flags))
		{
			ImGui::TableSetupColumn(u8"Название", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"Значение", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();

			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text(string(u8"Кол-во\nтактов").c_str(), 0, 14);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine(to_string(*current_state.CountTicks).c_str(), 1, 0, 0.5f, true);

			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text(string(u8"Кол-во\nинструкций").c_str(), 0, 1);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine(to_string(*current_state.CountInstruction).c_str(), 1, 1, 0.5f, true);


			ImGui::TableNextRow();


			static float LastTimeOneSecond = 0.f;

			static uint64_t LastCountTicksInSeconds = 0;
			static uint64_t LastCountTicksInSeconds_temp = 0;

			static uint64_t LastCountInstructionInSeconds = 0;
			static uint64_t LastCountInstructionInSeconds_temp = 0;


			if (glfwGetTime() - LastTimeOneSecond > 1.f) {

				LastTimeOneSecond = glfwGetTime();


				LastCountInstructionInSeconds = *current_state.CountInstruction - LastCountInstructionInSeconds_temp;
				LastCountInstructionInSeconds_temp = *current_state.CountInstruction;

				LastCountTicksInSeconds = *current_state.CountTicks - LastCountTicksInSeconds_temp;
				LastCountTicksInSeconds_temp = *current_state.CountTicks;
			}




			ImGui::TableSetColumnIndex(0);
			ImGui::Text(string(u8"Скорость\nтактов").c_str(), 0, 2);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine(ConvertToSI(LastCountTicksInSeconds,u8"Гц").c_str(), 1, 2, 0.5f, false);

			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text(string(u8"Скорость\nинструкций").c_str(), 0, 2);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine((std::to_string(LastCountInstructionInSeconds)).c_str(), 1, 2, 0.5f, false);



			ImGui::EndTable();
		}


		ImGui::End();
	}

}
void Widget_EmulatorInfo::Update() {
	UpdateActive();
}

std::string Widget_EmulatorInfo::Save() {
	std::string output = "";
	output += MakeBegin(2);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(std::string("Flag_Active"), std::to_string(WindowIsVisiable()));
	return output;
}

void Widget_EmulatorInfo::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else if (name_arg == "Flag_Active") {
			if (stoi(value_arg) == 1)
				SetActive();
		}
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}