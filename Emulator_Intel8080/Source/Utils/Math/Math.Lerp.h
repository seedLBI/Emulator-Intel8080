#ifndef MATH_LERP_UTILS_H
#define MATH_LERP_UTILS_H

#include "ThirdParty/ImGui/imgui.h"
#include <cmath>



void Lerp(ImColor& from, const ImColor& to, const float& force_lerp, const float& deltaTime);

void Lerp(ImVec2& from, const ImVec2& to, const float& force_lerp, const float& deltaTime);
void Lerp(float& from, const float& to, const float& force_lerp, const float& deltaTime);

#endif


