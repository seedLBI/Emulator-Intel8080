#include "Notification.Element.h"

N_Element::N_Element() = default;
N_Element::~N_Element() = default;
void N_Element::Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax) {

}
ImVec2 N_Element::GetSize() {
	return ImVec2{ 0,0 };
}
void N_Element::SetAlpha(const float& alphaValue) {

}