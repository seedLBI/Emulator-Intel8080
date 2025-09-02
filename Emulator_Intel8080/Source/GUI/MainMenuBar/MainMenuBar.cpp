#include "MainMenuBar.h"

MainMenuBar::MainMenuBar(
	OpenGL_WindowManager* openglWindowManager,
	I8080_WidgetManager* widgetManager,
	LastPathManager* lastPathManager,
	Setting* setting,
	ProjectManager* projectManager,
	WindowManager* windowManager,
	KeyCombinationHandler* keyCombinationHandler,
	EmulationControls* emulationControls,
	EmulationThread* emulationThread,
	I8080_WorkspaceManager* WorkspaceManager,
	I8080* processor) : IThemeLoadable(u8"Главное меню") {

	this->openglWindowManager = openglWindowManager;
	this->widgetManager = widgetManager;
	this->lastPathManager = lastPathManager;
	this->setting = setting;
	this->projectManager = projectManager;
	this->windowManager = windowManager;
	this->keyCombinationHandler = keyCombinationHandler;
	this->emulationControls = emulationControls;
	this->emulationThread = emulationThread;
	this->processor = processor;
	this->WorkspaceManager = WorkspaceManager;
		

	window = openglWindowManager->GetMainWindow()->GetHandle();
	authorPopup = new AuthorPopup(window);
	LoadIcon();

	IThemeLoadable::InitListWord(
		{
			u8"Логотип"
		});


}

MainMenuBar::~MainMenuBar() {

}

void MainMenuBar::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"Логотип")
			colorLogo = object_colors.colors[i].color;
	}
}
std::vector<NamedColor> MainMenuBar::GetDefaultLightColors() {
	return {
		{ u8"Логотип",ImColor(237, 168, 79,255) }
	};
}
std::vector<NamedColor> MainMenuBar::GetDefaultDarkColors() {
	return {
		{ u8"Логотип",ImColor(0.476, 0.631, 0.820, 1.f) }
	};
}


void MainMenuBar::Draw() {

	authorPopup->Draw();

	titleButtonRects.clear();

	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 7));


	Draw_MainMenu();


	ImGui::PopStyleVar();

	Draw_SecondaryMenu();

	ImGui::PopStyleColor();

	//Draw_DownMenu();

}

