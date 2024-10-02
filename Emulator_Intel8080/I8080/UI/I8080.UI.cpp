#include "I8080.UI.h"


I8080_UserInterface::I8080_UserInterface(GLFWwindow* window) {
	this->window = window;

	notificationManager = new NotificationManager();
	WorkspaceManager = new I8080_WorkspaceManager(&WidgetManager);

	saveSystemManager = new SaveSystemManager(GetExePath() + "\\SettingData.save");


	processor = new I8080();
	Compiler = new CompilerStable();
	emulationThread = new EmulationThread(processor);

	keyCombination_handler = new KeyCombinationHandler();
	font_manager = new FontManager();
	window_manager = new WindowManager();
	settings = new Setting(font_manager, window_manager, notificationManager, emulationThread);


	InitWidgets();
	InitSaveManager();
	InitKeyCombinationHandler();

	saveSystemManager->Load();

}
I8080_UserInterface::~I8080_UserInterface() {
	saveSystemManager->Save();
}

void I8080_UserInterface::Draw() {
	BeginDraw();


	DrawMainMenu();

	WidgetManager.Draw();
	notificationManager->Draw();
	settings->Draw();


#ifdef WITH_DEBUG_OUTPUT
	ImGui::ShowDemoWindow(); // Show demo window! :)
#endif


	EndDraw();
}
void I8080_UserInterface::Update() {
	keyCombination_handler->Update();
	WidgetManager.Update();
	WorkspaceManager->Update();
	notificationManager->Update();
}

bool I8080_UserInterface::OpenFileFromPath(string path) {
	if (path.size() != 0) {
		LastPathManager.AddPath(path);
		//path = from_utf8(path);
		pathLoadedFile = path;
		glfwSetWindowTitle(window, (u8"Эмулятор процессора I8080 -> " + pathLoadedFile).c_str());
		InitLineCodes(path);
		TranslateCode();
		widget_CodeEditor->SetFlagWindow(0);
		processor->Reset();
		processor->LoadMemory(translator.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();

		static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Файл успешно открыт.";

		notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));


		return true;
	}
	return false;
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
	WaitThread();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Emulator_Stop() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Stop()\n";
#endif

	emulationThread->SetControlMode(ControlMode::Stop);
	WaitThread();

	processor->ActiveFlagStop();
	processor->Reset();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Emulator_Next_step() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Pressed Emulator_Next_step() \n";
#endif
	emulationThread->SetControlMode(ControlMode::StepByStep);
	WaitThread();

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
	WaitThread();

	processor->ActiveFlagStop();
	processor->EraseMemory();
	processor->Reset();
	processor->Reset();

	translator.Opcodes.clear();

	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();
}
void I8080_UserInterface::Compile() {
	TranslateCode();
	widget_MnemocodeViewer->FollowCursorPC();
}



void I8080_UserInterface::InitLineCodes(string path) {
	lines_of_code.erase(lines_of_code.begin(), lines_of_code.end());

	std::ifstream t;
	t.open(stringUTF8_to_wstring(path));
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();
	editor.SetText(str);
	editor.SetLanguageDefinition(TextEditor::LanguageDefinition::I8080());
	editor.SetTextNotChanged();
}

