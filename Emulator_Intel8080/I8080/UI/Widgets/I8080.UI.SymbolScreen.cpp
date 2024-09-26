#include "I8080.UI.SymbolScreen.h"


Widget_SymbolScreen::Widget_SymbolScreen(I8080* processor) :I8080_Widget(u8"Символьный экран") {
	this->processor = processor;
}
Widget_SymbolScreen::~Widget_SymbolScreen() {

}
void Widget_SymbolScreen::Draw() {
	if (GetFlagShow() == false)
		return;


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar)) {





		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = g.CurrentWindow;

		ImVec2 avail_size = ImGui::GetContentRegionAvail();
		ImVec2 pos = ImGui::GetCursorScreenPos();


		bool MouseInPopup = false;

		if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + avail_size.x, pos.y + avail_size.y))) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImGui::OpenPopup("PopupSettingSymbolScreen");
			}
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
		if (ImGui::BeginPopup("PopupSettingSymbolScreen"))
		{
			MouseInPopup = true;

			ImGui::SeparatorText(u8"Соотношение");

			ImGui::RadioButton(u8"Квадратное", &Ratio_Mode, 0);
			ImGui::SameLine();
			ImGui::RadioButton(u8"Размер окна", &Ratio_Mode, 1);

			ImGui::SeparatorText(u8"Линии");
			ImGui::Checkbox(u8"Рисовать?", &DrawLines);
			ImGui::ColorEdit4(u8"Цвет", ColorsLine, ImGuiColorEditFlags_NoInputs);
			ImGui::SliderInt(u8"Толщина", &ThiknessLines, 1, 5);
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();

		const static float CountLinesHorizontal = 20.f;
		const static float CountLinesVertical = 20.f;

		float SizeWindowX = avail_size.x;
		float SizeWindowY = avail_size.y;
		float mmmin = min(SizeWindowX, SizeWindowY);
		if (Ratio_Mode == 0)
		{
			SizeWindowX = mmmin;
			SizeWindowY = mmmin;
		}

		if (SizeWindowX != 0 && SizeWindowY != 0) {
			float stepX = SizeWindowX / CountLinesVertical;
			float stepY = SizeWindowY / CountLinesHorizontal;

			float pos_x_begin = avail_size.x / 2.f - SizeWindowX / 2.f;
			float pos_y_begin = avail_size.y / 2.f - SizeWindowY / 2.f;

			pos.x += pos_x_begin;
			pos.y += pos_y_begin;

			ImGui::SetWindowFontScale(min(stepY, stepX) / ImGui::GetFontSize());



			static I8080_SymbolScreen* p = dynamic_cast<I8080_SymbolScreen*>(processor->Get_External_Peripherals()[0x07]);
			vector<vector<unsigned char>> array_symbols = p->Get_Array_symbols();
			vector<vector<unsigned char>> array_colors = p->Get_Array_colors();

			const static ImVec4 array_index_colors[8] = { ImVec4(0,0,0,1),ImVec4(0,0,1,1),ImVec4(0,1,0,1),ImVec4(0,1,1,1),ImVec4(1,0,0,1),ImVec4(1,0,1,1),ImVec4(1,1,0,1),ImVec4(1,1,1,1) };

			for (int i = 0; i < array_symbols.size(); i++) {
				for (int j = 0; j < array_symbols.size(); j++) {

					char char_symbol = array_symbols[i][j];
					string str_symbol = GetSymbol_1251_OnNumber(char_symbol);
					
					unsigned int bg_color_symbol = string2hex("0b00000" + int2stringBin(array_colors[i][j]).substr(2, 3));
					unsigned int fg_color_symbol = string2hex("0b00000" + int2stringBin(array_colors[i][j]).substr(5, 3));



					ImVec2 sizeText = ImGui::CalcTextSize(str_symbol.c_str());
					ImVec2 CurrentPos = pos;
					CurrentPos.x += j * stepX;
					CurrentPos.y += i * stepY;

					window->DrawList->AddRectFilled(CurrentPos, ImVec2(CurrentPos.x + stepX, CurrentPos.y + stepY), ImGui::ColorConvertFloat4ToU32(array_index_colors[bg_color_symbol]));

					ImGui::SetCursorScreenPos(ImVec2(CurrentPos.x + stepX / 2 - sizeText.x / 2, CurrentPos.y + stepY / 2 - sizeText.y / 2));
					ImGui::TextColored(array_index_colors[fg_color_symbol], str_symbol.c_str());

					

					if (ImGui::IsMouseHoveringRect(CurrentPos, ImVec2(CurrentPos.x + stepX, CurrentPos.y + stepY)) && !MouseInPopup && ImGui::IsPopupOpen(nullptr,ImGuiPopupFlags_AnyPopupId) == false) {
						string bits = int2stringBin(array_colors[i][j]);

						window->DrawList->AddRectFilled(CurrentPos, ImVec2(CurrentPos.x + stepX, CurrentPos.y + stepY), ImGui::ColorConvertFloat4ToU32(ImVec4(0.55, 0.55, 1, 0.5)));

						ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
						ImGui::BeginTooltip();
						ImGui::SeparatorText(u8"Позиция");
						ImGui::Text(string("X: " + to_string(j)).c_str());
						ImGui::Text(string("Y: " + to_string(i)).c_str());
						ImGui::SeparatorText(u8"Цвет");
						ImGui::Text("Bin: 0b");
						ImGui::SameLine(0, 0);
						ImGui::Text(bits.substr(0, 2).c_str(), ImVec4(1, 1, 1, 1));
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), bits.substr(2, 1).c_str());
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), bits.substr(3, 1).c_str());
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), bits.substr(4, 1).c_str());
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), bits.substr(5, 1).c_str());
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), bits.substr(6, 1).c_str());
						ImGui::SameLine(0, 0);
						ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), bits.substr(7, 1).c_str());

						ImGui::Text(("Hex: " + int2string_0x_Hex(array_colors[i][j])).c_str());
						ImGui::Text(("Dec: " + to_string(uint8_t(array_colors[i][j]))).c_str());

						ImGui::SeparatorText(u8"Символ");
						ImGui::Text((u8"Сам символ: [" + str_symbol + "]").c_str());
						ImGui::Text(("Bin: 0b" + int2stringBin(char_symbol)).c_str());
						ImGui::Text(("Hex: " + int2string_0x_Hex(char_symbol)).c_str());
						ImGui::Text(("Dec: " + to_string(uint8_t(char_symbol))).c_str());


						ImGui::EndTooltip();
						ImGui::PopStyleVar();
					}



				}
			}


			ImGui::SetWindowFontScale(1.f);


			if (DrawLines) {
				ImVec4 colorLine = ImVec4(ColorsLine[0], ColorsLine[1], ColorsLine[2], ColorsLine[3]);

				for (float i = 0; i <= SizeWindowX; i += stepX)
					window->DrawList->AddLine(ImVec2(pos.x + i, pos.y), ImVec2(pos.x + i, pos.y + SizeWindowY), ImGui::ColorConvertFloat4ToU32(colorLine), ThiknessLines);
				for (float i = stepY; i < SizeWindowY - 2; i += stepY)
					window->DrawList->AddLine(ImVec2(pos.x, pos.y + i), ImVec2(pos.x + SizeWindowX, pos.y + i), ImGui::ColorConvertFloat4ToU32(colorLine), ThiknessLines);
			}
		}
		ImGui::End();
	}
	ImGui::PopStyleVar();
}

