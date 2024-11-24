#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "imgui.h"
#include "OpenglWindow/OpenglWindow.h"

void Lerp(ImVec2& from, const ImVec2& to, const float& force_lerp);

void Lerp(float& from, const float& to, const float& force_lerp);

#endif


