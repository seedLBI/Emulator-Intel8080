#include "ISettingObject.h"

ISettingObject::ISettingObject(const std::string& NameObject, const std::string& NameTab) : ISettingSavable(NameObject), ISettingDrawable(NameTab) {

}

void ISettingObject::DrawBegin() {
	ImGui::SeparatorText(GetSaveObjectName().c_str());
}