void MainMenuBar::Draw_MainMenu() {
	if (ImGui::BeginMainMenuBar()) {

		menuBarPos = ImGui::GetWindowPos();
		menuBarSize = ImGui::GetWindowSize();


		DrawLogo();

		ImGui::PopStyleColor();

		Draw_MainMenu_File();
		Draw_MainMenu_View();
		Draw_MainMenu_Emulator();
		Draw_MainMenu_Setting();
		Draw_MainMenu_About();

		Draw_ProjectMode();
		Draw_Speedometer();


		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));

		DrawWindowButtons();



		ImGui::EndMainMenuBar();
	}
}
void MainMenuBar::Draw_SecondaryMenu() {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
	float height = ImGui::GetFrameHeight();



	if (ImGui::BeginViewportSideBar("##SecondaryMenuBar", NULL, ImGuiDir_Up, height, window_flags)) {
		if (ImGui::BeginMenuBar()) {


			ImGui::Dummy(ImVec2(20.f, 0.f));

			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_MenuBarBg));


			if (ImGui::Button(ICON_FA_FILE_CIRCLE_PLUS, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 4, 0))) {
				projectManager->NewFile();
			}
			PushSizeButtonIntoList();
			if (ImGui::Button(ICON_FA_FOLDER_OPEN, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 4, 0))) {
				projectManager->OpenFile();
			}
			PushSizeButtonIntoList();
			if (ImGui::Button(ICON_FA_FLOPPY_DISK, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 4, 0))) {
				projectManager->SaveFile();
			}
			PushSizeButtonIntoList();

			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical,2.f);
			
			const char* text_compile_button = std::string("  " + std::string(ICON_FA_MICROCHIP) + u8" Компилировать   ").c_str();
			if (ImGui::Button(text_compile_button, ImVec2(ImGui::CalcTextSize(text_compile_button).x, 0))) {
				projectManager->Compile();
			}
			PushSizeButtonIntoList();

			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);

			if (ImGui::Button(ICON_FA_PLAY, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 5, 0)))
				emulationControls->Play();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"Начать эмуляцию");


			if (ImGui::Button(ICON_FA_STOP, ImVec2(ImGui::CalcTextSize(ICON_FA_STOP).x * 5, 0)))
				emulationControls->Stop();
			PushSizeButtonIntoList();
			if(ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"Стоп");


			if (ImGui::Button(ICON_FA_PAUSE, ImVec2(ImGui::CalcTextSize(ICON_FA_PAUSE).x * 5, 0)))
				emulationControls->Pause();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"Пауза");

			if (processor->isHistoryModeEnabled()) {
				if (ImGui::Button(ICON_FA_BACKWARD_STEP, ImVec2(ImGui::CalcTextSize(ICON_FA_BACKWARD_STEP).x * 5, 0)))
					emulationControls->Undo_step_into();
				PushSizeButtonIntoList();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(u8"Шаг назад");
			}

			if (ImGui::Button(ICON_FA_FORWARD_STEP, ImVec2(ImGui::CalcTextSize(ICON_FA_FORWARD_STEP).x * 5, 0)))
				emulationControls->Next_step_into();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"Шаг с заходом");

			if (ImGui::Button(ICON_FA_FORWARD_FAST, ImVec2(ImGui::CalcTextSize(ICON_FA_FORWARD_FAST).x * 5, 0)))
				emulationControls->Next_step_over();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"Шаг с обходом");


			ImGui::PopStyleColor();


			ImGuiWindow* wind = nullptr;

			wind = ImGui::GetCurrentWindow();

			ImRect menuBar_rect = wind->MenuBarRect();
			ImGui::PushClipRect(menuBar_rect.Min, menuBar_rect.Max, false);

			float width = 220.f;
			ImGui::SetCursorPos(ImVec2(menuBar_rect.Max.x - width, 0.0f));
			const char* types_Workspace[2] = { u8"Стандартное",u8"Все команды" };
			ImGui::PushItemWidth(200.f);

			ImGuiContext& g = *GImGui;
			ImDrawList* draw_list = ImGui::GetForegroundDrawList();
			ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();
			const ImGuiStyle& style = g.Style;


			const ImU32 col = ImColor(ImVec4(1.f, 1.f, 1.f, 1.f));

			if (ImGui::BeginCombo("combo_workspace", WorkspaceManager->GetNameCurrentWorkspace().c_str(), ImGuiComboFlags_NoLabel)) {
				WorkspaceManager->Draw();

				ImGui::EndCombo();
			}
			PushSizeButtonIntoList();

			ImGui::PopItemWidth();

			width += ImGui::CalcTextSize(u8"Рабочее пространство").x * 1.05f;


			ImGui::SetCursorPos(ImVec2(menuBar_rect.Max.x - width, 0.0f));
			ImGui::Text(u8"Рабочее пространство");


			ImGui::PopClipRect();


			ImGui::EndMenuBar();
		}
	}

	ImGui::End();



}
void MainMenuBar::Draw_DownMenu() {

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
	float height = ImGui::GetFrameHeight();


	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
	if (ImGui::BeginViewportSideBar("##MainStatusBar", NULL, ImGuiDir_Down, height, window_flags)) {
		if (ImGui::BeginMenuBar()) {


			ImGui::Text(u8"Фоновые задачи не выполняются");


			ImGui::EndMenuBar();
		}
	}
	ImGui::End();

	ImGui::PopStyleColor();
}

void MainMenuBar::Draw_ProjectMode() {
	const char* tooltip = u8"Режим работы с загруженным файлом:\n\n* USER - пользователю доступно всё.\n\n* BIN - отключен редактор и компиляция.\n\n* COM - отключен редактор и компиляция.\nPC установливается в 0x0100 и внедряется несколько\nбайт в начало программы для реализации функций вывода CP/M.";
	TextWithTooltipInMainMenuBar(ModeProject_To_Str(processor->GetModeProject()).c_str(), tooltip);

}

void MainMenuBar::Draw_Speedometer() {
	emulationThread->DrawMainMenu();
}

void MainMenuBar::DrawLogo() {

	const float frameHeight = ImGui::GetFrameHeight();
	ImGui::SetCursorPosX(ImGui::GetStyle().ItemSpacing.x * 0.5f);
	ImGui::Image((ImTextureID)icon_logo.GetID(), ImVec2(frameHeight, frameHeight), ImVec2(0, 1), ImVec2(1, 0), colorLogo, ImVec4(0, 0, 0, 0));

	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.x);

}

void MainMenuBar::PushSizeButtonIntoList() {
	titleButtonRects.push_back(ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()));
}