std::string Widget_SymbolScreen::Save() {
	std::string output = "";
	output += MakeBegin(8);
	output += MakeSaveItem(string("Flag_Show"), std::to_string(GetFlagShow()));
	output += MakeSaveItem(string("Ratio_Mode"), std::to_string(Ratio_Mode));
	output += MakeSaveItem(string("DrawLines"), std::to_string(DrawLines));
	output += MakeSaveItem(string("ThiknessLines"), std::to_string(ThiknessLines));
	output += MakeSaveItem(string("ColorsLine_red"), std::to_string(ColorsLine[0]));
	output += MakeSaveItem(string("ColorsLine_green"), std::to_string(ColorsLine[1]));
	output += MakeSaveItem(string("ColorsLine_blue"), std::to_string(ColorsLine[2]));
	output += MakeSaveItem(string("ColorsLine_alpha"), std::to_string(ColorsLine[3]));
	return output;
}


void Widget_SymbolScreen::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "Flag_Show")
			SetFlagShow(stoi(value_arg));
		else if (name_arg == "Ratio_Mode")
			Ratio_Mode = stoi(value_arg);
		else if (name_arg == "DrawLines")
			DrawLines = stoi(value_arg);
		else if (name_arg == "ThiknessLines")
			ThiknessLines = stoi(value_arg);
		else if (name_arg == "ColorsLine_red")
			ColorsLine[0] = stof(value_arg);
		else if (name_arg == "ColorsLine_green")
			ColorsLine[1] = stof(value_arg);
		else if (name_arg == "ColorsLine_blue")
			ColorsLine[2] = stof(value_arg);
		else if (name_arg == "ColorsLine_alpha")
			ColorsLine[3] = stof(value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}
}

void Widget_SymbolScreen::Update() {

}
