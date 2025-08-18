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


std::string IntroManager::SaveSetting() {


	std::string save_window = save_MakeBegin(1);
	save_window += save_MakeItem("flag_NeedDraw", std::to_string(flag_NeedDraw));


	return save_window;
}
void IntroManager::LoadSetting(const std::string& Data) {

	auto info = load_TokenizeData(Data);

	for (int i = 0; i < info.size(); i++) {

		if (info[i].NameVar == "flag_NeedDraw") {
			flag_NeedDraw = stoi(info[i].ValueVar);
		}
		else {
			std::cout << "Unknowed save element founded: [" << info[i].NameVar << "] [" << info[i].ValueVar << "]\n";
		}
	}
}