void MainMenuBar::DrawWindowButtons() {
	ImGuiStyle& style = ImGui::GetStyle();
	float windowWidth = ImGui::GetWindowWidth();
	float buttonWidth = 60.0f;
	float spacing = style.ItemSpacing.x;
	float paddingRight = style.WindowPadding.x;
	float totalWidth = 3 * buttonWidth;

	// выравниваем блок кнопок по правому краю
	ImGui::SetCursorPosX(windowWidth - totalWidth);

	// сохраняем текущие цвета кнопки
	ImVec4 colBtn = style.Colors[ImGuiCol_Button];
	ImVec4 colBtnHover = style.Colors[ImGuiCol_ButtonHovered];
	ImVec4 colBtnActive = style.Colors[ImGuiCol_ButtonActive];

	// делаем «фон» кнопок таким же, как фон окна (невидимыми)
	ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_MenuBarBg]);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colBtnHover);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, colBtnActive);

	const ImVec2 buttonSize = ImVec2(buttonWidth, ImGui::GetFrameHeight() - 1.f);


	// кнопки
	if (ImGui::Button(ICON_FA_MINUS, buttonSize)) {
		glfwIconifyWindow(window);
	}
	PushSizeButtonIntoList();

	ImGui::SameLine(0, 0);



	if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED)) {
		if (ImGui::Button(ICON_FA_COMPRESS, buttonSize)) {
			glfwRestoreWindow(window);
		}
	}
	else {
		if (ImGui::Button(ICON_FA_EXPAND, buttonSize)) {
			glfwMaximizeWindow(window);
		}
	}
	PushSizeButtonIntoList();

	ImGui::SameLine(0, 0);
	if (ImGui::Button(ICON_FA_XMARK, buttonSize)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	PushSizeButtonIntoList();

	// восстанавливаем старые цвета
	ImGui::PopStyleColor(3);
}

