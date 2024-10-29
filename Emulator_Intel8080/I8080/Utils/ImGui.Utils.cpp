#include "ImGui.Utils.h"


void RenderTextWrapped(const char* text, bool bIndentToHere = false)
{
	const char* text_end = text + strlen(text);
	static float indentX = 0.f;

	const float scale = 1.0f;
	float widthLeft = ImGui::GetContentRegionAvail().x;
	const char* endPrevLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, text_end, widthLeft);
	ImGui::TextUnformatted(text, endPrevLine);
	if (bIndentToHere)
	{
		float indentNeeded = ImGui::GetContentRegionAvail().x - widthLeft;
		if (indentNeeded)
		{
			ImGui::Indent(indentNeeded);
			indentX += indentNeeded;
		}
	}
	widthLeft = ImGui::GetContentRegionAvail().x;
	while (endPrevLine < text_end)
	{
		const char* text = endPrevLine;
		if (*text == ' ') { ++text; } // skip a space at start of line
		endPrevLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, text_end, widthLeft);
		ImGui::TextUnformatted(text, endPrevLine);
	}
}

void TextCenteredOnLine(const char* label, int col, int row, float alignment, bool AndY){
	ImGuiStyle& style = ImGui::GetStyle();

	float size_x = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail_x = ImGui::GetContentRegionAvail().x;
	float off_x = (avail_x - size_x) * alignment;


	float off_y = 0.f;
	if (AndY)
	{
		float size_y = ImGui::CalcTextSize(label).y + style.FramePadding.y * 2.0f;
		float avail_y = ImGui::GetContentRegionAvail().y;
		float off_y = (avail_y - size_y) * alignment;
	}

	if (AndY)
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize() * 0.5f);
	}

	if (off_x > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off_x);

	ImGui::Text(label, col, row);
}

void TextCenteredOnLine(const char* label, int col, int row) {
	float alignment = 0.5f;
	bool AndY = false;

	ImGuiStyle& style = ImGui::GetStyle();

	float size_x = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail_x = ImGui::GetContentRegionAvail().x;
	float off_x = (avail_x - size_x) * alignment;


	float off_y = 0.f;
	if (AndY)
	{
		float size_y = ImGui::CalcTextSize(label).y + style.FramePadding.y * 2.0f;
		float avail_y = ImGui::GetContentRegionAvail().y;
		float off_y = (avail_y - size_y) * alignment;
	}

	if (AndY)
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize() * 0.5f);
	}

	if (off_x > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off_x);

	ImGui::Text(label, col, row);
}

void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
	{
		ImGui::BeginTooltip();
		ImGui::Text(desc);
		ImGui::EndTooltip();
	}

}

void RenderCharacterInRect(ImFont* font, ImDrawList* draw_list, const ImVec2& pos, const ImVec2& size,const char* text, ImU32 color) {

	// Позиция текста внутри прямоугольника
	ImVec2 text_pos = ImVec2(pos.x, pos.y);

	// Прямоугольник для обрезки текста
	ImVec4 clip_rect = ImVec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

	// Рендеринг текста
	font->RenderText(draw_list, size.y, text_pos, color, clip_rect, text, nullptr, 0.0f, false);
}

ImVec2 GetCharacterSize(ImFont* font, char character) {
	// Получение глифа символа
	const ImFontGlyph* glyph = font->FindGlyph(character);
	if (glyph) {
		// Ширина символа
		float width = glyph->AdvanceX;
		// Высота символа
		float height = glyph->Y1 - glyph->Y0;
		return ImVec2(width, height);
	}
	return ImVec2(0, 0);
}

bool ButtonCenteredOnLine(const char* label, float alignment)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Button(label);
}


void ButtonCheckBox(const char* label, const char* help, bool& state) {
	if (ImGui::Button(label))
		state = !state;

	ImVec2 minn = ImGui::GetItemRectMin();
	ImVec2 maxx = ImGui::GetItemRectMax();

	if (ImGui::IsItemHovered()){
		if (ImGui::BeginTooltip()) {
			ImGui::Text(help);
			ImGui::EndTooltip();
		}
	}




	if (state){
		auto drawList = ImGui::GetWindowDrawList();
		drawList->AddRect(minn, maxx, ImColor(1.f, 1.f, 1.f),0.f,0,2.f);
	}

}