void I8080_UserInterface::TranslateCode() {

	std::chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point clock_end = std::chrono::system_clock::now();

	emulationThread->SetControlMode(ControlMode::Stop);
	line_error = -1;
	type_erorr = -1;
	int i = 0, j = 0;

	if (pathLoadedFile.empty() == false)
		SaveFile();

	widget_CodeEditor->SetFlagWindow(0);
	lines_of_code = editor.GetTextLines();
	//translator = processor->Translate(lines_of_code);

	translator = Compiler->Compile(lines_of_code);

	if (translator.Error > 0) {
		translator.Opcodes.clear();

		line_error = translator.LineError;
		type_erorr = translator.Error;

#ifdef WITH_DEBUG_OUTPUT
		cout << "error_line: " << translator.LineError << "  type_erorr" << translator.Error << endl;
#endif

		TextEditor::ErrorMarkers line_error;
		line_error.insert({ translator.LineError + 1,GetErrorInfo(type_erorr) });
		editor.SetErrorMarkers(line_error);

		TextEditor::Coordinates coord;
		coord.mLine = 0;

		editor.SetCursorPosition(coord);
		coord.mLine = translator.LineError;

		editor.SetCursorPosition(coord);



		// Creating Notification - Compilation Success
		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string UNsuccess = u8"При компиляции найдена ошибка.\nНомер строки в коде: " + std::to_string(coord.mLine + 1) + u8"\nОписание: " + GetErrorInfo(type_erorr);

		notificationManager->AddNottification(Notification(color_RED, 3.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, UNsuccess)
		},
			nullptr));


	}


	emulationThread->SetControlMode(ControlMode::Stop);
	WaitThread();
	Emulator_Stop();



	if (translator.LineError == 0 && translator.Error == 0) {


		processor->Reset();
		processor->LoadMemory(translator.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();
	}

	clock_end = std::chrono::system_clock::now();
	float timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds> (clock_end - clock_start).count() / 1000.f;




	if (translator.LineError == 0 && translator.Error == 0) {

		// Creating Notification - Compilation Success

		static const ImVec4 color_GREEN{ 0.2f,0.45f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };
		string success = u8"Компиляция прошла успешно.";
		string time_info = u8"Затраченное время: " + cutFloat(std::to_string(timeElapsed), 4.f) + u8" сек.";

		notificationManager->AddNottification(Notification(color_GREEN, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, success),
				new N_Message(color_WHITE, time_info),
				new N_Progress(color_WHITE, u8"Память", u8" байт", translator.Opcodes.size(), 65535.f, false)
		},
			nullptr));

	}



#ifdef WITH_DEBUG_OUTPUT
	cout << "---------------------------------\n";
	cout << "Time Compilation: " << timeElapsed << "s" << endl;
	cout << "Used bytes: " << translator.Opcodes.size() << endl;
#endif
}



void I8080_UserInterface::WaitThread() {
	while (emulationThread->isThreadWorking()) {}
}

void I8080_UserInterface::Setting_ManagerColor() {
	vector<string> NameColor = {
		u8"Пересылка данных",
		u8"Сложения",
		u8"Вычитания",
		u8"Логические",
		u8"Сравнения",
		u8"Вызовы подпрограмм",
		u8"Возвраты",
		u8"Прыжки",
		u8"Общение с внешними портами",
		u8"Работа со стеком",
		u8"Остальные",
		u8"Дерективы транслятора",
	};

	float* values_color = new float[3];

	for (int i = 0; i < NameColor.size(); i++) {
		values_color[0] = Colors_TypesCommands[i].x;
		values_color[1] = Colors_TypesCommands[i].y;
		values_color[2] = Colors_TypesCommands[i].z;

		ImGui::ColorEdit3(NameColor[i].c_str(), values_color, ImGuiColorEditFlags_NoInputs);
	}
	delete[] values_color;
}



bool I8080_UserInterface::CheckFile_isUnsaved() {
	return widget_CodeEditor->GetFlagWindow();
}

