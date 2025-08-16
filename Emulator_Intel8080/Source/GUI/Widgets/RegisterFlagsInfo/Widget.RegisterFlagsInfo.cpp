#include "Widget.RegisterFlagsInfo.h"


Widget_RegisterFlagsInfo::Widget_RegisterFlagsInfo(I8080* processor) :I8080_Widget(u8"�������� � �����"),IThemeLoadable(u8"�������� ��������� � ������") {
	this->processor = processor;
	processor->InitPointer2State(current_state);

	IThemeLoadable::InitListWord({ u8"���������" });
}
Widget_RegisterFlagsInfo::~Widget_RegisterFlagsInfo() {

}


void Widget_RegisterFlagsInfo::Draw() {
	if (GetFlagShow() == false)
		return;

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::SetWindowFontScale(1.1f);
		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders;
		if (ImGui::BeginTable("table_register_and_flags", 4, flags))
		{
			ImGui::TableSetupColumn(u8"��������", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("Hex", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("Bin", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn("Dec", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();


			const std::string name_flags[5] = { "Zero","Carry","Sign","Parity","Aux. Carry"};
			unsigned int values_flag[5] = {
				*current_state.Zero,
				*current_state.Carry,
				*current_state.Sign,
				*current_state.Parity,
				*current_state.AuxiliaryCarry };
			unsigned int values_last_flag[5] = {
				prev_state.Zero,
				prev_state.Carry,
				prev_state.Sign,
				prev_state.Parity,
				prev_state.AuxiliaryCarry};

			const std::string name_registers[9] = { "A","B","C","D","E","H","L","M","F" };
			unsigned int values[9] = {
				*current_state.A,
				*current_state.B,
				*current_state.C,
				*current_state.D,
				*current_state.E,
				*current_state.H,
				*current_state.L,
				processor->GetMemory()[*current_state.H * 256 + *current_state.L],
				(0x02 + *current_state.Carry + *current_state.Parity * 4 + *current_state.AuxiliaryCarry * 16 + *current_state.Zero * 64 + *current_state.Sign * 128)
			};
			unsigned int values_last[9] = {
				prev_state.A,
				prev_state.B,
				prev_state.C,
				prev_state.D,
				prev_state.E,
				prev_state.H,
				prev_state.L,
				processor->GetMemory()[prev_state.H * 256 + prev_state.L],
				(0x02 + prev_state.Carry + prev_state.Parity * 4 + prev_state.AuxiliaryCarry * 16 + prev_state.Zero * 64 + prev_state.Sign * 128)
			};



			for (int i = 0; i < 9; i++) {
				ImGui::TableNextRow();

				if (values_last[i] != values[i])
				{
					ImU32 row_bg_color = ImGui::GetColorU32(color_Changed); // Flat or Gradient?
					ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, row_bg_color);
				}

				ImGui::TableSetColumnIndex(0);
				ImGui::Text(std::string(name_registers[i] + u8" �������").c_str(), 0, i);
				ImGui::TableSetColumnIndex(1);
				TextCenteredOnLine(to_hex_string((uint8_t)values[i]).c_str(), 1, i);
				ImGui::TableSetColumnIndex(2);
				TextCenteredOnLine(to_bin_string((uint8_t)values[i]).c_str(), 2, i);
				ImGui::TableSetColumnIndex(3);
				TextCenteredOnLine(std::to_string(values[i]).c_str(), 3, i);
			}

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(u8"PC", 0, 8);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine(to_hex_string(*current_state.PC).c_str(), 1, 8);


			ImGui::TableSetColumnIndex(3);
			TextCenteredOnLine(std::to_string(*current_state.PC).c_str(), 1, 8);


			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(u8"SP", 0, 9);
			ImGui::TableSetColumnIndex(1);
			TextCenteredOnLine(to_hex_string(*current_state.SP).c_str(), 1, 9);


			ImGui::TableSetColumnIndex(3);
			TextCenteredOnLine(std::to_string(*current_state.SP).c_str(), 1, 9);


			for (int i = 0; i < 5; i++) {
				ImGui::TableNextRow();

				if (values_flag[i] != values_last_flag[i]){
					ImU32 row_bg_color = ImGui::GetColorU32(color_Changed); // Flat or Gradient?
					ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, row_bg_color);
				}

				ImGui::TableSetColumnIndex(0);
				ImGui::Text(std::string(name_flags[i] + u8" ����").c_str(), 0, i + 10);
				ImGui::TableSetColumnIndex(1);
				TextCenteredOnLine(std::string(values_flag[i] == 0 ? "False" : "True").c_str(), 1, i + 10);
			}

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);



			ImGui::EndTable();
		}


		ImGui::End();
	}

}
void Widget_RegisterFlagsInfo::Update() {
	UpdateActive();
}
void Widget_RegisterFlagsInfo::InitLastState() {
	prev_state.Init(current_state);
}

nlohmann::json Widget_RegisterFlagsInfo::Save() {
	return SaveDefaultParameters();
}

void Widget_RegisterFlagsInfo::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}



void Widget_RegisterFlagsInfo::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"���������")
			color_Changed = object_colors.colors[i].color;
	}
}

std::vector<NamedColor> Widget_RegisterFlagsInfo::GetDefaultLightColors() {
	return {
		{ u8"���������",ImColor(255,180,69,179) }
	};
}
std::vector<NamedColor> Widget_RegisterFlagsInfo::GetDefaultDarkColors() {
	return { 
		{ u8"���������",ImVec4(1.f, 0.7f, 0.3f, 0.7f) }
	};
}