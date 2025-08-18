#include "Widget.PixelScreen.h"


Widget_PixelScreen::Widget_PixelScreen(GLFWwindow* window, I8080* processor) :I8080_Widget(u8"Пиксельный экран") {
	this->window = window;
	this->processor = processor;
	pbo = new PBO(window);
	bufferPixelScreen = new unsigned char[256 * 256 * 4];
}

Widget_PixelScreen::~Widget_PixelScreen() {

}
void Widget_PixelScreen::Draw() {

	if (GetFlagShow() == false)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

	//ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_None);
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);


	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_NoScrollbar)) {




		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = g.CurrentWindow;



		ImVec2 avail_size = ImGui::GetContentRegionAvail();
		ImVec2 pos = ImGui::GetCursorScreenPos();


		bool MouseInPopup = false;

		if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + avail_size.x, pos.y + avail_size.y))) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImGui::OpenPopup("PopupSettingPixelScreen");
			}
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
		if (ImGui::BeginPopup("PopupSettingPixelScreen"))
		{
			MouseInPopup = true;

			ImGui::SeparatorText(u8"Соотношение");

			ImGui::RadioButton(u8"Квадратное", &Ratio_Mode, 0);
			ImGui::SameLine();
			ImGui::RadioButton(u8"Размер окна", &Ratio_Mode, 1);

			//ImGui::Checkbox(u8"Квадратное", &SquareScreenDraw);
			ImGui::SeparatorText(u8"Линии");
			ImGui::Checkbox(u8"Рисовать?", &DrawLines);
			ImGui::ColorEdit4(u8"Цвет", ColorsLine, ImGuiColorEditFlags_NoInputs);
			ImGui::SliderInt(u8"Толщина", &ThiknessLines, 1, 3);
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();



		float min_sizeImage = std::min(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
		ImVec2 sizeImage;
		ImVec2 currentPos = pos;
		if (Ratio_Mode == 0)
		{
			sizeImage = ImVec2(min_sizeImage, min_sizeImage);
			currentPos = ImVec2(pos.x + ImGui::GetContentRegionAvail().x / 2.f - min_sizeImage / 2.f, pos.y + ImGui::GetContentRegionAvail().y / 2.f - min_sizeImage / 2.f);
		}
		else {
			sizeImage = ImGui::GetContentRegionAvail();
		}

		ImGui::SetCursorScreenPos(currentPos);
		ImGui::Image((void*)pbo->tex_id, sizeImage, ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 0));


		if (DrawLines) {
			float CountLinesHorizontal = 256.f;
			float CountLinesVertical = 256.f;

			float stepX = sizeImage.x / CountLinesVertical;
			float stepY = sizeImage.y / CountLinesHorizontal;


			ImVec4 colorLine = ImVec4(ColorsLine[0], ColorsLine[1], ColorsLine[2], ColorsLine[3]);

			for (float i = 0; i <= sizeImage.x; i += stepX)
				window->DrawList->AddLine(ImVec2(currentPos.x + i, currentPos.y), ImVec2(currentPos.x + i, currentPos.y + sizeImage.x), ImGui::ColorConvertFloat4ToU32(colorLine), (float)ThiknessLines);
			for (float i = stepY; i < sizeImage.y - 2; i += stepY)
				window->DrawList->AddLine(ImVec2(currentPos.x, currentPos.y + i), ImVec2(currentPos.x + sizeImage.x, currentPos.y + i), ImGui::ColorConvertFloat4ToU32(colorLine), (float)ThiknessLines);
		}


		ImGui::End();
	}
	ImGui::PopStyleVar();
}
void Widget_PixelScreen::Update() {
	UpdateActive();

	if (GetFlagShow() == false)
		return;

	static std::vector<std::vector<unsigned char>> last_array_colors;

	Port_PixelScreen* p = dynamic_cast<Port_PixelScreen*>(processor->Get_External_Peripherals()[0x05]);
	std::vector<std::vector<unsigned char>> array_colors = p->Get_Array_colors();

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			//vec2 p = vec2(window->GetConsoleSize().x - 28, window->GetConsoleSize().y - 21) + vec2(j, i);
			unsigned char value = array_colors[i][j];
			unsigned char r = (value >> 6);
			r *= 85;
			unsigned char g = (value << 2);
			g = g >> 5;
			g *= 32;
			unsigned char b = (value << 5);
			b = b >> 5;
			b *= 32;

			bufferPixelScreen[(i * 256 + j) * 4 + 0] = r;
			bufferPixelScreen[(i * 256 + j) * 4 + 1] = g;
			bufferPixelScreen[(i * 256 + j) * 4 + 2] = b;
			bufferPixelScreen[(i * 256 + j) * 4 + 3] = 255;
		}
	}



	if (last_array_colors != array_colors){
		pbo->fill(bufferPixelScreen);
		pbo->draw();
	}

	last_array_colors = array_colors;
}

nlohmann::json Widget_PixelScreen::Save() {

	nlohmann::json result = SaveDefaultParameters();

	result["Ratio_Mode"] = Ratio_Mode;
	result["DrawGrid"] = DrawLines;

	result["Line"]["thikness"] = ThiknessLines;
	result["Line"]["color"]["red"] = ColorsLine[0];
	result["Line"]["color"]["blue"] = ColorsLine[1];
	result["Line"]["color"]["green"] = ColorsLine[2];
	result["Line"]["color"]["alpha"] = ColorsLine[3];

	return result;

}

void Widget_PixelScreen::Load(const nlohmann::json& Data) {

	ReadDefaultParameters(Data);

	if (Data.contains("Ratio_Mode"))
		Ratio_Mode = Data["Ratio_Mode"].get<int>();

	if (Data.contains("DrawGrid"))
		DrawLines = Data["DrawGrid"].get<bool>();

	if (Data.contains("Line")) {
		ThiknessLines = Data["Line"]["thikness"].get<int>();
		ColorsLine[0] = Data["Line"]["color"]["red"].get<float>();
		ColorsLine[1] = Data["Line"]["color"]["blue"].get<float>();
		ColorsLine[2] = Data["Line"]["color"]["green"].get<float>();
		ColorsLine[3] = Data["Line"]["color"]["alpha"].get<float>();
	}
}