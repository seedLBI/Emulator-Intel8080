#ifndef NOTIFICATION_MESSAGE_H
#define NOTIFICATION_MESSAGE_H

#include "ThirdParty/ImGui/imgui.h"
#include "interface/Notification.Element.h"
#include <string>


class N_Message : public N_Element {
public:
	N_Message(const ImColor ColorText, std::string& Text);

	N_Message(const ImColor ColorText, const char* Text);

	~N_Message();

	void Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax) override;

	void SetAlpha(const float& alphaValue) override;

	ImVec2 GetSize() override;

private:
	ImColor Raw_ColorText;
	float alphaText;

	std::string Text;
};


#endif // !NOTIFICATION_MESSAGE_H
