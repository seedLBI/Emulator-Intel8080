#include "Widget.MnemoCodeViewer.h"



Widget_MnemocodeViewer::Widget_MnemocodeViewer(I8080* processor, TranslatorOutput* translator) :
	I8080_Widget(u8"Мнемо код"),
	ISettingObject(u8"Просмотр кода",u8"Общие"),
	IThemeLoadable(u8"Мнемо код")
{
	this->processor = processor;
	this->translator = translator;

	IThemeLoadable::InitListWord({ u8"Посещённая ячейка", u8"Текущая ячейка (PC)", u8"Ячейка останова", u8"Указатель на память (HL)"});

}
Widget_MnemocodeViewer::~Widget_MnemocodeViewer() {

}

std::vector<NamedColor> Widget_MnemocodeViewer::GetDefaultLightColors() {
	return {
		{u8"Посещённая ячейка",			ImColor(217,168,217,64)},
		{u8"Текущая ячейка (PC)",		ImColor(132,208,130,64)},
		{u8"Ячейка останова",			ImColor(203,161,61,115)},
		{u8"Указатель на память (HL)",	ImColor(234,220,157,77)}
	};
}
std::vector<NamedColor> Widget_MnemocodeViewer::GetDefaultDarkColors() {
	return {
		{u8"Посещённая ячейка",			ImVec4(0.9f, 0.2f, 0.9f, 0.25f)},
		{u8"Текущая ячейка (PC)",		ImVec4(0.3f, 0.9f, 0.3f, 0.25f)},
		{u8"Ячейка останова",			ImVec4(0.9f, 0.9f, 0.3f, 0.45f)},
		{u8"Указатель на память (HL)",	ImVec4(0.1f, 0.1f, 1.0f, 0.3f)}
	};
}
void Widget_MnemocodeViewer::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {

		if (object_colors.colors[i].nameColor == u8"Посещённая ячейка")
			color_Visited = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"Текущая ячейка (PC)")
			color_PC = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"Ячейка останова")
			color_Breakpoint = object_colors.colors[i].color;
		else if (object_colors.colors[i].nameColor == u8"Указатель на память (HL)")
			color_HL = object_colors.colors[i].color;

	}
}

void Widget_MnemocodeViewer::Draw() {
	if (GetFlagShow() == false)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	float prev_cellPadding = style.CellPadding.y;
	style.CellPadding.y = 1;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	//pos_follow


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {


		ImGuiTableFlags flags;

		if (flag_EnableAlwaysFocus)
			pos_follow = processor->GetProgrammCounter();

		flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollY;



		ImVec2 outer_size = ImVec2(0.0f, 20 * 8);
		if (ImGui::BeginTable("MnemoCode", 4, flags)) {

			ImGui::TableSetupColumn(u8"Адрес", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"Код", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"Строка кода", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupColumn(u8"Маркер", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1);
			ImGui::TableSetupScrollFreeze(1, 1);
			ImGui::TableSetupScrollFreeze(2, 1);
			ImGui::TableSetupScrollFreeze(3, 1);

			ImGui::TableHeadersRow();

			ImGuiListClipper clipper;

			clipper.Begin(SIZE_MEMORY);
			while (clipper.Step()) {
				for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++) {
					ImGui::TableNextRow();

					if (pos_follow != -1 && row != 0) {

						int count = abs(clipper.DisplayStart - clipper.DisplayEnd);
						int start = pos_follow - (count / 2) + 2;

						pos_follow -= count / 2 - 2;
						if (start < 0) {
							start = 0;
						}

						double koef = ImGui::GetFontSize() + 2;

						ImGui::SetScrollY((float)pos_follow * (float)koef);


						pos_follow = -1;
					}



					if (processor->GetVisetedMemory()[row])
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, color_Visited);

					if (processor->GetAdressHL() == row)
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, color_HL);

					if (processor->GetProgrammCounter() == row)
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, color_PC);

					if (processor->GetBreakpointsInMemory()[row])
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, color_Breakpoint);
					



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
void Widget_MnemocodeViewer::Update() {
	UpdateActive();
}
void Widget_MnemocodeViewer::FollowCursor(int position) {
	pos_follow = position;
}

void Widget_MnemocodeViewer::FollowCursorPC() {
	pos_follow = processor->GetProgrammCounter();
}

nlohmann::json Widget_MnemocodeViewer::Save() {
	return SaveDefaultParameters();
}

void Widget_MnemocodeViewer::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}

void Widget_MnemocodeViewer::ToggleFlagAlwaysFocus() {
	flag_EnableAlwaysFocus = !flag_EnableAlwaysFocus;
}
bool Widget_MnemocodeViewer::GetFlagAlwaysFocus() {
	return flag_EnableAlwaysFocus;
}

void Widget_MnemocodeViewer::DrawMainMenu() {
	ImGui::Checkbox("", &flag_EnableAlwaysFocus);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(u8"Отключает возможность прокрутки для окна Мнемокод\nпостоянно устанавливая позицию так чтобы\nтекущая выполняемая команда была в середине.");
}
void Widget_MnemocodeViewer::DrawSetting() {
	ISettingObject::DrawBegin();

	if (ImGui::RadioButton(u8"Постоянный фокус на регистр PC", flag_EnableAlwaysFocus))
		ToggleFlagAlwaysFocus();

	ImGui::SameLine();
	
	MyHelpMarker(u8"Отключает возможность прокрутки для окна Мнемокод\nпостоянно устанавливая позицию так чтобы\nтекущая выполняемая команда была в середине.");

}
nlohmann::json Widget_MnemocodeViewer::SaveSetting() {
	nlohmann::json result;

	result["flag_EnableAlwaysFocus"] = flag_EnableAlwaysFocus;

	return result;
}
void Widget_MnemocodeViewer::LoadSetting(const nlohmann::json& Data) {

	if (Data.contains("flag_EnableAlwaysFocus")) {
		flag_EnableAlwaysFocus = Data["flag_EnableAlwaysFocus"].get<bool>();
	}
}