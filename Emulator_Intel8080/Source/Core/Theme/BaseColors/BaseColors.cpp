#include "BaseColors.h"




BaseColors::BaseColors() : IThemeLoadable(u8"Основные цвета") {

	InitListWord({
		u8"Текст",u8"Текст ссылки",u8"Текст (не активный)",u8"Текст (выбранный)",
		u8"Окно (фон)",u8"Окно дочернее (фон)",u8"Онко всплывающее (фон)",
		u8"Граница",u8"Граница (тень)",u8"Рамка",u8"Рамка (выделенная)",
		u8"Рамка (активная)",u8"Название (фон)",u8"Название активное (фон)",
		u8"Название свёрнутое (фон)",u8"Строка меню (фон)",u8"Галочка (checkbox)",
		u8"Прокрутка (фон)",u8"Прокрутка (схваченная)",u8"Прокрутка (схваченная + выделенная)",
		u8"Прокрутка (схваченная + активная)",u8"Ползунок",u8"Ползунок (схваченный)",u8"Кнопка",
		u8"Кнопка (выделенная)",u8"Кнопка (активная)",u8"Заголовок",
		u8"Заголовок (выделенный)",u8"Заголовок (активный)",u8"Раздилитель",
		u8"Раздилитель (выделенный)",u8"Раздилитель (активный)",u8"Вкладка",
		u8"Вкладка (выделенная)",u8"Вкладка (выбранная)",u8"Полоска вкладки (выбранная)",
		u8"Затемнённая вкладка",u8"Затемнённая вкладка (выбранная)",u8"Затемнённая полоска вкладки (выбранная)",
		u8"Изменение размеров",u8"Изменение размеров (выделенная)",u8"Изменение размеров (активная)",
		u8"Заголовок таблицы (фон)",u8"Толстые границы таблицы",
		u8"Тонкие границы таблицы",u8"Фон нечётных строк таблицы",
		u8"Фон чётных строк таблицы",u8"Пространство",
		});

	MapNameAndIndex = {
		{u8"Текст",										ImGuiCol_Text},
		{u8"Текст ссылки",								ImGuiCol_TextLink},
		{u8"Текст (не активный)",						ImGuiCol_TextDisabled},
		{u8"Текст (выбранный)",							ImGuiCol_TextSelectedBg},
		{u8"Окно (фон)",								ImGuiCol_WindowBg},
		{u8"Окно дочернее (фон)",						ImGuiCol_ChildBg},
		{u8"Онко всплывающее (фон)",					ImGuiCol_PopupBg},
		{u8"Граница",									ImGuiCol_Border},
		{u8"Граница (тень)",							ImGuiCol_BorderShadow},
		{u8"Рамка",										ImGuiCol_FrameBg},
		{u8"Рамка (выделенная)",						ImGuiCol_FrameBgHovered},
		{u8"Рамка (активная)",							ImGuiCol_FrameBgActive},
		{u8"Название (фон)",							ImGuiCol_TitleBg},
		{u8"Название активное (фон)",					ImGuiCol_TitleBgActive},
		{u8"Название свёрнутое (фон)",					ImGuiCol_TitleBgCollapsed},
		{u8"Строка меню (фон)",							ImGuiCol_MenuBarBg},
		{u8"Галочка (checkbox)",						ImGuiCol_CheckMark},
		{u8"Прокрутка (фон)",							ImGuiCol_ScrollbarBg},
		{u8"Прокрутка (схваченная)",					ImGuiCol_ScrollbarGrab},
		{u8"Прокрутка (схваченная + выделенная)",		ImGuiCol_ScrollbarGrabHovered},
		{u8"Прокрутка (схваченная + активная)",			ImGuiCol_ScrollbarGrabActive},
		{u8"Ползунок",									ImGuiCol_SliderGrab},
		{u8"Ползунок (схваченный)",						ImGuiCol_SliderGrabActive},
		{u8"Кнопка",									ImGuiCol_Button},
		{u8"Кнопка (выделенная)",						ImGuiCol_ButtonHovered},
		{u8"Кнопка (активная)",							ImGuiCol_ButtonActive},
		{u8"Заголовок",									ImGuiCol_Header},
		{u8"Заголовок (выделенный)",					ImGuiCol_HeaderHovered},
		{u8"Заголовок (активный)",						ImGuiCol_HeaderActive},
		{u8"Раздилитель",								ImGuiCol_Separator},
		{u8"Раздилитель (выделенный)",					ImGuiCol_SeparatorHovered},
		{u8"Раздилитель (активный)",					ImGuiCol_SeparatorActive},
		{u8"Вкладка",									ImGuiCol_Tab},
		{u8"Вкладка (выделенная)",						ImGuiCol_TabHovered},
		{u8"Вкладка (выбранная)",						ImGuiCol_TabSelected},
		{u8"Полоска вкладки (выбранная)",				ImGuiCol_TabSelectedOverline},
		{u8"Затемнённая вкладка",						ImGuiCol_TabDimmed},
		{u8"Затемнённая вкладка (выбранная)",			ImGuiCol_TabDimmedSelected},
		{u8"Затемнённая полоска вкладки (выбранная)",	ImGuiCol_TabDimmedSelectedOverline},
		{u8"Изменение размеров",						ImGuiCol_ResizeGrip},
		{u8"Изменение размеров (выделенная)",			ImGuiCol_ResizeGripHovered},
		{u8"Изменение размеров (активная)",				ImGuiCol_ResizeGripActive},
		{u8"Заголовок таблицы (фон)",					ImGuiCol_TableHeaderBg},
		{u8"Толстые границы таблицы",					ImGuiCol_TableBorderStrong},
		{u8"Тонкие границы таблицы",					ImGuiCol_TableBorderLight},
		{u8"Фон нечётных строк таблицы",				ImGuiCol_TableRowBg},
		{u8"Фон чётных строк таблицы",					ImGuiCol_TableRowBgAlt},
		{u8"Пространство",								ImGuiCol_DockingEmptyBg},
	};

}

