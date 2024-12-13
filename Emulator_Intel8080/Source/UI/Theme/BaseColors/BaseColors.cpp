#include "BaseColors.h"




BaseColors::BaseColors() : IThemeLoadable(u8"�������� �����") {

	InitListWord({
		u8"�����",u8"����� ������",u8"����� (�� ��������)",u8"����� (���������)",
		u8"���� (���)",u8"���� �������� (���)",u8"���� ����������� (���)",
		u8"�������",u8"������� (����)",u8"�����",u8"����� (����������)",
		u8"����� (��������)",u8"�������� (���)",u8"�������� �������� (���)",
		u8"�������� �������� (���)",u8"������ ���� (���)",u8"������� (checkbox)",
		u8"��������� (���)",u8"��������� (����������)",u8"��������� (���������� + ����������)",
		u8"��������� (���������� + ��������)",u8"��������",u8"�������� (����������)",u8"������",
		u8"������ (����������)",u8"������ (��������)",u8"���������",
		u8"��������� (����������)",u8"��������� (��������)",u8"�����������",
		u8"����������� (����������)",u8"����������� (��������)",u8"�������",
		u8"������� (����������)",u8"������� (���������)",u8"������� ������� (���������)",
		u8"���������� �������",u8"���������� ������� (���������)",u8"���������� ������� ������� (���������)",
		u8"��������� ��������",u8"��������� �������� (����������)",u8"��������� �������� (��������)",
		u8"��������� ������� (���)",u8"������� ������� �������",
		u8"������ ������� �������",u8"��� �������� ����� �������",
		u8"��� ������ ����� �������",u8"������������",
		});

	MapNameAndIndex = {
		{u8"�����",										ImGuiCol_Text},
		{u8"����� ������",								ImGuiCol_TextLink},
		{u8"����� (�� ��������)",						ImGuiCol_TextDisabled},
		{u8"����� (���������)",							ImGuiCol_TextSelectedBg},
		{u8"���� (���)",								ImGuiCol_WindowBg},
		{u8"���� �������� (���)",						ImGuiCol_ChildBg},
		{u8"���� ����������� (���)",					ImGuiCol_PopupBg},
		{u8"�������",									ImGuiCol_Border},
		{u8"������� (����)",							ImGuiCol_BorderShadow},
		{u8"�����",										ImGuiCol_FrameBg},
		{u8"����� (����������)",						ImGuiCol_FrameBgHovered},
		{u8"����� (��������)",							ImGuiCol_FrameBgActive},
		{u8"�������� (���)",							ImGuiCol_TitleBg},
		{u8"�������� �������� (���)",					ImGuiCol_TitleBgActive},
		{u8"�������� �������� (���)",					ImGuiCol_TitleBgCollapsed},
		{u8"������ ���� (���)",							ImGuiCol_MenuBarBg},
		{u8"������� (checkbox)",						ImGuiCol_CheckMark},
		{u8"��������� (���)",							ImGuiCol_ScrollbarBg},
		{u8"��������� (����������)",					ImGuiCol_ScrollbarGrab},
		{u8"��������� (���������� + ����������)",		ImGuiCol_ScrollbarGrabHovered},
		{u8"��������� (���������� + ��������)",			ImGuiCol_ScrollbarGrabActive},
		{u8"��������",									ImGuiCol_SliderGrab},
		{u8"�������� (����������)",						ImGuiCol_SliderGrabActive},
		{u8"������",									ImGuiCol_Button},
		{u8"������ (����������)",						ImGuiCol_ButtonHovered},
		{u8"������ (��������)",							ImGuiCol_ButtonActive},
		{u8"���������",									ImGuiCol_Header},
		{u8"��������� (����������)",					ImGuiCol_HeaderHovered},
		{u8"��������� (��������)",						ImGuiCol_HeaderActive},
		{u8"�����������",								ImGuiCol_Separator},
		{u8"����������� (����������)",					ImGuiCol_SeparatorHovered},
		{u8"����������� (��������)",					ImGuiCol_SeparatorActive},
		{u8"�������",									ImGuiCol_Tab},
		{u8"������� (����������)",						ImGuiCol_TabHovered},
		{u8"������� (���������)",						ImGuiCol_TabSelected},
		{u8"������� ������� (���������)",				ImGuiCol_TabSelectedOverline},
		{u8"���������� �������",						ImGuiCol_TabDimmed},
		{u8"���������� ������� (���������)",			ImGuiCol_TabDimmedSelected},
		{u8"���������� ������� ������� (���������)",	ImGuiCol_TabDimmedSelectedOverline},
		{u8"��������� ��������",						ImGuiCol_ResizeGrip},
		{u8"��������� �������� (����������)",			ImGuiCol_ResizeGripHovered},
		{u8"��������� �������� (��������)",				ImGuiCol_ResizeGripActive},
		{u8"��������� ������� (���)",					ImGuiCol_TableHeaderBg},
		{u8"������� ������� �������",					ImGuiCol_TableBorderStrong},
		{u8"������ ������� �������",					ImGuiCol_TableBorderLight},
		{u8"��� �������� ����� �������",				ImGuiCol_TableRowBg},
		{u8"��� ������ ����� �������",					ImGuiCol_TableRowBgAlt},
		{u8"������������",								ImGuiCol_DockingEmptyBg},
	};

}

