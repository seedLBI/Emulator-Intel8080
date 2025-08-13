#include "IntroManager.h"


IntroManager::IntroManager() : ISettingObject(u8"�����", u8"�����") {

}

bool IntroManager::IsNeedDraw() {
	return flag_NeedDraw;
}


IntroManager::~IntroManager() {

}

void IntroManager::DrawSetting() {

	ISettingObject::DrawBegin();

	if (ImGui::RadioButton(u8"���������� ", flag_NeedDraw)) {
		flag_NeedDraw = !flag_NeedDraw;
	}
	
	ImGui::SameLine();

	HelpMarker(u8"���������\\�������� ����� ��������� �������� � ����������� � �������, �����������");

	ImGui::SameLine();

	if (flag_NeedDraw == true) 
		ImGui::TextDisabled(u8"����� �� ��������... � ��������");
	else
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), std::string(std::string(ICON_FA_FACE_ANGRY) + std::string(ICON_FA_FACE_ANGRY) + u8" �����!! " + std::string(ICON_FA_FACE_ANGRY) + std::string(ICON_FA_FACE_ANGRY)).c_str());


}


nlohmann::json IntroManager::SaveSetting() {

	nlohmann::json result;

	result["flag_NeedDraw"] = flag_NeedDraw;

	return result;
}
void IntroManager::LoadSetting(const nlohmann::json& Data) {

	if (Data.contains("flag_NeedDraw"))
		flag_NeedDraw = Data["flag_NeedDraw"].get<bool>();

}