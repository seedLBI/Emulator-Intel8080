#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include <string>


void RenderTextWrapped(const char* text, bool bIndentToHere);

void TextCenteredOnLine(const char* label, int col, int row, float alignment, bool AndY);

void TextCenteredOnLine(const char* label, int col, int row);

void HelpMarker(const char* desc);

void DrawTextWithBackground(const char* text, ImVec4 bgColor);

void RenderCharacterInRect(ImFont* font, ImDrawList* draw_list, const ImVec2& pos, const ImVec2& size, const char* text, ImU32 color);

ImVec2 GetCharacterSize(ImFont* font, char character);

bool ButtonCenteredOnLine(const char* label, float alignment);

void ButtonCheckBox(const char* label, const char* help, bool& state);


bool ButtonDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const char* nameIndex, const ImU32& ColorText);