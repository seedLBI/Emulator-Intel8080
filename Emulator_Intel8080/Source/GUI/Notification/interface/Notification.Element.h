#ifndef NOTIFICATION_ELEMENT_H
#define NOTIFICATION_ELEMENT_H

#include "ThirdParty/ImGui/imgui.h"

class N_Element {
public:
	N_Element();
	~N_Element();
	virtual void Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax);
	virtual ImVec2 GetSize();

	virtual void SetAlpha(const float& alphaValue);
};


#endif // !NOTIFICATION_ELEMENT_H
