#include "I8080.UI.ColorPicker.h"

Widget_ColorPicker::Widget_ColorPicker(TextEditor* editor) : I8080_Widget(u8"Все цвета") {
	this->editor = editor;
}
Widget_ColorPicker::~Widget_ColorPicker() {

}

void Widget_ColorPicker::Draw() {
	if (GetFlagShow() == false)
		return;


	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGuiStyle& style = ImGui::GetStyle();
		float height = style.ItemSpacing.y;
		style.ItemSpacing.y = 0.f;
		ImVec2 SizeWind = { abs(ImGui::GetWindowSize().x) / 16.f, abs(ImGui::GetWindowSize().y - style.FramePadding.y - style.WindowPadding.y - ImGui::GetFontSize()) / 16.f };
		float minSize = (std::min)(SizeWind.x, SizeWind.y);

		bool ShowTooltip = false;

		static bool FirstPress = true;


		static std::vector<RGB> Colors;
		if (Colors.size() == 0)
		{
			for (unsigned int h = 0; h < 16; h++) {
				for (unsigned int j = 0; j < 16; j++) {
					unsigned char value = unsigned char(16) * h + j;
					std::string bits = int2stringBin(value);
					unsigned char r = (value >> 6);
					r *= 85;
					unsigned char g = (value << 2);
					g = g >> 5;
					g *= 32;
					unsigned char b = (value << 5);
					b = b >> 5;
					b *= 32;

					Colors.push_back(RGB{ double(r),double(g),double(b) });

				}

			}

		}


		ImVec2 avail_size = ImGui::GetContentRegionAvail();
		ImVec2 pos = ImGui::GetCursorScreenPos();

		bool MouseInPopup = false;

		if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + avail_size.x, pos.y + avail_size.y))) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImGui::OpenPopup("PopupSettingColorPicker");
			}
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
		if (ImGui::BeginPopup("PopupSettingColorPicker"))
		{
			MouseInPopup = true;

			static float ColorsLine[3] = { 0.f,0.f,0.f };
			static int Mode_Color_Space = 0;
			static std::vector<RGB> FamiliarColor;


			bool SourceColor_Changed = false;
			bool ModeColorSpace_Changed = false;


			ImGui::SeparatorText(u8"Инструменты");
			ImGui::Button(std::string(ICON_FA_EYE_DROPPER).c_str());
			ImGui::SameLine();
			ImGui::Text(u8"Пипетка");

			float ColorsLine_last[3] = { ColorsLine[0],ColorsLine[1],ColorsLine[2] };

			ImGui::ColorEdit3("", ColorsLine, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine();
			ImGui::Text(u8"Ручной выбор");






			ImGui::SeparatorText(u8"Метрика для цветов");


			int last_Mode = Mode_Color_Space;

			ImGui::RadioButton(u8"Евклидова", &Mode_Color_Space, 0);
			ImGui::SameLine();
			ImGui::RadioButton("CIE76", &Mode_Color_Space, 1);
			ImGui::SameLine();
			ImGui::RadioButton("CIE94", &Mode_Color_Space, 2);



			if (Mode_Color_Space != last_Mode)
			{
				ModeColorSpace_Changed = true;
			}
			if (ColorsLine_last[0] != ColorsLine[0] || ColorsLine_last[1] != ColorsLine[1] || ColorsLine_last[2] != ColorsLine[2])
			{
				SourceColor_Changed = true;
			}

			if (ModeColorSpace_Changed || SourceColor_Changed || FamiliarColor.size() == 0)
			{
				switch (Mode_Color_Space)
				{
				case 0:
					FamiliarColor = GetSortedByDeltaColors_Eucledean(Colors, RGB{ ColorsLine[0] * 255.f, ColorsLine[1] * 255.f, ColorsLine[2] * 255.f });
					break;
				case 1:
					FamiliarColor = GetSortedByDeltaColors_CIE76(Colors, RGB{ ColorsLine[0] * 255.f, ColorsLine[1] * 255.f, ColorsLine[2] * 255.f });
					break;
				case 2:
					FamiliarColor = GetSortedByDeltaColors_CIE94(Colors, RGB{ ColorsLine[0] * 255.f, ColorsLine[1] * 255.f, ColorsLine[2] * 255.f });
					break;
				default:
					break;
				}

			}

			ImGui::SeparatorText(u8"Похожие цвета");

			for (int i = 0; i < 48; i++)
			{
				if (i != 16 && i != 32 && i != 0)
				{
					ImGui::SameLine(0.f, 0.f);
				}

				std::string bin_r = int2stringBin((int)FamiliarColor[i].r / 85, 2);
				std::string bin_g = int2stringBin((int)FamiliarColor[i].g / 32, 3);
				std::string bin_b = int2stringBin((int)FamiliarColor[i].b / 32, 3);

				std::string bin_value = "0b" + bin_r + bin_g + bin_b;

				int value = string2hex(bin_value);


				if (ImGui::ColorButton(std::string("ButtonFamiliarColor " + std::to_string(i)).c_str(), ImVec4(FamiliarColor[i].r / 255.0, FamiliarColor[i].g / 255.0, FamiliarColor[i].b / 255.0, 1),
					ImGuiColorEditFlags_NoSidePreview |
					ImGuiColorEditFlags_NoDragDrop |
					ImGuiColorEditFlags_NoSmallPreview |
					ImGuiColorEditFlags_NoAlpha |
					ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip,
					ImVec2(minSize, minSize))) {
					std::cout << "Insert color: [" << bin_value << "]" << std::endl;
					editor->InsertText(bin_value);
					FirstPress = false;
				}

				if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
					ImGui::BeginTooltip();



					if (FirstPress)
						ImGui::Text(u8"Нажми не бойся)))))...");



					ImGui::Text("Bin: 0b");
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), bin_r.c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), bin_g.c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), bin_b.c_str());

					ImGui::Text(("Hex: " + int2string_0x_Hex(value)).c_str());
					ImGui::Text(("Dec: " + std::to_string(value)).c_str());


					ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), ("R: " + std::to_string((int)FamiliarColor[i].r)).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), (" G: " + std::to_string((int)FamiliarColor[i].g)).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), (" B: " + std::to_string((int)FamiliarColor[i].b)).c_str());


					ImGui::EndTooltip();
				}
			}




			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();







		for (unsigned int h = 0; h < 16; h++) {
			for (unsigned int j = 0; j < 16; j++) {
				unsigned char value = unsigned char(16) * h + j;
				std::string bits = int2stringBin(value);
				unsigned char r = (value >> 6);
				r *= 85;
				unsigned char g = (value << 2);
				g = g >> 5;
				g *= 32;
				unsigned char b = (value << 5);
				b = b >> 5;
				b *= 32;
				//cout << "orig:" << int2stringBin(value) << " b: " << int2stringBin(b) << endl;
				if (j != 0) {
					ImGui::SameLine(0.f, 0.f);
				}

				if (ImGui::ColorButton(std::string("ButtonColor " + std::to_string(16 * h + j)).c_str(), ImVec4(r / 255.0, g / 255.0, b / 255.0, 1),
					ImGuiColorEditFlags_NoSidePreview |
					ImGuiColorEditFlags_NoDragDrop |
					ImGuiColorEditFlags_NoSmallPreview |
					ImGuiColorEditFlags_NoAlpha |
					ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip,
					ImVec2(minSize, minSize))) {
					FirstPress = false;
					editor->InsertText("0b" + bits);
				}

				if (!ShowTooltip && ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
					ShowTooltip = true;
					ImGui::BeginTooltip();

					if (FirstPress)
						ImGui::Text(u8"Нажми не бойся)))))...");

					ImGui::Text("Bin: 0b");
					// + bits
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), bits.substr(0, 2).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), bits.substr(2, 3).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), bits.substr(5, 3).c_str());

					ImGui::Text(("Hex: " + int2string_0x_Hex(value)).c_str());
					ImGui::Text(("Dec: " + std::to_string(value)).c_str());

					ImGui::TextColored(ImVec4(1, 0.55, 0.55, 1), ("R: " + std::to_string(r)).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 1, 0.55, 1), (" G: " + std::to_string(g)).c_str());
					ImGui::SameLine(0, 0);
					ImGui::TextColored(ImVec4(0.55, 0.55, 1, 1), (" B: " + std::to_string(b)).c_str());
					//ImGui::Text(("R: " + to_string(r) + " G: " + to_string(g) + " B: " + to_string(b)).c_str());
					ImGui::EndTooltip();
				}
			}

		}
		style.ItemSpacing.y = height;
		ImGui::End();
	}


}
void Widget_ColorPicker::Update() {

}

std::string Widget_ColorPicker::Save() {
	std::string output = "";
	output += MakeBegin(1);
	output += MakeSaveItem(std::string("Flag_Show"), std::to_string(GetFlagShow()));
	return output;
}

void Widget_ColorPicker::Load(const std::string& Data) {
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