void I8080_UserInterface::NewFile() {
	translator.Opcodes.clear();
	lines_of_code.clear();
	editor.SetTextLines(vector<string>{""});
	editor.SetTextNotChanged();
	processor->Reset();
	processor->LoadMemory(translator.Opcodes);
	pathLoadedFile = "";
	widget_RegisterFlagsInfo->InitLastState();
	glfwSetWindowTitle(window, u8"Эмулятор процессора I8080");





	static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
	static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

	string text = u8"Создан новый проект.";

	notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
		new N_Message(color_WHITE, text)
	},
		nullptr));



}
void I8080_UserInterface::OpenFile() {
	string path = OpenFileDialog();



#ifdef WITH_DEBUG_OUTPUT
	UTF8_SPLITER_ERROR error = UTF8_SPLITER_ERROR::NOTHING;
	auto print_data = utf8_splitter(path, error);

	for (int i = 0; i < print_data.size(); i++)
	{
		std::cout << "[" << print_data[i] << "]    ";

		for (int j = 0; j < print_data[i].size(); j++)
		{
			std::cout << int2string_0x_Hex(uint8_t(print_data[i][j])) << " ";
		}

		std::cout << std::endl;
	}
#endif

	OpenFileFromPath(path);
}
void I8080_UserInterface::SaveFile() {

	if (pathLoadedFile.empty()) {
		SaveFileAs();
	}
	else {
		lines_of_code = editor.GetTextLines();
		if (pathLoadedFile.size() != 0) {
			widget_CodeEditor->SetFlagWindow(0);
			ofstream ofn;
			ofn.open(stringUTF8_to_wstring(pathLoadedFile));
			for (string line : lines_of_code)
				ofn << line << endl;
			ofn.close();


			static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

			string text = u8"Файл сохранён.";

			notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, text)
			},
				nullptr));


		}
	}
}
void I8080_UserInterface::SaveFileAs() {


	string nameFile = SaveFileDialogI8080();

	if (nameFile == "") {
		return;
	}


	widget_CodeEditor->SetFlagWindow(0);

	string Path2NewFile = nameFile + ".I8080";

	LastPathManager.AddPath(Path2NewFile);


	lines_of_code = editor.GetTextLines();
	ofstream ofn;
	ofn.open(stringUTF8_to_wstring(Path2NewFile));
	for (string line : lines_of_code)
		ofn << line << endl;
	ofn.close();

	static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
	static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

	string text = u8"Файл сохранён.";

	notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
		new N_Message(color_WHITE, text)
	},
		nullptr));



	pathLoadedFile = Path2NewFile;
	glfwSetWindowTitle(window, (u8"Эмулятор процессора I8080 -> " + pathLoadedFile).c_str());
	InitLineCodes(Path2NewFile);
	TranslateCode();

	processor->Reset();
	processor->LoadMemory(translator.Opcodes);

	widget_RegisterFlagsInfo->InitLastState();

}

