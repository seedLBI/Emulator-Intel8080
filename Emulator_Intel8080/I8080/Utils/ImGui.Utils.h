#pragma once
#include "imgui.h"

void RenderTextWrapped(const char* text, bool bIndentToHere);

void TextCenteredOnLine(const char* label, int col, int row, float alignment, bool AndY);

void TextCenteredOnLine(const char* label, int col, int row);

void HelpMarker(const char* desc);

void RenderCharacterInRect(ImFont* font, ImDrawList* draw_list, const ImVec2& pos, const ImVec2& size, const char* text, ImU32 color);

ImVec2 GetCharacterSize(ImFont* font, char character);

bool ButtonCenteredOnLine(const char* label, float alignment);