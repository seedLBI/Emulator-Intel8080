#include "Notification.Message.h"


N_Message::N_Message(const ImColor ColorText, std::string& Text) :N_Element() {
	this->Raw_ColorText = ColorText;
	this->Text = Text;
	alphaText = 0.f;
}

N_Message::N_Message(const ImColor ColorText, const char* Text) :N_Element() {
	this->Raw_ColorText = ColorText;
	this->Text = Text;
	alphaText = 0.f;
}

N_Message::~N_Message() = default;

void N_Message::Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax)  {

	// Устанавливаем ограничение на текстовый регион
	draw_list->PushClipRect(rectMin, rectMax);

	// Рендерим текст. Функция RenderTextWrapped автоматически переносит текст по словам.
	ImColor temp = Raw_ColorText;
	temp.Value.w *= alphaText;

	draw_list->AddText(NULL, 0.0f, rectMin, temp, Text.c_str(), NULL, rectMax.x - rectMin.x);

	// Снимаем ограничение на текстовый регион
	draw_list->PopClipRect();


	//ImGui::TextColored(ColorText, Text);
}

ImVec2 N_Message::GetSize()  {
	return ImGui::CalcTextSize(Text.c_str(), 0);
}


void N_Message::SetAlpha(const float& alphaValue) {
	alphaText = alphaValue;
}
