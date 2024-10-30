#include "I8080.UI.h"


I8080_UserInterface::I8080_UserInterface(GLFWwindow* window) {
	this->window = window;


	saveSystemManager = new SaveSystemManager(GetExePath() + "\\SettingData.save");

	notificationManager = new NotificationManager();
	WorkspaceManager = new I8080_WorkspaceManager(&WidgetManager);
	lastPathManager = new LastPathManager();
	

	processor = new I8080();
	Compiler = new CompilerStable();
	emulationThread = new EmulationThread(processor);

	keyCombination_handler = new KeyCombinationHandler(notificationManager);
	font_manager = new FontManager();
	window_manager = new WindowManager();


	projectManager = new ProjectManager(
		window,
		processor,
		notificationManager,
		lastPathManager,
		emulationThread,
		Compiler);


	settings = new Setting(font_manager, window_manager, WorkspaceManager, notificationManager, emulationThread, keyCombination_handler, projectManager);

	InitSaveManager();
	InitWidgets();
	InitKeyCombinationHandler();


	projectManager->InitWidgets(
		widget_MnemocodeViewer,
		widget_RegisterFlagsInfo,
		widget_CodeEditor);


	saveSystemManager->Load();

}
I8080_UserInterface::~I8080_UserInterface() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "I8080_UserInterface::~I8080_UserInterface()\n";
#endif // !WITH_DEBUG_OUTPUT

	saveSystemManager->Save();
}

void I8080_UserInterface::Draw() {
	BeginDraw();






	DrawMainMenu();

	WidgetManager.Draw();
	notificationManager->Draw();
	settings->Draw();

	authorPopup.Draw();



	//ImGui::ShowDemoWindow();

#ifdef WITH_DEBUG_OUTPUT
	ImGui::ShowDemoWindow(); // Show demo window! :)
#endif


	EndDraw();


}
void I8080_UserInterface::Update() {
	projectManager->Update();
	keyCombination_handler->Update();
	WidgetManager.Update();
	WorkspaceManager->Update();
	notificationManager->Update();
}

bool I8080_UserInterface::OpenFileFromPath(string path) {
	return projectManager->OpenFileWithPath(path);
}


void I8080_UserInterface::BeginDraw() {


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}
void I8080_UserInterface::EndDraw() {

	ImGui::EndFrame();




	font_manager->ReloadFont();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}




void I8080_UserInterface::Emulator_Play() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Play()\n";
#endif

	processor->ResetFlagStop();
	emulationThread->SetControlMode(ControlMode::Continous);


}
void I8080_UserInterface::Emulator_Pause() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Pause()\n";
#endif

	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Emulator_Stop() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Stop()\n";
#endif

	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->ActiveFlagStop();
	processor->Reset();

	//processor->RemoveAllBreakPoints();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Emulator_Next_step() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Next_step() \n";
#endif
	emulationThread->SetControlMode(ControlMode::StepByStep);
	emulationThread->WaitThread();

	//processor->ResetFlagStop();
	widget_RegisterFlagsInfo->InitLastState();
	processor->NextStep();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Emulator_FullReset() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_FullReset()\n";
#endif
	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->ActiveFlagStop();
	processor->EraseMemory();
	processor->RemoveAllBreakPoints();
	processor->Reset();
	processor->Reset();

	widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();


	projectManager->GetPtrTranslatorOutput()->Opcodes.clear();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}


