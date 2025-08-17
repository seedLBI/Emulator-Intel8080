#include "Utils.ImGui.h"


void RenderTextWrapped(const char* text, bool bIndentToHere = false) {
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

void RenderTextAlignedClipped(const char* text, const char* text_end, const ImVec2* p_text_size_if_avail, float align_x)
{
	using namespace ImGui;
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;

	
	if (!text_end)
		text_end = text + strlen(text);

	const ImVec2 text_size = p_text_size_if_avail ? *p_text_size_if_avail : CalcTextSize(text, text_end);
	const ImVec2 avail = GetContentRegionAvail();

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 pos_max(pos.x + avail.x, window->ClipRect.Max.y);
	window->DC.CursorMaxPos.x = ImMax(window->DC.CursorMaxPos.x, pos.x + text_size.x);
	window->DC.IdealMaxPos.x = ImMax(window->DC.IdealMaxPos.x, pos.x + text_size.x);

	if (align_x > 0.0f && text_size.x < avail.x) {
		pos.x += ImTrunc((avail.x - text_size.x) * align_x);
		window->DC.CursorPos = pos;
	}

	
	RenderTextEllipsis(window->DrawList, pos, pos_max, pos_max.x,0.f, text, text_end, &text_size);

	const ImVec2 backup_max_pos = window->DC.CursorMaxPos;
	Dummy(ImVec2(ImMin(avail.x, text_size.x), text_size.y));
	//DebugDrawItemRect();
	window->DC.CursorMaxPos.x = backup_max_pos.x; // Cancel out extending content size because alignment will mess it up.

	if (avail.x < text_size.x && IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
		SetItemTooltip("%.*s", (int)(text_end - text), text);
}


void DrawTextWithBackground(const char* text, ImVec4 bgColor) {
	ImVec2 position = ImGui::GetCursorScreenPos();
	ImVec2 textSize = ImGui::CalcTextSize(text);

	// Получаем текущий draw list
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	// Координаты прямоугольника
	ImVec2 rectMin = position;
	ImVec2 rectMax = ImVec2(position.x + textSize.x, position.y + textSize.y);

	// Рисуем прямоугольник
	draw_list->AddRectFilled(rectMin, rectMax, ImColor(bgColor));

	// Рисуем текст поверх
	ImGui::SetCursorScreenPos(position);
	ImGui::TextUnformatted(text);
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

void TextWithTooltipInMainMenuBar(const char* label, const char* tooltip) {
	const std::string projectName = label;

	// Размер текста и паддингов
	ImVec2 padding = ImGui::GetStyle().FramePadding;
	ImVec2 textSize = ImGui::CalcTextSize(projectName.c_str());
	float totalW = textSize.x + padding.x * 2.0f;
	float totalH = textSize.y + padding.y * 2.0f;

	// Уменьшаем высоту (пример: на 20%)
	float shrinkFactor = 0.8f;
	float newH = totalH * shrinkFactor;

	// Получаем высоту строки (frame) — это высота меню/фрейма
	float frameH = ImGui::GetFrameHeight();

	// Считаем, на сколько нужно опустить наш элемент, чтобы центрировать по высоте
	float vertOffset = (frameH - newH) * 0.5f;

	// Позиционируемся на той же линии и со смещением по Y
	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.x + 10.0f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + vertOffset);

	// Резервируем область под наш элемент
	ImGui::Dummy(ImVec2(totalW, newH));

	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
		ImGui::BeginTooltip();
		ImGui::Text(tooltip);
		ImGui::EndTooltip();
	}

	// Координаты прямоугольника
	ImVec2 bb_min = ImGui::GetItemRectMin();
	ImVec2 bb_max = ImGui::GetItemRectMax();

	// Сдвиг текста внутри рамки для вертикального центрирования
	float textOffsetY = (newH - textSize.y) * 0.5f;

	// Рисуем рамку и текст
	ImDrawList* draw = ImGui::GetWindowDrawList();
	ImU32 col_text = ImGui::GetColorU32(ImGuiCol_Text);
	ImU32 col_back = ImGui::GetColorU32(ImGuiCol_FrameBg);

	draw->AddRectFilled(ImVec2(bb_min.x, bb_min.y + 3.f), bb_max, col_back, 0.0f);
	draw->AddText(
		ImVec2(bb_min.x + padding.x,
			bb_min.y + textOffsetY),
		col_text,
		projectName.c_str()
	);
}

void MyHelpMarker(const char* desc)
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


bool ButtonDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const char* nameIndex, const ImU32& ColorText) {
	ImVec2 p = ImGui::GetCursorScreenPos();
	float size = ImGui::GetFontSize();
	float offset = size / 6.f;
	float offset_edge = size / 8.f;

	ImVec2 Delete_min = ImVec2(p.x, p.y);
	ImVec2 Delete_max = ImVec2(p.x + size, p.y + size);
	ImRect Delete_size = ImRect(Delete_min.x, Delete_min.y, Delete_max.x, Delete_max.y);

	ImGuiID id = imgui_window->GetID(nameIndex);
	ImGui::ItemAdd(Delete_size, id);

	bool hovered, held;
	bool pressed_Delete = ImGui::ButtonBehavior(Delete_size, id, &hovered, &held, 0);
	ImU32 coll = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

	ImGui::RenderFrame(Delete_min, Delete_max, coll, false);

	RenderCharacterInRect(ImGui::GetFont(), ImGui::GetWindowDrawList(), ImVec2(p.x + size / 6.f, p.y), ImVec2(size, size), ICON_FA_TRASH, ColorText);

	p.x += size + 2.f * offset_edge;
	ImGui::SetCursorScreenPos(p);

	return pressed_Delete;
}