BaseColors::~BaseColors() {

}


std::vector<NamedColor> BaseColors::GetDefaultLightColors() {
	std::vector<NamedColor> colors = {
	NamedColor{u8"Текст",									ImColor(52,24,0,255)},
	NamedColor{u8"Текст ссылки",							ImColor(82,184,221,255)},
	NamedColor{u8"Текст (не активный)",						ImColor(152,135,113,255)},
	NamedColor{u8"Текст (выбранный)",						ImColor(250,176,66,89)},
	NamedColor{u8"Окно (фон)",								ImColor(210,198,174,255)},
	NamedColor{u8"Окно дочернее (фон)",						ImColor(0,0,0,0)},
	NamedColor{u8"Онко всплывающее (фон)",					ImColor(235,220,199,255)},
	NamedColor{u8"Граница",									ImColor(79,56,0,255)},
	NamedColor{u8"Граница (тень)",							ImColor(0,0,0,0)},
	NamedColor{u8"Рамка",									ImColor(247,237,212,255)},
	NamedColor{u8"Рамка (выделенная)",						ImColor(250,176,66,102)},
	NamedColor{u8"Рамка (активная)",						ImColor(234,175,61,171)},
	NamedColor{u8"Название (фон)",							ImColor(234,221,190,255)},
	NamedColor{u8"Название активное (фон)",					ImColor(177,165,138,255)},
	NamedColor{u8"Название свёрнутое (фон)",				ImColor(211,200,176,130)},
	NamedColor{u8"Строка меню (фон)",						ImColor(215,205,182,255)},
	NamedColor{u8"Галочка (checkbox)",						ImColor(116,100,67,255)},
	NamedColor{u8"Прокрутка (фон)",							ImColor(255,239,218,135)},
	NamedColor{u8"Прокрутка (схваченная)",					ImColor(182,168,151,204)},
	NamedColor{u8"Прокрутка (схваченная + выделенная)",		ImColor(125,116,99,204)},
	NamedColor{u8"Прокрутка (схваченная + активная)",		ImColor(125,109,83,255)},
	NamedColor{u8"Ползунок",								ImColor(250,191,66,199)},
	NamedColor{u8"Ползунок (схваченный)",					ImColor(204,176,117,153)},
	NamedColor{u8"Кнопка",									ImColor(250,191,66,102)},
	NamedColor{u8"Кнопка (выделенная)",						ImColor(250,183,66,255)},
	NamedColor{u8"Кнопка (активная)",						ImColor(250,165,15,255)},
	NamedColor{u8"Заголовок",								ImColor(250,172,66,79)},
	NamedColor{u8"Заголовок (выделенный)",					ImColor(250,179,66,204)},
	NamedColor{u8"Заголовок (активный)",					ImColor(250,183,66,255)},
	NamedColor{u8"Раздилитель",								ImColor(97,84,67,158)},
	NamedColor{u8"Раздилитель (выделенный)",				ImColor(204,133,36,199)},
	NamedColor{u8"Раздилитель (активный)",					ImColor(204,133,36,255)},
	NamedColor{u8"Вкладка",									ImColor(216,205,189,237)},
	NamedColor{u8"Вкладка (выделенная)",					ImColor(250,176,66,204)},
	NamedColor{u8"Вкладка (выбранная)",						ImColor(224,198,154,255)},
	NamedColor{u8"Полоска вкладки (выбранная)",				ImColor(250,187,66,255)},
	NamedColor{u8"Затемнённая вкладка",						ImColor(237,227,206,252)},
	NamedColor{u8"Затемнённая вкладка (выбранная)",			ImColor(232,216,189,255)},
	NamedColor{u8"Затемнённая полоска вкладки (выбранная)",	ImColor(255,183,66,255)},
	NamedColor{u8"Изменение размеров",						ImColor(87,80,68,43)},
	NamedColor{u8"Изменение размеров (выделенная)",			ImColor(250,179,66,171)},
	NamedColor{u8"Изменение размеров (активная)",			ImColor(250,179,66,242)},
	NamedColor{u8"Заголовок таблицы (фон)",					ImColor(250,230,199,255)},
	NamedColor{u8"Толстые границы таблицы",					ImColor(163,156,145,255)},
	NamedColor{u8"Тонкие границы таблицы",					ImColor(189,184,173,255)},
	NamedColor{u8"Фон нечётных строк таблицы",				ImColor(0,0,0,0)},
	NamedColor{u8"Фон чётных строк таблицы",				ImColor(97,54,0,23)},
	NamedColor{u8"Пространство",							ImColor(49,31,8,255)}
	};
	return colors;

}
std::vector<NamedColor> BaseColors::GetDefaultDarkColors() {

	std::vector<NamedColor> colors = {
		{u8"Текст",										ImColor(1.00f, 1.00f, 1.00f, 1.00f)},
		{u8"Текст ссылки",								ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Текст (не активный)",						ImColor(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"Текст (выбранный)",							ImColor(0.26f, 0.59f, 0.98f, 0.35f)},
		{u8"Окно (фон)",								ImColor(0.06f, 0.06f, 0.06f, 0.94f)},
		{u8"Окно дочернее (фон)",						ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Онко всплывающее (фон)",					ImColor(0.08f, 0.08f, 0.08f, 0.94f)},
		{u8"Граница",									ImColor(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"Граница (тень)",							ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Рамка",										ImColor(0.16f, 0.29f, 0.48f, 0.54f)},
		{u8"Рамка (выделенная)",						ImColor(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"Рамка (активная)",							ImColor(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"Название (фон)",							ImColor(0.04f, 0.04f, 0.04f, 1.00f)},
		{u8"Название активное (фон)",					ImColor(0.16f, 0.29f, 0.48f, 1.00f)},
		{u8"Название свёрнутое (фон)",					ImColor(0.00f, 0.00f, 0.00f, 0.51f)},
		{u8"Строка меню (фон)",							ImColor(0.14f, 0.14f, 0.14f, 1.00f)},
		{u8"Галочка (checkbox)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Прокрутка (фон)",							ImColor(0.02f, 0.02f, 0.02f, 0.53f)},
		{u8"Прокрутка (схваченная)",					ImColor(0.31f, 0.31f, 0.31f, 1.00f)},
		{u8"Прокрутка (схваченная + выделенная)",		ImColor(0.41f, 0.41f, 0.41f, 1.00f)},
		{u8"Прокрутка (схваченная + активная)",			ImColor(0.51f, 0.51f, 0.51f, 1.00f)},
		{u8"Ползунок",									ImColor(0.24f, 0.52f, 0.88f, 1.00f)},
		{u8"Ползунок (схваченный)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Кнопка",									ImColor(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"Кнопка (выделенная)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Кнопка (активная)",							ImColor(0.06f, 0.53f, 0.98f, 1.00f)},
		{u8"Заголовок",									ImColor(0.26f, 0.59f, 0.98f, 0.31f)},
		{u8"Заголовок (выделенный)",					ImColor(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"Заголовок (активный)",						ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Раздилитель",								ImColor(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"Раздилитель (выделенный)",					ImColor(0.10f, 0.40f, 0.75f, 0.78f)},
		{u8"Раздилитель (активный)",					ImColor(0.10f, 0.40f, 0.75f, 1.00f)},
		{u8"Вкладка",									ImColor(0.18f, 0.35f, 0.58f, 0.86f)},
		{u8"Вкладка (выделенная)",						ImColor(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"Вкладка (выбранная)",						ImColor(0.20f, 0.41f, 0.68f, 1.00f)},
		{u8"Полоска вкладки (выбранная)",				ImColor(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Затемнённая вкладка",						ImColor(0.07f, 0.10f, 0.15f, 0.97f)},
		{u8"Затемнённая вкладка (выбранная)",			ImColor(0.14f, 0.26f, 0.42f, 1.00f)},
		{u8"Затемнённая полоска вкладки (выбранная)",	ImColor(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"Изменение размеров",						ImColor(0.26f, 0.59f, 0.98f, 0.20f)},
		{u8"Изменение размеров (выделенная)",			ImColor(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"Изменение размеров (активная)",				ImColor(0.26f, 0.59f, 0.98f, 0.95f)},
		{u8"Заголовок таблицы (фон)",					ImColor(0.19f, 0.19f, 0.20f, 1.00f)},
		{u8"Толстые границы таблицы",					ImColor(0.31f, 0.31f, 0.35f, 1.00f)},
		{u8"Тонкие границы таблицы",					ImColor(0.23f, 0.23f, 0.25f, 1.00f)},
		{u8"Фон нечётных строк таблицы",				ImColor(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Фон чётных строк таблицы",					ImColor(1.00f, 1.00f, 1.00f, 0.06f)},
		{u8"Пространство",								ImColor(0.20f, 0.20f, 0.20f, 1.00f)},
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