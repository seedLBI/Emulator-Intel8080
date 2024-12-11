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
	NamedColor{u8"�����",									ImVec4(0.00f, 0.00f, 0.00f, 1.00f)},
	NamedColor{u8"����� ������",							ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"����� (�� ��������)",						ImVec4(0.60f, 0.60f, 0.60f, 1.00f)},
	NamedColor{u8"����� (���������)",						ImVec4(0.26f, 0.59f, 0.98f, 0.35f)},
	NamedColor{u8"���� (���)",								ImVec4(0.94f, 0.94f, 0.94f, 1.00f)},
	NamedColor{u8"���� �������� (���)",						ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"���� ����������� (���)",					ImVec4(1.00f, 1.00f, 1.00f, 0.98f)},
	NamedColor{u8"�������",									ImVec4(0.00f, 0.00f, 0.00f, 0.30f)},
	NamedColor{u8"������� (����)",							ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"�����",									ImVec4(1.00f, 1.00f, 1.00f, 1.00f)},
	NamedColor{u8"����� (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
	NamedColor{u8"����� (��������)",						ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
	NamedColor{u8"�������� (���)",							ImVec4(0.96f, 0.96f, 0.96f, 1.00f)},
	NamedColor{u8"�������� �������� (���)",					ImVec4(0.82f, 0.82f, 0.82f, 1.00f)},
	NamedColor{u8"�������� �������� (���)",				ImVec4(1.00f, 1.00f, 1.00f, 0.51f)},
	NamedColor{u8"������ ���� (���)",						ImVec4(0.86f, 0.86f, 0.86f, 1.00f)},
	NamedColor{u8"������� (checkbox)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"��������� (���)",							ImVec4(0.98f, 0.98f, 0.98f, 0.53f)},
	NamedColor{u8"��������� (����������)",					ImVec4(0.69f, 0.69f, 0.69f, 0.80f)},
	NamedColor{u8"��������� (���������� + ����������)",		ImVec4(0.49f, 0.49f, 0.49f, 0.80f)},
	NamedColor{u8"��������� (���������� + ��������)",		ImVec4(0.49f, 0.49f, 0.49f, 1.00f)},
	NamedColor{u8"��������",								ImVec4(0.26f, 0.59f, 0.98f, 0.78f)},
	NamedColor{u8"�������� (����������)",					ImVec4(0.46f, 0.54f, 0.80f, 0.60f)},
	NamedColor{u8"������",									ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
	NamedColor{u8"������ (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"������ (��������)",						ImVec4(0.06f, 0.53f, 0.98f, 1.00f)},
	NamedColor{u8"���������",								ImVec4(0.26f, 0.59f, 0.98f, 0.31f)},
	NamedColor{u8"��������� (����������)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
	NamedColor{u8"��������� (��������)",					ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"�����������",								ImVec4(0.39f, 0.39f, 0.39f, 0.62f)},
	NamedColor{u8"����������� (����������)",				ImVec4(0.14f, 0.44f, 0.80f, 0.78f)},
	NamedColor{u8"����������� (��������)",					ImVec4(0.14f, 0.44f, 0.80f, 1.00f)},
	NamedColor{u8"�������",									ImVec4(0.76f, 0.80f, 0.84f, 0.93f)},
	NamedColor{u8"������� (����������)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
	NamedColor{u8"������� (���������)",						ImVec4(0.60f, 0.73f, 0.88f, 1.00f)},
	NamedColor{u8"������� ������� (���������)",				ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"���������� �������",						ImVec4(0.92f, 0.93f, 0.94f, 0.99f)},
	NamedColor{u8"���������� ������� (���������)",			ImVec4(0.74f, 0.82f, 0.91f, 1.00f)},
	NamedColor{u8"���������� ������� ������� (���������)",	ImVec4(0.26f, 0.59f, 1.00f, 1.00f)},
	NamedColor{u8"��������� ��������",						ImVec4(0.35f, 0.35f, 0.35f, 0.17f)},
	NamedColor{u8"��������� �������� (����������)",			ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
	NamedColor{u8"��������� �������� (��������)",			ImVec4(0.26f, 0.59f, 0.98f, 0.95f)},
	NamedColor{u8"��������� ������� (���)",					ImVec4(0.78f, 0.87f, 0.98f, 1.00f)},
	NamedColor{u8"������� ������� �������",					ImVec4(0.57f, 0.57f, 0.64f, 1.00f)},
	NamedColor{u8"������ ������� �������",					ImVec4(0.68f, 0.68f, 0.74f, 1.00f)},
	NamedColor{u8"��� �������� ����� �������",				ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"��� ������ ����� �������",				ImVec4(0.30f, 0.30f, 0.30f, 0.09f)},
	NamedColor{u8"������������",							ImVec4(0.20f, 0.20f, 0.20f, 1.00f)}
	};
	return colors;

}
std::vector<NamedColor> BaseColors::GetDefaultDarkColors() {

	std::vector<NamedColor> colors = {
		{u8"�����",										ImVec4(1.00f, 1.00f, 1.00f, 1.00f)},
		{u8"����� ������",								ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"����� (�� ��������)",						ImVec4(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"����� (���������)",							ImVec4(0.26f, 0.59f, 0.98f, 0.35f)},
		{u8"���� (���)",								ImVec4(0.06f, 0.06f, 0.06f, 0.94f)},
		{u8"���� �������� (���)",						ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"���� ����������� (���)",					ImVec4(0.08f, 0.08f, 0.08f, 0.94f)},
		{u8"�������",									ImVec4(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"������� (����)",							ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"�����",										ImVec4(0.16f, 0.29f, 0.48f, 0.54f)},
		{u8"����� (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"����� (��������)",							ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"�������� (���)",							ImVec4(0.04f, 0.04f, 0.04f, 1.00f)},
		{u8"�������� �������� (���)",					ImVec4(0.16f, 0.29f, 0.48f, 1.00f)},
		{u8"�������� �������� (���)",					ImVec4(0.00f, 0.00f, 0.00f, 0.51f)},
		{u8"������ ���� (���)",							ImVec4(0.14f, 0.14f, 0.14f, 1.00f)},
		{u8"������� (checkbox)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"��������� (���)",							ImVec4(0.02f, 0.02f, 0.02f, 0.53f)},
		{u8"��������� (����������)",					ImVec4(0.31f, 0.31f, 0.31f, 1.00f)},
		{u8"��������� (���������� + ����������)",		ImVec4(0.41f, 0.41f, 0.41f, 1.00f)},
		{u8"��������� (���������� + ��������)",			ImVec4(0.51f, 0.51f, 0.51f, 1.00f)},
		{u8"��������",									ImVec4(0.24f, 0.52f, 0.88f, 1.00f)},
		{u8"�������� (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"������",									ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"������ (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"������ (��������)",							ImVec4(0.06f, 0.53f, 0.98f, 1.00f)},
		{u8"���������",									ImVec4(0.26f, 0.59f, 0.98f, 0.31f)},
		{u8"��������� (����������)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"��������� (��������)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"�����������",								ImVec4(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"����������� (����������)",					ImVec4(0.10f, 0.40f, 0.75f, 0.78f)},
		{u8"����������� (��������)",					ImVec4(0.10f, 0.40f, 0.75f, 1.00f)},
		{u8"�������",									ImVec4(0.18f, 0.35f, 0.58f, 0.86f)},
		{u8"������� (����������)",						ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"������� (���������)",						ImVec4(0.20f, 0.41f, 0.68f, 1.00f)},
		{u8"������� ������� (���������)",				ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"���������� �������",						ImVec4(0.07f, 0.10f, 0.15f, 0.97f)},
		{u8"���������� ������� (���������)",			ImVec4(0.14f, 0.26f, 0.42f, 1.00f)},
		{u8"���������� ������� ������� (���������)",	ImVec4(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"��������� ��������",						ImVec4(0.26f, 0.59f, 0.98f, 0.20f)},
		{u8"��������� �������� (����������)",			ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"��������� �������� (��������)",				ImVec4(0.26f, 0.59f, 0.98f, 0.95f)},
		{u8"��������� ������� (���)",					ImVec4(0.19f, 0.19f, 0.20f, 1.00f)},
		{u8"������� ������� �������",					ImVec4(0.31f, 0.31f, 0.35f, 1.00f)},
		{u8"������ ������� �������",					ImVec4(0.23f, 0.23f, 0.25f, 1.00f)},
		{u8"��� �������� ����� �������",				ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"��� ������ ����� �������",					ImVec4(1.00f, 1.00f, 1.00f, 0.06f)},
		{u8"������������",								ImVec4(0.20f, 0.20f, 0.20f, 1.00f)},
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