#include "Notification.Progress.h"


N_Progress::N_Progress(const ImColor& TextColor,const char* NameProgress, const char* UnitName, float* PtrValue, const float& MaxValue, const bool& InPercent) : N_Element() {
	this->TextColor = TextColor;
	this->UnitName = UnitName;
	this->NameProgress = NameProgress;
	this->PtrValue = PtrValue;
	this->MaxValue = MaxValue;
	this->InPercent = InPercent;
}

N_Progress::N_Progress(const ImColor& TextColor, const char* NameProgress, const char* UnitName, const float& ConstValue, const float& MaxValue, const bool& InPercent) : N_Element() {
	this->ConstValue = ConstValue;
	this->MaxValue = MaxValue;
	this->TextColor = TextColor;
	this->UnitName = UnitName;
	this->NameProgress = NameProgress;
	this->InPercent = InPercent;
}

N_Progress::~N_Progress() = default;

void N_Progress::Draw(ImDrawList* draw_list, const ImVec2& rectMin, const ImVec2& rectMax) {

	if (PtrValue == nullptr)
		FullUnit = cutFloat(std::to_string(ConstValue), 2) + "\\" + cutFloat(std::to_string(MaxValue), 2) + UnitName;
	else
		FullUnit = cutFloat(std::to_string(*PtrValue), 2) + "\\" + cutFloat(std::to_string(MaxValue), 2) + UnitName;

	
	ImColor temp = TextColor;
	temp.Value.w *= alpha;

	draw_list->AddText(NULL, 0.0f, rectMin, temp, NameProgress, NULL);

	draw_list->AddText(NULL, 0.0f, { rectMax.x- ImGui::CalcTextSize(FullUnit.c_str(), 0).x, rectMin.y}, temp, FullUnit.c_str(), NULL);

	draw_list->AddRectFilled({ rectMin.x,rectMin.y+ size_UnitName.y }, { rectMax.x , rectMin.y + size_UnitName.y*1.7f }, ImColor{ 0.1f,0.1f,0.1f,alpha }, 0.0f);

	float progress = 0.f;

	if (PtrValue == nullptr)
		progress = ConstValue / MaxValue;
	else
		progress = *PtrValue / MaxValue;

	float width_complete = rectMin.x + (rectMax.x - rectMin.x) * progress;

	draw_list->AddRectFilled({ rectMin.x,rectMin.y + size_UnitName.y }, { width_complete , rectMin.y + size_UnitName.y * 1.7f }, ImColor{ 0.3f,1.0f,0.3f,alpha }, 0.0f);

}

ImVec2 N_Progress::GetSize() {

	std::string TempFullUnit = cutFloat(std::to_string(MaxValue),2) + "\\" + cutFloat(std::to_string(MaxValue),2) + UnitName;

	size_UnitName = ImGui::CalcTextSize(TempFullUnit.c_str(), 0);
	size_ProgressName = ImGui::CalcTextSize(NameProgress, 0);

	return ImVec2(size_UnitName.x + 25.f + size_ProgressName.x, size_UnitName.y*2.f);
}

void N_Progress::SetAlpha(const float& alphaValue) {
	alpha = alphaValue;
}