void I8080_UserInterface::DrawMainMenu() {

	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* wind = nullptr;
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu((string(ICON_FA_FILE) + u8" Файл").c_str())) {
			if (ImGui::MenuItem((string(ICON_FA_FILE) + u8" Новый файл").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Новый файл").c_str())) {
				projectManager->NewFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_FOLDER_OPEN) + u8" Открыть").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Открыть файл").c_str())) {
				projectManager->OpenFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_FOLDER_OPEN) + u8" Открыть бинарный файл").c_str())) {
				projectManager->OpenBinaryFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_BOX_ARCHIVE) + u8" Сохранить").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Сохранить").c_str())) {
				projectManager->SaveFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_FILE_EXPORT) + u8" Сохранить как...").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Сохранить как").c_str())) {
				projectManager->SaveFileAs();
			}
			if (ImGui::BeginMenu(string(string(ICON_FA_COPY) + u8" Последние проекты").c_str())) {
				if (lastPathManager->Draw()) {
					OpenFileFromPath(lastPathManager->GetChoosedPath());
				}
				ImGui::EndMenu();
			}
			//if (ImGui::MenuItem(string(string(ICON_FA_FILE_IMAGE) + u8" PixelScreen to png").c_str())) {
			//	SaveImagePixelScreen();
			//}
			//if (ImGui::MenuItem(string(string(ICON_FA_FILE_LINES) + u8" Сохранить Output to txt").c_str())) {
			//	SaveConsoleOutput();
			//}
			ImGui::Separator();
			if (ImGui::MenuItem((string(ICON_FA_CIRCLE_XMARK) + u8" Выйти").c_str())) {
				ExitButton = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu((string(ICON_FA_CALCULATOR) + u8" Эмулятор").c_str())) {
			if (ImGui::MenuItem((string(ICON_FA_MICROCHIP) + u8" Компилировать").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Компилировать").c_str())  ) {
				projectManager->Compile();
			}
			ImGui::Separator();
			if (ImGui::MenuItem((string(ICON_FA_PLAY) + u8" Запуск").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Запуск").c_str())) {
				Emulator_Play();
			}

			if (ImGui::MenuItem((string(ICON_FA_FORWARD_STEP) + u8" Шаг вперёд").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Шаг вперёд").c_str())) {
				Emulator_Next_step();
			}
			if (ImGui::MenuItem((string(ICON_FA_PAUSE) + u8" Пауза").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Пауза").c_str())) {
				Emulator_Pause();
			}
			if (ImGui::MenuItem((string(ICON_FA_STOP) + u8" Стоп").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Стоп").c_str())) {
				Emulator_Stop();
			}
			ImGui::Separator();
			if (ImGui::MenuItem((string(ICON_FA_ROTATE_RIGHT) + u8" Сбросить состояние").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Сбросить состояние").c_str())) {
				Emulator_FullReset();
			}
			if (ImGui::MenuItem((string(ICON_FA_ERASER) + u8" Удалить точки останова").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Удалить точки останова").c_str())) {
				processor->RemoveAllBreakPoints();
			}
			ImGui::Separator();

			if (ImGui::MenuItem((string(ICON_FA_GEAR) + u8" Настройки").c_str(), keyCombination_handler->GetStrCombinationByName(u8"Настройки").c_str())) {
				settings->Open();
			}



			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu((string(ICON_FA_WINDOW_RESTORE) + u8" Окна").c_str())) {


			if (ImGui::MenuItem(std::string(string(ICON_FA_WINDOW_RESTORE) + u8" Открыть\\Закрыть все окна").c_str())) {
				if (WidgetManager.GetFlag_AllOpened())
					WidgetManager.CloseAll();
				else
					WidgetManager.OpenAll();
			}

			ImGui::Separator();

			ImGui::MenuItem((string(ICON_FA_CODE) + u8" Редактор кода").c_str(), "", widget_CodeEditor->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_FILE_LINES) + u8" Просмотр мнемо кода").c_str(), "", widget_MnemocodeViewer->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_CUBE) + u8" Hex просмотр").c_str(), "", widget_HexViewer->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Пиксельный экран (0x05)").c_str(), "", widget_PixelScreen->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Продвинутый пиксельный экран (0x06)").c_str(), "", widget_PixelScreenTwoBuffers->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Символьный экран (0x07)").c_str(), "", widget_SymbolScreen->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_CLOCK) + u8" Таймер (0x16)").c_str(), "", widget_timer->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_RIGHT_FROM_BRACKET) + u8" Окно вывода (0x02)").c_str(), "", widget_output0x02->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_RIGHT_TO_BRACKET) + u8" Окно ввода (0x08)").c_str(), "", widget_input0x08->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_KEYBOARD) + u8" Окно клавиатуры (0x10)").c_str(), "", widget_keyboard->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_PALETTE) + u8" Вывод всевозможных цветов").c_str(), "", widget_ColorPicker->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_FONT) + u8" Вывод всевозможных символов").c_str(), "", widget_SymbolPicker->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_FONT_AWESOME) + u8" Регистры и флаги").c_str(), "", widget_RegisterFlagsInfo->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_GAUGE_HIGH) + u8" Быстродействие").c_str(), "", widget_EmulatorInfo->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_HIGHLIGHTER) + u8" Список маркеров").c_str(), "", widget_MarkerList->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_BARS) + u8" Список переменных").c_str(), "", widget_VarList->GetPtrFlagShow());
			ImGui::MenuItem((string(ICON_FA_HAMMER) + u8" Список постоянных").c_str(), "", widget_ConstList->GetPtrFlagShow());

			ImGui::MenuItem((string(ICON_FA_CODE) + u8" Дизассемблер").c_str(), "", widget_Disassembler->GetPtrFlagShow());

			ImGui::MenuItem((string(ICON_FA_BOOK_BOOKMARK) + u8" Руководство к программе").c_str(), "", widget_Help->GetPtrFlagShow());


			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu((string(ICON_FA_LIFE_RING) + u8" Помощь").c_str())) {

			if (ImGui::MenuItem((string(ICON_FA_ADDRESS_CARD) + u8" О авторе...").c_str())) {
				authorPopup.Open();
			}

			/*
			if (ImGui::MenuItem((string(ICON_FA_CIRCLE_INFO) + u8" О программе...").c_str())) {

			}
			if (ImGui::BeginMenu((string(ICON_FA_BOOK_BOOKMARK) + u8" Примеры программ").c_str())) {
				ImGui::MenuItem(u8"1. Переменные");
				ImGui::MenuItem(u8"2. Сложение и вычитание");
				ImGui::MenuItem(u8"3. Сравнение");
				ImGui::MenuItem(u8"4. Массивы");
				ImGui::MenuItem(u8"5. Циклы");
				ImGui::MenuItem(u8"6. Вывод");
				ImGui::MenuItem(u8"7. Ввод");
				ImGui::MenuItem(u8"8. Работа с символьным экраном");
				ImGui::MenuItem(u8"9. Работа с пиксельным экраном");
				ImGui::MenuItem(u8"10. Работа с таймером");
				ImGui::MenuItem(u8"11. Работа с генератором");
				ImGui::MenuItem(u8"12. Работа с памятью");


				ImGui::EndMenu();
			}
			if (ImGui::MenuItem((string(ICON_FA_ARROWS_ROTATE) + u8" Проверить обновления").c_str())) {

			}
			*/


			ImGui::EndMenu();
		}




		if (ImGui::Button(ICON_FA_PLAY, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 4, 0)))
			Emulator_Play();

		if (ImGui::Button(ICON_FA_PAUSE, ImVec2(ImGui::CalcTextSize(ICON_FA_PAUSE).x * 4, 0)))
			Emulator_Pause();

		if (ImGui::Button(ICON_FA_STOP, ImVec2(ImGui::CalcTextSize(ICON_FA_STOP).x * 4, 0)))
			Emulator_Stop();

		if (ImGui::Button(ICON_FA_FORWARD_STEP, ImVec2(ImGui::CalcTextSize(ICON_FA_FORWARD_STEP).x * 4, 0)))
			Emulator_Next_step();


		{
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
			ImGui::PopItemWidth();

			width += ImGui::CalcTextSize(u8"Рабочее пространство").x * 1.05;


			ImGui::SetCursorPos(ImVec2(menuBar_rect.Max.x - width, 0.0f));
			ImGui::Text(u8"Рабочее пространство");


			ImGui::PopClipRect();
		}
		ImGui::EndMainMenuBar();
	}
}




