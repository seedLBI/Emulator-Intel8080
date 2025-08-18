#ifndef IMGUI_UTILS_H
#define IMGUI_UTILS_H


#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include <string>


void RenderTextWrapped(const char* text, bool bIndentToHere);

void TextCenteredOnLine(const char* label, int col, int row, float alignment, bool AndY);

void TextCenteredOnLine(const char* label, int col, int row);

void TextWithTooltipInMainMenuBar(const char* label, const char* tooltip);

void RenderTextAlignedClipped(const char* text, const char* text_end = NULL, const ImVec2* p_text_size_if_avail = NULL, float align_x = 1.0f);

void MyHelpMarker(const char* desc);

void DrawTextWithBackground(const char* text, ImVec4 bgColor);

void RenderCharacterInRect(ImFont* font, ImDrawList* draw_list, const ImVec2& pos, const ImVec2& size, const char* text, ImU32 color);

ImVec2 GetCharacterSize(ImFont* font, char character);

bool ButtonCenteredOnLine(const char* label, float alignment);

void ButtonCheckBox(const char* label, const char* help, bool& state);


bool ButtonDelete(ImGuiWindow* imgui_window, ImDrawList* draw_list, const char* nameIndex, const ImU32& ColorText);

void MyImageRounded(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), float rounding = 0.0f, ImU32 col = IM_COL32_WHITE);

#endif
