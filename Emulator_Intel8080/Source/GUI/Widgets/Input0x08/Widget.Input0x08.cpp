#include "Widget.Input0x08.h"


Widget_Input0x08::Widget_Input0x08(I8080* processor) : I8080_Widget(u8"Окно ввода"), IThemeLoadable(u8"Окно ввода") {
	this->processor = processor;

	IThemeLoadable::InitListWord({ u8"Фон при активации" });
	//ImColor color_Active;
}
Widget_Input0x08::~Widget_Input0x08() {

}



void Widget_Input0x08::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"Фон при активации")
			color_Active = object_colors.colors[i].color;
	}
}

std::vector<NamedColor> Widget_Input0x08::GetDefaultLightColors() {
	return {
		{u8"Фон при активации", ImColor(1.f,0.5f,1.f,1.f)}
	};
}

std::vector<NamedColor> Widget_Input0x08::GetDefaultDarkColors() {
	return {
		{u8"Фон при активации", ImColor(0.f,0.5f,0.f,1.f)}
	};
}


void Widget_Input0x08::SendValue_to_Port(const std::string& str_value) {
	if (str_value.size() != 0) {
		unsigned int value = std::stoi(str_value);
		if (value < 256)
			processor->InputAnswer2Port(value);
	}
	Focus_ones = true;
}



int Widget_Input0x08::InputTextCallback(ImGuiInputTextCallbackData* data) {
	// Проверяем, что вводимый символ - это число или backspace
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter) {
		// Если символ не цифра и не backspace, игнорируем ввод
		if (data->EventChar < '0' || data->EventChar > '9') {
			return 1;  // Неподходящий символ, отменяем ввод
		}
	}

	// Проверяем текущее значение в буфере
	if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
		if (data->BufTextLen > 0) {
			// Преобразуем строку в число
			int value = atoi(data->Buf);

			// Если число больше 255, удаляем последний символ
			if (value > 255) {
				if (data->BufTextLen > 0) {
					data->Buf[data->BufTextLen - 1] = '\0';  // Удаляем последний символ
					data->BufDirty = true;  // Отмечаем, что буфер был изменен
					data->BufTextLen--;  // Корректируем длину текста
				}
			}

			// Проверяем на наличие ведущих нулей
			if (data->BufTextLen > 1 && data->Buf[0] == '0') {
				// Удаляем первый символ, если это не единственный символ "0"
				for (int i = 0; i < data->BufTextLen; ++i) {
					data->Buf[i] = data->Buf[i + 1]; // Сдвигаем влево
				}
				data->Buf[data->BufTextLen - 1] = '\0';  // Удаляем последний символ
				data->BufTextLen--;  // Корректируем длину текста
				data->BufDirty = true;  // Отмечаем, что буфер был изменен
			}

		}
	}

	return 0;  // Возвращаем 0, если все ок
}




void Widget_Input0x08::Draw() {



	ImVec4 ColorBG = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
	float t = 0.f;
	ImVec4 NewColorBG;

	if (processor->IsWaitingPortInput()) {
		float t = abs( sin(glfwGetTime() * 8.f ) * 0.5f + 0.5f);


		NewColorBG.x = color_Active.Value.x * t + ColorBG.x * (1.f - t);
		NewColorBG.y = color_Active.Value.y * t + ColorBG.y * (1.f - t);
		NewColorBG.z = color_Active.Value.z * t + ColorBG.z * (1.f - t);
		NewColorBG.w = 1.f;
	}
	else {
		Focus_ones = true;
	}

	if (processor->IsWaitingPortInput() && Focus_ones) {
		if (GetFlagShow() == false)
			SetFlagShow(true);

		MakeActiveCurrentWidget();
	}

	if (GetFlagShow() == false)
		return;



 	ImGui::PushStyleColor(ImGuiCol_WindowBg, NewColorBG);

	if (ImGui::Begin(GetName_c_str(), GetPtrFlagShow(), ImGuiWindowFlags_AlwaysAutoResize)) {

		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
			ImGui::BeginTooltip();
			ImGui::Text(info);
			ImGui::EndTooltip();
		}

		ImGui::Text(u8"Ввод значения в порт 0x08");
		ImGui::Separator();

		static char buf2[4] = "";

		if (Focus_ones && processor->IsWaitingPortInput()){
			Focus_ones = false;
			ImGui::SetKeyboardFocusHere(0);
		}

		std::string str_value(buf2);


		if (ImGui::InputText(
			u8"Значение от 0 до 255",
			buf2,
			4,
			ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_NoLabel | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackEdit,
			InputTextCallback)
			) 
		{

			SendValue_to_Port(str_value);
			for (int i = 0; i < 4; i++)
				buf2[i] = 0;
		}

		
		ImGui::SameLine();

		if (ImGui::Button(u8"Ввод")) {
			if (processor->IsWaitingPortInput()){
				SendValue_to_Port(str_value);
			}

			for (int i = 0; i < 4; i++)
				buf2[i] = 0;
		}

		ImGui::SameLine();

		MyHelpMarker(u8"Вводить значение от 0 до 255, в любом случае у тебя не выйдет написать больше.");



		ImGui::End();
	}

	ImGui::PopStyleColor();

}
void Widget_Input0x08::Update() {
	UpdateActive();
}

nlohmann::json Widget_Input0x08::Save() {
	return SaveDefaultParameters();
}

void Widget_Input0x08::Load(const nlohmann::json& Data) {
	ReadDefaultParameters(Data);
}
