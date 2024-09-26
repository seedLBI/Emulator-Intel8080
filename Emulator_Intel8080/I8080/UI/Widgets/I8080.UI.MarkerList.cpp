#include "I8080.UI.MarkerList.h"



Widget_MarkerList::Widget_MarkerList(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* MnemocodeViewer) :I8080_Widget(u8"�������") {
	this->processor = processor;
	this->translator = translator;
	this->MnemocodeViewer = MnemocodeViewer;
}

Widget_MarkerList::~Widget_MarkerList() {

}

void Widget_MarkerList::Draw() {
	if (GetFlagShow() == false)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 3));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_AlwaysAutoResize)) {

		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_ScrollY;
		if (ImGui::BeginTable("table_markers", 2, flags))
		{
			ImGui::TableSetupColumn(u8"������", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"��������", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible

			ImGui::TableHeadersRow();

			int count = 0;
			for (int i = 0; i < translator->Opcodes.size(); i++)
			{
				if (translator->Opcodes[i].marker.size() != 0)
				{
					ImGui::TableNextRow();


					int adress = translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l;

					if (processor->GetProgrammCounter() == adress)
					{
						ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.9f, 0.3f, 0.45f)); // Flat or Gradient?
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, row_bg_color);
					}



					
					if (processor->GetBreakpointsInMemory()[adress]){
						ImU32 row_bg_color = ImGui::GetColorU32(ImVec4(0.9f, 0.9f, 0.3f, 0.45f)); // Flat or Gradient?
						ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, row_bg_color);
						break;
					}
					


					ImGui::TableSetColumnIndex(1);

					bool pressed = false;
					ImGui::Selectable(translator->Opcodes[i].marker.c_str(), &pressed, ImGuiSelectableFlags_SpanAllColumns);
					if (pressed) {
						processor->SetProgrammCounter(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
						MnemocodeViewer->FollowCursorPC();
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Middle)) {
						MnemocodeViewer->FollowCursor(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
						processor->SetBreakPointPosition(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
					}

					ImGui::TableSetColumnIndex(0);
					ImGui::Text(int2stringDoubleHex(translator->Opcodes[i].adress_h, translator->Opcodes[i].adress_l).c_str(), 0, count);
					count++;
				}
			}

			ImGui::EndTable();
		}


		ImGui::End();
	}
	ImGui::PopStyleVar();
}

void Widget_MarkerList::Update() {

}

std::string Widget_MarkerList::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_MarkerList::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}

