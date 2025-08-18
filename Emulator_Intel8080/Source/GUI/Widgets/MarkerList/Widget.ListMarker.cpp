#include "Widget.ListMarker.h"



Widget_ListMarker::Widget_ListMarker(I8080* processor, TranslatorOutput* translator, Widget_MnemocodeViewer* MnemocodeViewer, NotificationManager* notificationManager) : I8080_Widget(u8"Маркеры") {
	this->processor = processor;
	this->translator = translator;
	this->MnemocodeViewer = MnemocodeViewer;
	this->notificationManager = notificationManager;
}

Widget_ListMarker::~Widget_ListMarker() {

}

void Widget_ListMarker::Draw() {
	if (GetFlagShow() == false)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 3));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow())) {


		static char* input = new char[120];

		static bool flag_first_init = false;

		if (flag_first_init == false) {
			flag_first_init = true;
			for (int i = 0; i < 120; i++)
				input[i] = 0;
		}
		ImGui::InputTextEx(u8"Поиск маркеров", u8"Поиск", input, 120, ImVec2(ImGui::GetWindowSize().x, 0), ImGuiInputTextFlags_NoLabel);

		int count_chars = 0;


		for (int i = 0; i < 120; i++) {
			if (input[i] == 0) {
				count_chars = i;
				break;
			}
		}


		static ImGuiTableFlags flags =
			ImGuiTableFlags_RowBg |
			ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_ScrollY;
		if (ImGui::BeginTable("table_markers", 2, flags))
		{
			ImGui::TableSetupColumn(u8"Адреса", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn(u8"Названия", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible

			ImGui::TableHeadersRow();

			int count = 0;
			for (int i = 0; i < translator->Opcodes.size(); i++)
			{




				if (translator->Opcodes[i].marker.size() != 0)
				{

					if (count_chars != 0)
					{
						bool flag_AllGood = true;
						if (translator->Opcodes[i].marker.size() < count_chars)
							continue;

						for (int j = 0; j < count_chars; j++)
						{
							if (translator->Opcodes[i].marker[j] != input[j]) {
								flag_AllGood = false;
								break;
							}
						}
						if (flag_AllGood == false)
							continue;
					}


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
						
					}
					


					ImGui::TableSetColumnIndex(1);

					bool pressed = false;
					ImGui::Selectable(translator->Opcodes[i].marker.c_str(), &pressed, ImGuiSelectableFlags_SpanAllColumns);
					if (pressed) {
						processor->SetProgrammCounter(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
						MnemocodeViewer->FollowCursorPC();
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Middle)) {
						if (MnemocodeViewer->GetFlagAlwaysFocus() == true) {
							static const ImVec4 color_GRAY{ 0.6f,0.1f,0.1f,1.0f };
							static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

							std::string text = u8"ВЫКЛЮЧИ режим постоянного\nслежения за PC в окне мнемокода";

							notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
								new N_Message(color_WHITE, text)
							},
								nullptr));
						}
						else {
							MnemocodeViewer->FollowCursor(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
						}
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
						processor->ToggleBreakPointPosition(translator->Opcodes[i].adress_h * 256 + translator->Opcodes[i].adress_l);
					}

					ImGui::TableSetColumnIndex(0);
					ImGui::Text(std::string(to_hex_string((uint8_t)translator->Opcodes[i].adress_h) + to_hex_string((uint8_t)translator->Opcodes[i].adress_l)).c_str(), 0, count);
					count++;
				}
			}

			ImGui::EndTable();
		}


		ImGui::End();
	}
	ImGui::PopStyleVar();
}

void Widget_ListMarker::Update() {
	UpdateActive();
}

nlohmann::json Widget_ListMarker::Save() {
	return SaveDefaultParameters();
}

void Widget_ListMarker::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}