void I8080_UserInterface::InitWidgets() {
	widget_CodeEditor = new Widget_CodeEditor();
	widget_Disassembler = new Widget_Disassembler(processor);
	widget_ColorPicker = new Widget_ColorPicker(widget_CodeEditor->GetPtrTextEditor());
	widget_SymbolPicker = new Widget_SymbolPicker(widget_CodeEditor->GetPtrTextEditor());
	widget_SymbolScreen = new Widget_SymbolScreen(processor);
	widget_PixelScreen = new Widget_PixelScreen(processor);
	widget_PixelScreenTwoBuffers = new Widget_PixelScreenTwoBuffers(processor);
	widget_input0x08 = new Widget_Input0x08(processor);
	widget_keyboard = new Widget_Keyboard(widget_CodeEditor->GetPtrTextEditor());
	widget_output0x02 = new Widget_Output0x02(processor);
	widget_timer = new Widget_Timer(processor);
	widget_HexViewer = new Widget_HexViewer(processor, projectManager->GetPtrTranslatorOutput());
	widget_MnemocodeViewer = new Widget_MnemocodeViewer(processor, projectManager->GetPtrTranslatorOutput());
	widget_RegisterFlagsInfo = new Widget_RegisterFlagsInfo(processor);
	widget_EmulatorInfo = new Widget_EmulatorInfo(processor);
	widget_MarkerList = new Widget_MarkerList(processor, projectManager->GetPtrTranslatorOutput(), widget_MnemocodeViewer);
	widget_VarList = new Widget_VarList(processor, projectManager->GetPtrTranslatorOutput());
	widget_ConstList = new Widget_ConstList(projectManager->GetPtrTranslatorOutput());
	widget_Help = new Widget_Help();

	WidgetManager.AddWidgetPtr(widget_Help);
	WidgetManager.AddWidgetPtr(widget_Disassembler);
	WidgetManager.AddWidgetPtr(widget_ColorPicker);
	WidgetManager.AddWidgetPtr(widget_SymbolPicker);
	WidgetManager.AddWidgetPtr(widget_SymbolScreen);
	WidgetManager.AddWidgetPtr(widget_PixelScreen);
	WidgetManager.AddWidgetPtr(widget_PixelScreenTwoBuffers);
	WidgetManager.AddWidgetPtr(widget_input0x08);
	WidgetManager.AddWidgetPtr(widget_keyboard);
	WidgetManager.AddWidgetPtr(widget_output0x02);
	WidgetManager.AddWidgetPtr(widget_timer);
	WidgetManager.AddWidgetPtr(widget_CodeEditor);
	WidgetManager.AddWidgetPtr(widget_HexViewer);
	WidgetManager.AddWidgetPtr(widget_MnemocodeViewer);
	WidgetManager.AddWidgetPtr(widget_RegisterFlagsInfo);
	WidgetManager.AddWidgetPtr(widget_EmulatorInfo);
	WidgetManager.AddWidgetPtr(widget_MarkerList);
	WidgetManager.AddWidgetPtr(widget_VarList);
	WidgetManager.AddWidgetPtr(widget_ConstList);

}
void I8080_UserInterface::InitSaveManager() {
	saveSystemManager->AddObjectPtr((SaveSystem*)settings);
	saveSystemManager->AddObjectPtr((SaveSystem*)lastPathManager);
	saveSystemManager->AddObjectPtr((SaveSystem*)WorkspaceManager);
}
void I8080_UserInterface::InitKeyCombinationHandler() {

	keyCombination_handler->AddCombination(u8"Компилировать", KeyCombination({ GLFW_KEY_F2 }, std::bind(&ProjectManager::Compile, projectManager)));
	keyCombination_handler->AddCombination(u8"Запуск", KeyCombination({ GLFW_KEY_F5 }, std::bind(&I8080_UserInterface::Emulator_Play, this)));
	keyCombination_handler->AddCombination(u8"Пауза", KeyCombination({ GLFW_KEY_F12 }, std::bind(&I8080_UserInterface::Emulator_Pause, this)));
	keyCombination_handler->AddCombination(u8"Стоп", KeyCombination({ GLFW_KEY_ESCAPE }, std::bind(&I8080_UserInterface::Emulator_Stop, this)));
	keyCombination_handler->AddCombination(u8"Шаг вперёд", KeyCombination({ GLFW_KEY_F9 }, std::bind(&I8080_UserInterface::Emulator_Next_step, this)));
	keyCombination_handler->AddCombination(u8"Сбросить состояние", KeyCombination({  }, std::bind(&I8080_UserInterface::Emulator_FullReset, this)));
	keyCombination_handler->AddCombination(u8"Удалить точки останова", KeyCombination({  }, std::bind(&I8080::RemoveAllBreakPoints, processor)));

	keyCombination_handler->AddCombination(u8"Сохранить", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_S }, std::bind(&ProjectManager::SaveFile, projectManager)));
	keyCombination_handler->AddCombination(u8"Сохранить как", KeyCombination({}, std::bind(&ProjectManager::SaveFileAs, projectManager)));

	keyCombination_handler->AddCombination(u8"Новый файл", KeyCombination({}, std::bind(&ProjectManager::NewFile, projectManager)));
	keyCombination_handler->AddCombination(u8"Открыть файл", KeyCombination({}, std::bind(&ProjectManager::OpenFile, projectManager)));

	keyCombination_handler->AddCombination(u8"Настройки", KeyCombination({}, std::bind(&Setting::Toggle, settings)));

	keyCombination_handler->AddCombination(u8"Полноэкранный\\Оконный", KeyCombination({ GLFW_KEY_F11 }, std::bind(&WindowManager::ToggleFullscreen, window_manager)));

	keyCombination_handler->AddCombination(u8"Следующее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadNext, WorkspaceManager)));
	keyCombination_handler->AddCombination(u8"Предыдущее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_LEFT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadPrevious, WorkspaceManager)));

	keyCombination_handler->AddCombination(u8"Увеличить шрифт на 1", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_EQUAL }, std::bind(&FontManager::SetOneStepBigger, font_manager)));
	keyCombination_handler->AddCombination(u8"Уменьшить шрифт на 1", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_MINUS }, std::bind(&FontManager::SetOneStepSmaller, font_manager)));

}