inline void MainMenuBar::Draw_MainMenu_File() {
	if (ImGui::BeginMenu(u8" Файл ")) {


		if (ImGui::MenuItem((std::string(ICON_FA_FILE) + u8" Новый файл").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Новый файл").c_str())) {
			projectManager->NewFile();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FOLDER_OPEN) + u8" Открыть").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Открыть файл").c_str())) {
			projectManager->OpenFile();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_BOX_ARCHIVE) + u8" Сохранить").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Сохранить").c_str())) {
			projectManager->SaveFile();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FILE_EXPORT) + u8" Сохранить как...").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Сохранить как").c_str())) {
			projectManager->SaveFileAs();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FOLDER_OPEN) + u8" Сохранить в бинарный файл").c_str())) {
			projectManager->SaveFileIntoBinary();
		}
		ImGui::Separator();
		if (ImGui::BeginMenu(std::string(std::string(ICON_FA_COPY) + u8" Последние проекты").c_str())) {
			if (lastPathManager->Draw()) {
				projectManager->OpenFileWithPath(lastPathManager->GetChoosedPath());
			}
			ImGui::EndMenu();
		}

		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_CIRCLE_XMARK) + u8" Выйти").c_str(),u8"Alt + F4")) {
			//ExitButton = true;
		}
		PushSizeButtonIntoList();




		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_View() {
	if (ImGui::BeginMenu(u8" Окна ")) {

		if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" Закрыть все окна").c_str()))
			widgetManager->CloseAll();

		ImGui::Separator();

		if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" Открыть все окна").c_str()))
			widgetManager->OpenAll();


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.2, 0.2, 1.0));
		ImGui::SeparatorText(u8"Основное");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_CODE) + u8" Редактор кода").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Редактор кода")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FILE_LINES) + u8" Просмотр мнемо кода").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Мнемо код")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FILE_LINES) + u8" Просмотр мнемо кода (нацеленный)").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Мнемо код (нацеленный)")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_CUBE) + u8" Hex просмотр").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Просмотр памяти")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FONT_AWESOME) + u8" Регистры и флаги").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Регистры и флаги")->GetPtrFlagShow()
		);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.6, 0.0, 1.0));
		ImGui::SeparatorText(u8"Вспомогательное");
		ImGui::PopStyleColor();
		//ImGui::MenuItem((string(ICON_FA_CODE)				+ u8" Дизассемблер").c_str(), "", widget_Disassembler->GetPtrFlagShow());
		ImGui::MenuItem(
			(std::string(ICON_FA_GAUGE_HIGH) + u8" Быстродействие").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Быстродействие")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_HIGHLIGHTER) + u8" Список маркеров").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Маркеры")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_BARS) + u8" Список переменных").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Переменные")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_HAMMER) + u8" Список постоянных").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Постоянные")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_LIST) + u8" История выполнения").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"История выполнения")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_PALETTE) + u8" Вывод всевозможных цветов").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Все цвета")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FONT) + u8" Вывод всевозможных символов").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Все символы")->GetPtrFlagShow()
		);



		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.6, 0.0, 1.0));
		ImGui::SeparatorText(u8"Внешние порты");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" Пиксельный экран").c_str(),
			"0x05",
			widgetManager->GetWidgetPtr(u8"Пиксельный экран")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" Продвинутый пиксельный экран").c_str(),
			"0x06",
			widgetManager->GetWidgetPtr(u8"Продвинутый пиксельный экран")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" Символьный экран").c_str(),
			"0x07",
			widgetManager->GetWidgetPtr(u8"Символьный экран")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_RIGHT_FROM_BRACKET) + u8" Окно вывода").c_str(),
			"0x02",
			widgetManager->GetWidgetPtr(u8"Окно вывода")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_RIGHT_TO_BRACKET) + u8" Окно ввода").c_str(),
			"0x08",
			widgetManager->GetWidgetPtr(u8"Окно ввода")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_KEYBOARD) + u8" Окно клавиатуры").c_str(),
			"0x10",
			widgetManager->GetWidgetPtr(u8"Клавиатура")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_CLOCK) + u8" Таймер").c_str(),
			"0x16",
			widgetManager->GetWidgetPtr(u8"Таймер")->GetPtrFlagShow()
		);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4, 1.0, 0.4, 1.0));
		ImGui::SeparatorText(u8"Помощь");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_BOOK_BOOKMARK) + u8" Руководство к программе").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Руководство")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_TABLE) + u8" Таблица инструкций").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"Таблица инструкций")->GetPtrFlagShow()
		);

		//ImGui::MenuItem((string(ICON_FA_LIST)				+ u8" Список инструкций").c_str(), "", widget_ListInstruction->GetPtrFlagShow());


		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_Emulator() {
	if (ImGui::BeginMenu(u8" Эмулятор ")) {

		if (ImGui::MenuItem((std::string(ICON_FA_MICROCHIP) + u8" Компилировать").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Компилировать").c_str())) {
			projectManager->Compile();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_PLAY) + u8" Запуск").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Запуск").c_str())) {
			emulationControls->Play();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_FORWARD_STEP) + u8" Шаг c заходом").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Шаг c заходом").c_str())) {
			emulationControls->Next_step_into();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_FORWARD_STEP) + u8" Шаг c обходом").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Шаг c обходом").c_str())) {
			emulationControls->Next_step_over();
		}

		if (processor->isHistoryModeEnabled()) {
			if (ImGui::MenuItem((std::string(ICON_FA_BACKWARD_STEP) + u8" Шаг назад").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Шаг назад").c_str()))
				emulationControls->Undo_step_into();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_PAUSE) + u8" Пауза").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Пауза").c_str())) {
			emulationControls->Pause();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_STOP) + u8" Стоп").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Стоп").c_str())) {
			emulationControls->Stop();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_ROTATE_RIGHT) + u8" Сбросить состояние").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Сбросить состояние").c_str())) {
			emulationControls->FullReset();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_ERASER) + u8" Удалить точки останова").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"Удалить точки останова").c_str())) {
			processor->RemoveAllBreakPoints();
		}


		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_Setting() {
	if (ImGui::MenuItem(u8" Настройки ")) {
		setting->Open();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_About() {


	if (ImGui::MenuItem(u8" О авторе ")) {
		authorPopup->Open();
	}
	PushSizeButtonIntoList();
}



bool MainMenuBar::IsPointOverTitleButton(const POINT& pt) const {
	for (const auto& r : titleButtonRects) {
		if (pt.x >= r.Min.x && pt.x < r.Max.x &&
			pt.y >= r.Min.y && pt.y < r.Max.y)
			return true;
	}
	return false;
}

void MainMenuBar::LoadIcon() {

	TextureSetting settingFlags;
	settingFlags.Min = TextureFilter::LINEAR_MIPMAP_LINEAR;
	settingFlags.Max = TextureFilter::LINEAR_MIPMAP_LINEAR;
	settingFlags.WrapX = TextureWrap::CLAMP_TO_EDGE;
	settingFlags.WrapY = TextureWrap::CLAMP_TO_EDGE;
	icon_logo.SetSetting(settingFlags);
	icon_logo.LoadTexture(logo_transparent_data.data(), (int)logo_transparent_data.size());
	icon_logo.Init();

}