void I8080_UserInterface::DrawMainMenu() {

	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* wind = nullptr;
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu((string(ICON_FA_FILE) + u8" Файл").c_str())) {
			if (ImGui::MenuItem((string(ICON_FA_FILE) + u8" Новый файл").c_str(), "Ctrl + N")) {
				NewFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_FOLDER_OPEN) + u8" Открыть").c_str(), "Ctrl + O")) {
				OpenFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_BOX_ARCHIVE) + u8" Сохранить").c_str(), "Ctrl + S")) {
				SaveFile();
			}
			if (ImGui::MenuItem((string(ICON_FA_FILE_EXPORT) + u8" Сохранить как...").c_str())) {
				SaveFileAs();
			}
			if (ImGui::BeginMenu(string(string(ICON_FA_COPY) + u8" Последние проекты").c_str())) {
				if (LastPathManager.Draw()) {
					OpenFileFromPath(LastPathManager.GetChoosedPath());
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
			if (ImGui::MenuItem((string(ICON_FA_MICROCHIP) + u8" Компилировать").c_str(), "F2")) {
				TranslateCode();
			}
			ImGui::Separator();
			if (ImGui::MenuItem((string(ICON_FA_PLAY) + u8" Запуск").c_str(), "F5")) {
				Emulator_Play();
			}

			if (ImGui::MenuItem((string(ICON_FA_FORWARD_STEP) + u8" Шаг вперёд").c_str(), "F9")) {
				Emulator_Next_step();
			}
			if (ImGui::MenuItem((string(ICON_FA_PAUSE) + u8" Пауза").c_str(), "F12")) {
				Emulator_Pause();
			}
			if (ImGui::MenuItem((string(ICON_FA_STOP) + u8" Стоп").c_str(), "Esc")) {
				Emulator_Stop();
			}
			ImGui::Separator();
			if (ImGui::MenuItem((string(ICON_FA_ROTATE_RIGHT) + u8" Сбросить состояние").c_str())) {
				Emulator_FullReset();
			}
			if (ImGui::MenuItem((string(ICON_FA_ERASER) + u8" Удалить точки останова").c_str())) {
				processor->RemoveAllBreakPoints();
			}
			ImGui::Separator();

			if (ImGui::MenuItem((string(ICON_FA_GEAR) + u8" Настройки").c_str())) {
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
			ImGui::MenuItem((string(ICON_FA_BOOK_BOOKMARK) + u8" Руководство к программе").c_str(), "", widget_Help->GetPtrFlagShow());




			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu((string(ICON_FA_LIFE_RING) + u8" Помощь").c_str())) {
			if (ImGui::MenuItem((string(ICON_FA_ADDRESS_CARD) + u8" О авторе...").c_str())) {

			}
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
	widget_ColorPicker = new Widget_ColorPicker(&editor);
	widget_SymbolPicker = new Widget_SymbolPicker(&editor);
	widget_SymbolScreen = new Widget_SymbolScreen(processor);
	widget_PixelScreen = new Widget_PixelScreen(processor);
	widget_PixelScreenTwoBuffers = new Widget_PixelScreenTwoBuffers(processor);
	widget_input0x08 = new Widget_Input0x08(processor);
	widget_keyboard = new Widget_Keyboard(&editor);
	widget_output0x02 = new Widget_Output0x02(processor);
	widget_timer = new Widget_Timer(processor);
	widget_CodeEditor = new Widget_CodeEditor(&editor);
	widget_HexViewer = new Widget_HexViewer(processor, &translator);
	widget_MnemocodeViewer = new Widget_MnemocodeViewer(processor, &translator);
	widget_RegisterFlagsInfo = new Widget_RegisterFlagsInfo(processor);
	widget_EmulatorInfo = new Widget_EmulatorInfo(processor);
	widget_MarkerList = new Widget_MarkerList(processor, &translator, widget_MnemocodeViewer);
	widget_VarList = new Widget_VarList(processor, &translator);
	widget_ConstList = new Widget_ConstList(&translator);
	widget_Help = new Widget_Help();

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
	WidgetManager.AddWidgetPtr(widget_Help);
}
void I8080_UserInterface::InitSaveManager() {
	saveSystemManager->AddObjectPtr((SaveSystem*)settings);
	saveSystemManager->AddObjectPtr((SaveSystem*)&LastPathManager);
	saveSystemManager->AddObjectPtr((SaveSystem*)WorkspaceManager);
}
void I8080_UserInterface::InitKeyCombinationHandler() {

	keyCombination_handler->AddCombination(u8"Компилировать", KeyCombination({ GLFW_KEY_F2 }, std::bind(&I8080_UserInterface::Compile, this)));
	keyCombination_handler->AddCombination(u8"Запуск", KeyCombination({ GLFW_KEY_F5 }, std::bind(&I8080_UserInterface::Emulator_Play, this)));
	keyCombination_handler->AddCombination(u8"Пауза", KeyCombination({ GLFW_KEY_F12 }, std::bind(&I8080_UserInterface::Emulator_Pause, this)));
	keyCombination_handler->AddCombination(u8"Стоп", KeyCombination({ GLFW_KEY_ESCAPE }, std::bind(&I8080_UserInterface::Emulator_Stop, this)));
	keyCombination_handler->AddCombination(u8"Шаг вперёд", KeyCombination({ GLFW_KEY_F9 }, std::bind(&I8080_UserInterface::Emulator_Next_step, this)));
	keyCombination_handler->AddCombination(u8"Сбросить состояние", KeyCombination({  }, std::bind(&I8080_UserInterface::Emulator_FullReset, this)));
	keyCombination_handler->AddCombination(u8"Удалить точки останова", KeyCombination({  }, std::bind(&I8080::RemoveAllBreakPoints, processor)));


	keyCombination_handler->AddCombination(u8"Сохранить", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_S }, std::bind(&I8080_UserInterface::SaveFile, this)));
	keyCombination_handler->AddCombination(u8"Сохранить как", KeyCombination({}, std::bind(&I8080_UserInterface::SaveFileAs, this)));

	keyCombination_handler->AddCombination(u8"Новый файл", KeyCombination({}, std::bind(&I8080_UserInterface::NewFile, this)));
	keyCombination_handler->AddCombination(u8"Открыть файл", KeyCombination({}, std::bind(&I8080_UserInterface::OpenFile, this)));


	keyCombination_handler->AddCombination(u8"Настройки", KeyCombination({}, std::bind(&I8080_UserInterface::OpenFile, this)));


	keyCombination_handler->AddCombination(u8"Режим экрана", KeyCombination({ GLFW_KEY_F11 }, std::bind(&WindowManager::ToggleFullscreen, window_manager)));



	keyCombination_handler->AddCombination(u8"Следующее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadNext, WorkspaceManager)));
	keyCombination_handler->AddCombination(u8"Предыдущее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_LEFT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadPrevious, WorkspaceManager)));


}