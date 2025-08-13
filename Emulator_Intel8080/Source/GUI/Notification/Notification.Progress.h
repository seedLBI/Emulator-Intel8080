#ifndef NOTIFICATION_PROGRESS_H
#define NOTIFICATION_PROGRESS_H

#include "ThirdParty/ImGui/imgui.h"
#include "interface/Notification.Element.h"
#include "Utils/TextUtils.h"
#include <string>


class N_Progress : public N_Element
{
public:
	N_Progress(const ImColor& TextColor, const char* NameProgress, const char* UnitName, float* PtrValue, const float& MaxValue, const bool& InPercent);
	N_Progress(const ImColor& TextColor, const char* NameProgress, const char* UnitName, const float& ConstValue, const float& MaxValue, const bool& InPercent);




	~N_Progress();

	void Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax) override;

	ImVec2 GetSize() override;

	void SetAlpha(const float& alphaValue) override;

private:

	float MaxValue;
	float* PtrValue = nullptr;

	float ConstValue = 0;



	const char* NameProgress = nullptr;
	const char* UnitName = nullptr;
	bool InPercent = false;

	std::string FullUnit;

	ImVec2 size_UnitName; 
	ImVec2 size_ProgressName;

	ImColor TextColor;
	float alpha = 0.f;
};



#endif // !NOTIFICATION_PROGRESS_H