BaseColors::~BaseColors() {

}


std::vector<NamedColor> BaseColors::GetDefaultLightColors() {
	std::vector<NamedColor> colors = {
	NamedColor{u8"�����",									ImColor(52,24,0,255)},
	NamedColor{u8"����� ������",							ImColor(82,184,221,255)},
	NamedColor{u8"����� (�� ��������)",						ImColor(152,135,113,255)},
	NamedColor{u8"����� (���������)",						ImColor(250,176,66,89)},
	NamedColor{u8"���� (���)",								ImColor(210,198,174,255)},
	NamedColor{u8"���� �������� (���)",						ImColor(0,0,0,0)},
	NamedColor{u8"���� ����������� (���)",					ImColor(235,220,199,255)},
	NamedColor{u8"�������",									ImColor(79,56,0,255)},
	NamedColor{u8"������� (����)",							ImColor(0,0,0,0)},
	NamedColor{u8"�����",									ImColor(247,237,212,255)},
	NamedColor{u8"����� (����������)",						ImColor(250,176,66,102)},
	NamedColor{u8"����� (��������)",						ImColor(234,175,61,171)},
	NamedColor{u8"�������� (���)",							ImColor(234,221,190,255)},
	NamedColor{u8"�������� �������� (���)",					ImColor(177,165,138,255)},
	NamedColor{u8"�������� �������� (���)",				ImColor(211,200,176,130)},
	NamedColor{u8"������ ���� (���)",						ImColor(215,205,182,255)},
	NamedColor{u8"������� (checkbox)",						ImColor(116,100,67,255)},
	NamedColor{u8"��������� (���)",							ImColor(255,239,218,135)},
	NamedColor{u8"��������� (����������)",					ImColor(182,168,151,204)},
	NamedColor{u8"��������� (���������� + ����������)",		ImColor(125,116,99,204)},
	NamedColor{u8"��������� (���������� + ��������)",		ImColor(125,109,83,255)},
	NamedColor{u8"��������",								ImColor(250,191,66,199)},
	NamedColor{u8"�������� (����������)",					ImColor(204,176,117,153)},
	NamedColor{u8"������",									ImColor(250,191,66,102)},
	NamedColor{u8"������ (����������)",						ImColor(250,183,66,255)},
	NamedColor{u8"������ (��������)",						ImColor(250,165,15,255)},
	NamedColor{u8"���������",								ImColor(250,172,66,79)},
	NamedColor{u8"��������� (����������)",					ImColor(250,179,66,204)},
	NamedColor{u8"��������� (��������)",					ImColor(250,183,66,255)},
	NamedColor{u8"�����������",								ImColor(97,84,67,158)},
	NamedColor{u8"����������� (����������)",				ImColor(204,133,36,199)},
	NamedColor{u8"����������� (��������)",					ImColor(204,133,36,255)},
	NamedColor{u8"�������",									ImColor(216,205,189,237)},
	NamedColor{u8"������� (����������)",					ImColor(250,176,66,204)},
	NamedColor{u8"������� (���������)",						ImColor(224,198,154,255)},
	NamedColor{u8"������� ������� (���������)",				ImColor(250,187,66,255)},
	NamedColor{u8"���������� �������",						ImColor(237,227,206,252)},
	NamedColor{u8"���������� ������� (���������)",			ImColor(232,216,189,255)},
	NamedColor{u8"���������� ������� ������� (���������)",	ImColor(255,183,66,255)},
	NamedColor{u8"��������� ��������",						ImColor(87,80,68,43)},
	NamedColor{u8"��������� �������� (����������)",			ImColor(250,179,66,171)},
	NamedColor{u8"��������� �������� (��������)",			ImColor(250,179,66,242)},
	NamedColor{u8"��������� ������� (���)",					ImColor(250,230,199,255)},
	NamedColor{u8"������� ������� �������",					ImColor(163,156,145,255)},
	NamedColor{u8"������ ������� �������",					ImColor(189,184,173,255)},
	NamedColor{u8"��� �������� ����� �������",				ImColor(0,0,0,0)},
	NamedColor{u8"��� ������ ����� �������",				ImColor(97,54,0,23)},
	NamedColor{u8"������������",							ImColor(49,31,8,255)}
	};
	return colors;

}
std::vector<NamedColor> BaseColors::GetDefaultDarkColors() {

	std::vector<NamedColor> colors = {
		{u8"�����",										ImColor(1.00f, 1.00f, 1.00f, 1.00f)},
		{u8"����� ������",								ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"����� (�� ��������)",						ImColor(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"����� (���������)",							ImColor(0.26f, 0.59f, 0.98f, 0.35f)},
		{u8"���� (���)",								ImColor(0.06f, 0.06f, 0.06f, 0.94f)},
		{u8"���� �������� (���)",						ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"���� ����������� (���)",					ImColor(0.08f, 0.08f, 0.08f, 0.94f)},
		{u8"�������",									ImColor(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"������� (����)",							ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"�����",										ImColor(0.16f, 0.29f, 0.48f, 0.54f)},
		{u8"����� (����������)",						ImColor(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"����� (��������)",							ImColor(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"�������� (���)",							ImColor(0.04f, 0.04f, 0.04f, 1.00f)},
		{u8"�������� �������� (���)",					ImColor(0.16f, 0.29f, 0.48f, 1.00f)},
		{u8"�������� �������� (���)",					ImColor(0.00f, 0.00f, 0.00f, 0.51f)},
		{u8"������ ���� (���)",							ImColor(0.14f, 0.14f, 0.14f, 1.00f)},
		{u8"������� (checkbox)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"��������� (���)",							ImColor(0.02f, 0.02f, 0.02f, 0.53f)},
		{u8"��������� (����������)",					ImColor(0.31f, 0.31f, 0.31f, 1.00f)},
		{u8"��������� (���������� + ����������)",		ImColor(0.41f, 0.41f, 0.41f, 1.00f)},
		{u8"��������� (���������� + ��������)",			ImColor(0.51f, 0.51f, 0.51f, 1.00f)},
		{u8"��������",									ImColor(0.24f, 0.52f, 0.88f, 1.00f)},
		{u8"�������� (����������)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"������",									ImColor(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"������ (����������)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"������ (��������)",							ImColor(0.06f, 0.53f, 0.98f, 1.00f)},
		{u8"���������",									ImColor(0.26f, 0.59f, 0.98f, 0.31f)},
		{u8"��������� (����������)",					ImColor(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"��������� (��������)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"�����������",								ImColor(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"����������� (����������)",					ImColor(0.10f, 0.40f, 0.75f, 0.78f)},
		{u8"����������� (��������)",					ImColor(0.10f, 0.40f, 0.75f, 1.00f)},
		{u8"�������",									ImColor(0.18f, 0.35f, 0.58f, 0.86f)},
		{u8"������� (����������)",						ImColor(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"������� (���������)",						ImColor(0.20f, 0.41f, 0.68f, 1.00f)},
		{u8"������� ������� (���������)",				ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"���������� �������",						ImColor(0.07f, 0.10f, 0.15f, 0.97f)},
		{u8"���������� ������� (���������)",			ImColor(0.14f, 0.26f, 0.42f, 1.00f)},
		{u8"���������� ������� ������� (���������)",	ImColor(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"��������� ��������",						ImColor(0.26f, 0.59f, 0.98f, 0.20f)},
		{u8"��������� �������� (����������)",			ImColor(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"��������� �������� (��������)",				ImColor(0.26f, 0.59f, 0.98f, 0.95f)},
		{u8"��������� ������� (���)",					ImColor(0.19f, 0.19f, 0.20f, 1.00f)},
		{u8"������� ������� �������",					ImColor(0.31f, 0.31f, 0.35f, 1.00f)},
		{u8"������ ������� �������",					ImColor(0.23f, 0.23f, 0.25f, 1.00f)},
		{u8"��� �������� ����� �������",				ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"��� ������ ����� �������",					ImColor(1.00f, 1.00f, 1.00f, 0.06f)},
		{u8"������������",								ImColor(0.20f, 0.20f, 0.20f, 1.00f)},
	};

	return colors;

}
void BaseColors::LoadColors() {

	ImVec4* colorss = ImGui::GetStyle().Colors;

	std::string toSearch;

	for (int i = 0; i < object_colors.colors.size(); i++) {

		toSearch = object_colors.colors[i].nameColor;

		if (MapNameAndIndex.contains(toSearch)) {
			colorss[MapNameAndIndex[toSearch]] = object_colors.colors[i].color.Value;
		}
	}
}