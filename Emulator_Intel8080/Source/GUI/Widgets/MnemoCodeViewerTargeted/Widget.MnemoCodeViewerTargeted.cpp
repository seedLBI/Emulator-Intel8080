#include "Widget.MnemoCodeViewerTargeted.h"


Widget_MnemocodeViewerTargeted::Widget_MnemocodeViewerTargeted(I8080* processor, TranslatorOutput* translator) :
	I8080_Widget(u8"����� ��� (����������)"),
	IThemeLoadable(u8"����� ��� (����������)")
{
	this->processor = processor;
	this->translator = translator;

	IThemeLoadable::InitListWord({ u8"����" });

}

Widget_MnemocodeViewerTargeted::~Widget_MnemocodeViewerTargeted() {

}

std::vector<NamedColor> Widget_MnemocodeViewerTargeted::GetDefaultLightColors() {
	return {
		{u8"����", ImColor(234,112,112,115)}
	};
}
std::vector<NamedColor> Widget_MnemocodeViewerTargeted::GetDefaultDarkColors() {
	return {
		{u8"����", ImVec4(1.0f, 0.3f, 0.3f, 0.45f)}
	};
}
void Widget_MnemocodeViewerTargeted::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {

		if (object_colors.colors[i].nameColor == u8"����")
			color_target = object_colors.colors[i].color;

	}
}

void Widget_MnemocodeViewerTargeted::Draw() {
	if (GetFlagShow() == false)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	int prev_cellPadding = style.CellPadding.y;
	style.CellPadding.y = 1;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {


		ImGuiTableFlags flags;

		flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollY;



		ImVec2 outer_size = ImVec2(0.0f, 20 * 8);


		ImGuiListClipper clipper;

		if (ImGui::RadioButton(u8"PC", target == TargetType::PC))
			target = TargetType::PC;
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"SP", target == TargetType::SP))
			target = TargetType::SP;
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"HL", target == TargetType::HL))
			target = TargetType::HL;
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"DE", target == TargetType::DE)) 
			target = TargetType::DE;
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"BC", target == TargetType::BC))
			target = TargetType::BC;

		if (ImGui::BeginTable("MnemoCode", 4, flags)) {

			ImGui::TableSetupColumn(u8"�����", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"���", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"������ ����", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"������", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1);
			ImGui::TableSetupScrollFreeze(1, 1);
			ImGui::TableSetupScrollFreeze(2, 1);
			ImGui::TableSetupScrollFreeze(3, 1);

			ImGui::TableHeadersRow();



			clipper.Begin(SIZE_MEMORY);
			while (clipper.Step()) {
				for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++) {
					ImGui::TableNextRow();


					int pos_follow = 0;

					switch (target)
					{
					case Widget_MnemocodeViewerTargeted::PC:
						pos_follow = processor->GetProgrammCounter();
						break;
					case Widget_MnemocodeViewerTargeted::SP:
						pos_follow = processor->GetSP();
						break;
					case Widget_MnemocodeViewerTargeted::HL:
						pos_follow = processor->GetAdressHL();
						break;
					case Widget_MnemocodeViewerTargeted::DE:
						pos_follow = processor->GetDE();
						break;
					case Widget_MnemocodeViewerTargeted::BC:
						pos_follow = processor->GetBC();
						break;
					default:
						break;
					}


					if (row != 0) {

						int count = abs(clipper.DisplayStart - clipper.DisplayEnd) - 6;

						if (count < 0)
							count = 0;

						double koef = ImGui::GetFontSize() + 2;

						ImGui::SetScrollY((pos_follow - count / 2 - 2) * koef);
					}



					if (pos_follow == row)
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, color_target);




					bool finded = false;
					ImGui::TableSetColumnIndex(0);
					bool pressed = false;
					ImGui::Selectable(to_hex_string((uint16_t)row).c_str(), &pressed, ImGuiSelectableFlags_SpanAllColumns);
					if (pressed) {
						processor->SetProgrammCounter(row);
					}
					if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
						processor->ToggleBreakPointPosition(row);
					}

					for (int i = 0; i < translator->Opcodes.size(); i++) {
						if (translator->Opcodes[i].adress_h == row / 256 && translator->Opcodes[i].adress_l == row % 256) {
							ImGui::TableSetColumnIndex(1);
							ImGui::Text(to_hex_string(processor->GetMemory()[row]).c_str(), 1, row);
							ImGui::TableSetColumnIndex(2);
							//ImGui::TextColored( Colors_TypesCommands[GetTypeCommand(translator->Opcodes[i].command)], translator->Opcodes[i].command.c_str(), 2, row);

							std::string instruction = translator->Opcodes[i].command.substr(0, translator->Opcodes[i].command.find_first_of(' ') == 0 ? std::string::npos : translator->Opcodes[i].command.find_first_of(' '));
							ImVec4 col = Singleton_I8080_HighlighterInstruction::Instance().GetColorFromName(instruction);
							ImGui::TextColored(col, translator->Opcodes[i].command.c_str(), 2, row);

							ImGui::TableSetColumnIndex(3);
							ImGui::Text(translator->Opcodes[i].marker.c_str(), 3, row);
							finded = true;
							break;
						}

					}

					if (!finded) {
						ImGui::TableSetColumnIndex(1);
						ImGui::Text(to_hex_string(processor->GetMemory()[row]).c_str(), 1, row);
						ImGui::TableSetColumnIndex(2);
						ImGui::Text("NOP", 2, row);
					}
				}
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}
	ImGui::PopStyleVar();

	style.CellPadding.y = prev_cellPadding;
}
void Widget_MnemocodeViewerTargeted::Update() {
	UpdateActive();
}


std::string Widget_MnemocodeViewerTargeted::TargetType_to_str(const TargetType& _target) {
	switch (_target){
	case TargetType::PC:
		return u8"PC";
		break;
	case TargetType::SP:
		return u8"SP";
		break;
	case TargetType::HL:
		return u8"HL";
		break;
	case TargetType::DE:
		return u8"DE";
		break;
	case TargetType::BC:
		return u8"BC";
		break;
	default:
		break;
	}
}

Widget_MnemocodeViewerTargeted::TargetType Widget_MnemocodeViewerTargeted::str_to_TargetType(const std::string& str_target) {
	if (str_target == u8"PC")
		return TargetType::PC;
	else if (str_target == u8"SP")
		return TargetType::SP;
	else if (str_target == u8"HL")
		return TargetType::HL;
	else if (str_target == u8"DE")
		return TargetType::DE;
	else if (str_target == u8"BC")
		return TargetType::BC;
	else
		return TargetType::PC;
}

nlohmann::json Widget_MnemocodeViewerTargeted::Save() {

	nlohmann::json result = SaveDefaultParameters();
	result["Target"] = TargetType_to_str(target);
	return result;
}

void Widget_MnemocodeViewerTargeted::Load(const nlohmann::json& Data) {

	ReadDefaultParameters(Data);

	if (Data.contains("Target")) {
		target = str_to_TargetType(Data["Target"].get<std::string>());
	}

}
