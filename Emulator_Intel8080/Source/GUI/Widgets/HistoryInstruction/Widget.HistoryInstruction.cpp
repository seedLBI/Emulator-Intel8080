#include "Widget.HistoryInstruction.h"

Widget_HistoryInstruction::Widget_HistoryInstruction(I8080* processor, EmulationThread* emulationThread, Caretaker_Momento* processor_CaretakerMomento) : I8080_Widget(u8"История выполнения") {
	this->processor = processor;
	this->emulationThread = emulationThread;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
}


Widget_HistoryInstruction::~Widget_HistoryInstruction() {

}

void Widget_HistoryInstruction::Draw() {

	if (GetFlagShow() == false)
		return;





	ImGuiStyle& style = ImGui::GetStyle();
	style.CellPadding.y = 1;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {

		if (emulationThread->GetControlMode() != ControlMode::Continous && processor->isHistoryModeEnabled()){

			auto data = processor_CaretakerMomento->GetHistory();

			const ImGuiTableFlags flags = ImGuiTableFlags_RowBg |
				ImGuiTableFlags_BordersOuter |
				ImGuiTableFlags_BordersV |
				ImGuiTableFlags_Reorderable |
				ImGuiTableFlags_Hideable |
				ImGuiTableFlags_NoBordersInBody |
				ImGuiTableFlags_ScrollY;


			if (ImGui::BeginTable(u8"HistoryInstructionsTable",3, flags)) {


				ImGui::TableSetupColumn(u8"Номер", ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupColumn(u8"Опкод", ImGuiTableColumnFlags_WidthFixed);
				ImGui::TableSetupColumn(u8"Мнемокод", ImGuiTableColumnFlags_WidthStretch);

				ImGui::TableSetupScrollFreeze(0, 1);
				ImGui::TableSetupScrollFreeze(1, 1);
				ImGui::TableSetupScrollFreeze(2, 1);
				ImGui::TableHeadersRow();

				ImGuiListClipper clipper;
				clipper.Begin((int)data.size());

				while (clipper.Step())
				{
					for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++) {
						ImGui::TableNextRow();

						ImGui::TableSetColumnIndex(0);

						if (ImGui::Selectable(std::to_string(row).c_str(), false, ImGuiSelectableFlags_SpanAllColumns)) {
							for (int i = 0; i < row + 1; i++)
								processor_CaretakerMomento->Undo();
						}

						ImGui::TableSetColumnIndex(1);

						ImGui::Text(data[row].first.c_str());

						ImGui::TableSetColumnIndex(2);

						ImGui::Text(data[row].second.c_str());

					}
				}

				ImGui::EndTable();
			}

		}
		else {

			ImGuiStyle& style = ImGui::GetStyle();
			auto contentSize = ImGui::GetWindowSize();
			auto drawList = ImGui::GetWindowDrawList();
			auto cursorScreenPos = ImGui::GetWindowPos();

			const float scrollbarsSize = style.ScrollbarSize + 2.f;

			const ImVec2 LeftUpperCorner = { cursorScreenPos.x, cursorScreenPos.y };
			const ImVec2 RightUpperCorner = { cursorScreenPos.x + contentSize.x - scrollbarsSize, cursorScreenPos.y };
			const ImVec2 LeftDownCorner = { cursorScreenPos.x, cursorScreenPos.y + contentSize.y - scrollbarsSize };
			const ImVec2 RightDownCorner = { cursorScreenPos.x + contentSize.x - scrollbarsSize,cursorScreenPos.y + contentSize.y - scrollbarsSize };

			const ImVec2 Center = { cursorScreenPos.x + contentSize.x / 2.f, cursorScreenPos.y + contentSize.y / 2.f };

			const char* TextDisableInput;
			if (processor->isHistoryModeEnabled() == false){
				TextDisableInput =
					u8"     Выключен режим истории.\n"
				      "(это можно изменить в настройках)\n"
					  "               или";
			}
			else{
				TextDisableInput =
					u8"    Программа эмулируется...  \n"
					  "Останови эмуляцию для просмотра.";
			}



			ImVec2 SizeText = ImGui::CalcTextSize(TextDisableInput);


			ImGui::SetCursorScreenPos({ Center.x - SizeText.x / 2.f ,Center.y - SizeText.y / 2.f });

			ImGui::TextColored(ImColor(0.7f, 0.1f, 0.1f, 1.f), TextDisableInput);

			if (processor->isHistoryModeEnabled() == false) {

				ImVec2 SizeText1 = ImGui::CalcTextSize(u8"Включить режим истории тут");

				ImGui::SetCursorScreenPos({ Center.x - SizeText1.x / 2.f ,Center.y + SizeText.y / 2.f + 5.f });


				if (ImGui::Button(u8"Включить режим истории тут")) {
					processor->ToggleHistoryMode();
				}

			}

		}
		ImGui::End();
	}

	ImGui::PopStyleVar();

}
void Widget_HistoryInstruction::Update() {
	UpdateActive();
}

nlohmann::json Widget_HistoryInstruction::Save() {
	return SaveDefaultParameters();
}
void Widget_HistoryInstruction::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}