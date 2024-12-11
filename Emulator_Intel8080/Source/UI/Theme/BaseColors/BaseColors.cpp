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
	NamedColor{u8"Текст",									ImVec4(0.00f, 0.00f, 0.00f, 1.00f)},
	NamedColor{u8"Текст ссылки",							ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"Текст (не активный)",						ImVec4(0.60f, 0.60f, 0.60f, 1.00f)},
	NamedColor{u8"Текст (выбранный)",						ImVec4(0.26f, 0.59f, 0.98f, 0.35f)},
	NamedColor{u8"Окно (фон)",								ImVec4(0.94f, 0.94f, 0.94f, 1.00f)},
	NamedColor{u8"Окно дочернее (фон)",						ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"Онко всплывающее (фон)",					ImVec4(1.00f, 1.00f, 1.00f, 0.98f)},
	NamedColor{u8"Граница",									ImVec4(0.00f, 0.00f, 0.00f, 0.30f)},
	NamedColor{u8"Граница (тень)",							ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"Рамка",									ImVec4(1.00f, 1.00f, 1.00f, 1.00f)},
	NamedColor{u8"Рамка (выделенная)",						ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
	NamedColor{u8"Рамка (активная)",						ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
	NamedColor{u8"Название (фон)",							ImVec4(0.96f, 0.96f, 0.96f, 1.00f)},
	NamedColor{u8"Название активное (фон)",					ImVec4(0.82f, 0.82f, 0.82f, 1.00f)},
	NamedColor{u8"Название свёрнутое (фон)",				ImVec4(1.00f, 1.00f, 1.00f, 0.51f)},
	NamedColor{u8"Строка меню (фон)",						ImVec4(0.86f, 0.86f, 0.86f, 1.00f)},
	NamedColor{u8"Галочка (checkbox)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"Прокрутка (фон)",							ImVec4(0.98f, 0.98f, 0.98f, 0.53f)},
	NamedColor{u8"Прокрутка (схваченная)",					ImVec4(0.69f, 0.69f, 0.69f, 0.80f)},
	NamedColor{u8"Прокрутка (схваченная + выделенная)",		ImVec4(0.49f, 0.49f, 0.49f, 0.80f)},
	NamedColor{u8"Прокрутка (схваченная + активная)",		ImVec4(0.49f, 0.49f, 0.49f, 1.00f)},
	NamedColor{u8"Ползунок",								ImVec4(0.26f, 0.59f, 0.98f, 0.78f)},
	NamedColor{u8"Ползунок (схваченный)",					ImVec4(0.46f, 0.54f, 0.80f, 0.60f)},
	NamedColor{u8"Кнопка",									ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
	NamedColor{u8"Кнопка (выделенная)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"Кнопка (активная)",						ImVec4(0.06f, 0.53f, 0.98f, 1.00f)},
	NamedColor{u8"Заголовок",								ImVec4(0.26f, 0.59f, 0.98f, 0.31f)},
	NamedColor{u8"Заголовок (выделенный)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
	NamedColor{u8"Заголовок (активный)",					ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"Раздилитель",								ImVec4(0.39f, 0.39f, 0.39f, 0.62f)},
	NamedColor{u8"Раздилитель (выделенный)",				ImVec4(0.14f, 0.44f, 0.80f, 0.78f)},
	NamedColor{u8"Раздилитель (активный)",					ImVec4(0.14f, 0.44f, 0.80f, 1.00f)},
	NamedColor{u8"Вкладка",									ImVec4(0.76f, 0.80f, 0.84f, 0.93f)},
	NamedColor{u8"Вкладка (выделенная)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
	NamedColor{u8"Вкладка (выбранная)",						ImVec4(0.60f, 0.73f, 0.88f, 1.00f)},
	NamedColor{u8"Полоска вкладки (выбранная)",				ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
	NamedColor{u8"Затемнённая вкладка",						ImVec4(0.92f, 0.93f, 0.94f, 0.99f)},
	NamedColor{u8"Затемнённая вкладка (выбранная)",			ImVec4(0.74f, 0.82f, 0.91f, 1.00f)},
	NamedColor{u8"Затемнённая полоска вкладки (выбранная)",	ImVec4(0.26f, 0.59f, 1.00f, 1.00f)},
	NamedColor{u8"Изменение размеров",						ImVec4(0.35f, 0.35f, 0.35f, 0.17f)},
	NamedColor{u8"Изменение размеров (выделенная)",			ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
	NamedColor{u8"Изменение размеров (активная)",			ImVec4(0.26f, 0.59f, 0.98f, 0.95f)},
	NamedColor{u8"Заголовок таблицы (фон)",					ImVec4(0.78f, 0.87f, 0.98f, 1.00f)},
	NamedColor{u8"Толстые границы таблицы",					ImVec4(0.57f, 0.57f, 0.64f, 1.00f)},
	NamedColor{u8"Тонкие границы таблицы",					ImVec4(0.68f, 0.68f, 0.74f, 1.00f)},
	NamedColor{u8"Фон нечётных строк таблицы",				ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
	NamedColor{u8"Фон чётных строк таблицы",				ImVec4(0.30f, 0.30f, 0.30f, 0.09f)},
	NamedColor{u8"Пространство",							ImVec4(0.20f, 0.20f, 0.20f, 1.00f)}
	};
	return colors;

}
std::vector<NamedColor> BaseColors::GetDefaultDarkColors() {

	std::vector<NamedColor> colors = {
		{u8"Текст",										ImVec4(1.00f, 1.00f, 1.00f, 1.00f)},
		{u8"Текст ссылки",								ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Текст (не активный)",						ImVec4(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"Текст (выбранный)",							ImVec4(0.26f, 0.59f, 0.98f, 0.35f)},
		{u8"Окно (фон)",								ImVec4(0.06f, 0.06f, 0.06f, 0.94f)},
		{u8"Окно дочернее (фон)",						ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Онко всплывающее (фон)",					ImVec4(0.08f, 0.08f, 0.08f, 0.94f)},
		{u8"Граница",									ImVec4(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"Граница (тень)",							ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Рамка",										ImVec4(0.16f, 0.29f, 0.48f, 0.54f)},
		{u8"Рамка (выделенная)",						ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"Рамка (активная)",							ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"Название (фон)",							ImVec4(0.04f, 0.04f, 0.04f, 1.00f)},
		{u8"Название активное (фон)",					ImVec4(0.16f, 0.29f, 0.48f, 1.00f)},
		{u8"Название свёрнутое (фон)",					ImVec4(0.00f, 0.00f, 0.00f, 0.51f)},
		{u8"Строка меню (фон)",							ImVec4(0.14f, 0.14f, 0.14f, 1.00f)},
		{u8"Галочка (checkbox)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Прокрутка (фон)",							ImVec4(0.02f, 0.02f, 0.02f, 0.53f)},
		{u8"Прокрутка (схваченная)",					ImVec4(0.31f, 0.31f, 0.31f, 1.00f)},
		{u8"Прокрутка (схваченная + выделенная)",		ImVec4(0.41f, 0.41f, 0.41f, 1.00f)},
		{u8"Прокрутка (схваченная + активная)",			ImVec4(0.51f, 0.51f, 0.51f, 1.00f)},
		{u8"Ползунок",									ImVec4(0.24f, 0.52f, 0.88f, 1.00f)},
		{u8"Ползунок (схваченный)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Кнопка",									ImVec4(0.26f, 0.59f, 0.98f, 0.40f)},
		{u8"Кнопка (выделенная)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Кнопка (активная)",							ImVec4(0.06f, 0.53f, 0.98f, 1.00f)},
		{u8"Заголовок",									ImVec4(0.26f, 0.59f, 0.98f, 0.31f)},
		{u8"Заголовок (выделенный)",					ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"Заголовок (активный)",						ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Раздилитель",								ImVec4(0.43f, 0.43f, 0.50f, 0.50f)},
		{u8"Раздилитель (выделенный)",					ImVec4(0.10f, 0.40f, 0.75f, 0.78f)},
		{u8"Раздилитель (активный)",					ImVec4(0.10f, 0.40f, 0.75f, 1.00f)},
		{u8"Вкладка",									ImVec4(0.18f, 0.35f, 0.58f, 0.86f)},
		{u8"Вкладка (выделенная)",						ImVec4(0.26f, 0.59f, 0.98f, 0.80f)},
		{u8"Вкладка (выбранная)",						ImVec4(0.20f, 0.41f, 0.68f, 1.00f)},
		{u8"Полоска вкладки (выбранная)",				ImVec4(0.26f, 0.59f, 0.98f, 1.00f)},
		{u8"Затемнённая вкладка",						ImVec4(0.07f, 0.10f, 0.15f, 0.97f)},
		{u8"Затемнённая вкладка (выбранная)",			ImVec4(0.14f, 0.26f, 0.42f, 1.00f)},
		{u8"Затемнённая полоска вкладки (выбранная)",	ImVec4(0.50f, 0.50f, 0.50f, 1.00f)},
		{u8"Изменение размеров",						ImVec4(0.26f, 0.59f, 0.98f, 0.20f)},
		{u8"Изменение размеров (выделенная)",			ImVec4(0.26f, 0.59f, 0.98f, 0.67f)},
		{u8"Изменение размеров (активная)",				ImVec4(0.26f, 0.59f, 0.98f, 0.95f)},
		{u8"Заголовок таблицы (фон)",					ImVec4(0.19f, 0.19f, 0.20f, 1.00f)},
		{u8"Толстые границы таблицы",					ImVec4(0.31f, 0.31f, 0.35f, 1.00f)},
		{u8"Тонкие границы таблицы",					ImVec4(0.23f, 0.23f, 0.25f, 1.00f)},
		{u8"Фон нечётных строк таблицы",				ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		{u8"Фон чётных строк таблицы",					ImVec4(1.00f, 1.00f, 1.00f, 0.06f)},
		{u8"Пространство",								ImVec4(0.20f, 0.20f, 0.20f, 1.00f)},
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