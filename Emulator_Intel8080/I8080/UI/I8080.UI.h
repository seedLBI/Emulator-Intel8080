#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "Config_Compilier.h"

#include "OpenglWindow/OpenglWindow.h"

#include "lodepng.h"
#include "imgui_memory_editor.h"
#include "imgui_markdown.h"
#include <imgui_internal.h>
#include "IconFontCppHeaders/IconsFontAwesome6.h"
#include "TextEditor.h"


#include "Emulator\I8080.h"
#include "Utils\ColorUtilities.h"

#include "Shellapi.h"
#include "PBO.h"
#include "UTF8_2_CP1251/utf8_to_cp1251.h"
#include "DataStructures\TypesCommand.h"

#include "Utils\ImGui.Utils.h"


#include "UI/EmulationThread/EmulationThread.h"

#include "UI\Widgets\I8080.UI.ColorPicker.h"
#include "UI\Widgets\I8080.UI.SymbolPicker.h"
#include "UI\Widgets\I8080.UI.MarkerList.h"
#include "UI\Widgets\I8080.UI.VarList.h"
#include "UI\Widgets\I8080.UI.ConstList.h"
#include "UI\Widgets\I8080.UI.CodeEditor.h"
#include "UI\Widgets\I8080.UI.HexViewer.h"

#include "UI\Widgets\I8080.UI.Keyboard.h"
#include "UI\Widgets\I8080.UI.Input0x08.h"
#include "UI\Widgets\I8080.UI.Output0x02.h"
#include "UI\Widgets\I8080.UI.Timer.h"

#include "UI\Widgets\I8080.UI.MnemoCodeViewer.h"
#include "UI\Widgets\I8080.UI.RegisterFlagsInfo.h"
#include "UI\Widgets\I8080.UI.EmulatorInfo.h"

#include "UI\Widgets\I8080.UI.SymbolScreen.h"
#include "UI\Widgets\I8080.UI.PixelScreen.h"
#include "UI\Widgets\I8080.UI.PixelScreenTwoBuffers.h"
#include "UI\Widgets\I8080.UI.Help.h"

#include "UI\Widget\I8080.WidgetManager.h"
#include "UI\Workspaces\I8080.WorkspaceManager.h"
#include "UI\LastPathManager\LastPathManager.h"

#include "SaveSystem\SaveSystemManager.h"

#include "UI\FontManager\FontManager.h"
#include "UI\WindowManager\WindowManager.h"
#include "UI\Setting\Setting.h"

#include "Notification/NotificationManager.h"




#ifndef I8080_UI_H
#define I8080_UI_H


class I8080_UserInterface
{
public:
	bool ExitButton = false;

	I8080_UserInterface(GLFWwindow* window) {
		this->window = window;

		notificationManager = new NotificationManager();
		WorkspaceManager = new I8080_WorkspaceManager(&WidgetManager);

		saveSystemManager = new SaveSystemManager(GetExePath() + "\\SettingData.save");


		processor = new I8080();
		emulationThread = new EmulationThread(processor);

		font_manager = new FontManager();
		window_manager = new WindowManager();
		settings = new Setting(font_manager, window_manager,notificationManager,emulationThread);


		InitWidgets();
		InitSaveManager();


		saveSystemManager->Load();

	}
	~I8080_UserInterface() {

		saveSystemManager->Save();

	}

	void Draw() {
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
	void Update() {
		if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
			if (ImGui::IsKeyPressed(ImGuiKey_S)) {
				SaveFile();
			}
		}
		if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
			Emulator_Stop();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_F2)) {
			TranslateCode();
			widget_MnemocodeViewer->FollowCursorPC();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_F5)) {
			Emulator_Play();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_F9)) {
			Emulator_Next_step();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_F12)) {
			Emulator_Pause();
		}

		WidgetManager.Update();
		WorkspaceManager->Update();
		notificationManager->Update();
	}

	bool OpenFileFromPath(string path) {
		if (path.size() != 0) {
			LastPathManager.AddPath(path);
			path = from_utf8(path);
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
private:
	GLFWwindow* window = nullptr;
	void BeginDraw() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	}
	void EndDraw() {

		ImGui::EndFrame();

		font_manager->ReloadFont();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}



	void Emulator_Play() {
#ifdef WITH_DEBUG_OUTPUT
		cout << "Pressed Emulator_Play()\n";
#endif

		processor->ResetFlagStop();
		emulationThread->SetControlMode(ControlMode::Continous);
	}
	void Emulator_Pause() {
#ifdef WITH_DEBUG_OUTPUT
		cout << "Pressed Emulator_Pause()\n";
#endif

		emulationThread->SetControlMode(ControlMode::Stop);
		WaitThread();

		widget_RegisterFlagsInfo->InitLastState();
		widget_MnemocodeViewer->FollowCursorPC();
	}
	void Emulator_Stop() {
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
	void Emulator_Next_step() {
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
	void Emulator_FullReset() {
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


	string pathLoadedFile;
	vector<string> lines_of_code;
	TranslatorOutput translator;
	int line_error = -2;
	int type_erorr = -2;
	void InitLineCodes(string path) {
		lines_of_code.erase(lines_of_code.begin(), lines_of_code.end());

		std::ifstream t;
		t.open(path);
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		t.close();
		editor.SetText(str);
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::I8080());
		editor.SetTextNotChanged();
	}
	void TranslateCode() {

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
		translator = processor->Translate(lines_of_code);

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




	I8080* processor = nullptr;

	EmulationThread* emulationThread = nullptr;

	void WaitThread() {
		while (emulationThread->isThreadWorking()) { }
	}




	void Setting_ManagerColor() {
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




	bool Popup_NewFile_withUnsave = false;
	bool Popup_OpenFile_withUnsave = false;

	bool CheckFile_isUnsaved() {
		return widget_CodeEditor->GetFlagWindow();
	}



	void NewFile() {
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
	void OpenFile() {
		string path = OpenFileDialog();
		OpenFileFromPath(path);
	}
	void SaveFile() {

		if (pathLoadedFile.empty()) {
			SaveFileAs();
		}
		else {
			lines_of_code = editor.GetTextLines();
			if (pathLoadedFile.size() != 0) {
				widget_CodeEditor->SetFlagWindow(0);
				ofstream ofn;
				ofn.open(pathLoadedFile);
				for (string line : lines_of_code)
					ofn << line << endl;
				ofn.close();
			}
		}
	}
	void SaveFileAs() {


		string nameFile = SaveFileDialogI8080();

		if (nameFile == ""){
			return;
		}


		widget_CodeEditor->SetFlagWindow(0);

		string Path2NewFile = nameFile + ".I8080";

		LastPathManager.AddPath(Path2NewFile);


		lines_of_code = editor.GetTextLines();
		ofstream ofn;
		ofn.open(Path2NewFile);
		for (string line : lines_of_code)
			ofn << line << endl;
		ofn.close();



		pathLoadedFile = Path2NewFile;
		glfwSetWindowTitle(window, (u8"Эмулятор процессора I8080 -> " + pathLoadedFile).c_str());
		InitLineCodes(Path2NewFile);
		TranslateCode();

		processor->Reset();
		processor->LoadMemory(translator.Opcodes);

		widget_RegisterFlagsInfo->InitLastState();

	}

	void DrawMainMenu() {

		ImGuiIO& io = ImGui::GetIO();
		ImGuiWindow* wind = nullptr;
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu((string(ICON_FA_FILE) + u8" Файл").c_str())) {
				if (ImGui::MenuItem((string(ICON_FA_FILE) + u8" Новый файл").c_str(), "Ctrl + N")) {
					NewFile();
				}
				if (ImGui::MenuItem( (string(ICON_FA_FOLDER_OPEN) + u8" Открыть").c_str(), "Ctrl + O")) {
					OpenFile();
				}
				if (ImGui::MenuItem((string(ICON_FA_BOX_ARCHIVE) + u8" Сохранить").c_str(), "Ctrl + S")) {
					SaveFile();
				}
				if (ImGui::MenuItem((string(ICON_FA_FILE_EXPORT) + u8" Сохранить как...").c_str())) {
					SaveFileAs();
				}
				if (ImGui::BeginMenu(  string(string(ICON_FA_COPY) + u8" Последние проекты").c_str() ) ) {
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

				ImGui::MenuItem((string(ICON_FA_CODE) + u8" Редактор кода").c_str(), "",						   widget_CodeEditor->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_FILE_LINES) + u8" Просмотр мнемо кода").c_str(), "",			   widget_MnemocodeViewer->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_CUBE) + u8" Hex просмотр").c_str(), "",							   widget_HexViewer->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Пиксельный экран (0x05)").c_str(), "",			   widget_PixelScreen->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Продвинутый пиксельный экран (0x06)").c_str(),"",   widget_PixelScreenTwoBuffers->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_DISPLAY) + u8" Символьный экран (0x07)").c_str(), "",			   widget_SymbolScreen->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_CLOCK) + u8" Таймер (0x16)").c_str(), "",						   widget_timer->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_RIGHT_FROM_BRACKET) + u8" Окно вывода (0x02)").c_str(), "",		   widget_output0x02->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_RIGHT_TO_BRACKET) + u8" Окно ввода (0x08)").c_str(), "",		   widget_input0x08->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_KEYBOARD) + u8" Окно клавиатуры (0x10)").c_str(), "",			   widget_keyboard->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_PALETTE) + u8" Вывод всевозможных цветов").c_str(), "",			   widget_ColorPicker->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_FONT) + u8" Вывод всевозможных символов").c_str(), "",			   widget_SymbolPicker->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_FONT_AWESOME) + u8" Регистры и флаги").c_str(), "",				   widget_RegisterFlagsInfo->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_GAUGE_HIGH) + u8" Быстродействие").c_str(), "",				       widget_EmulatorInfo->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_HIGHLIGHTER) + u8" Список маркеров").c_str(), "",				   widget_MarkerList->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_BARS) + u8" Список переменных").c_str(), "",					   widget_VarList->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_HAMMER) + u8" Список постоянных").c_str(), "",					   widget_ConstList->GetPtrFlagShow());
				ImGui::MenuItem((string(ICON_FA_BOOK_BOOKMARK) + u8" Руководство к программе").c_str(), "",		   widget_Help->GetPtrFlagShow());


				

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu((string(ICON_FA_LIFE_RING) + u8" Помощь").c_str())) {
				if (ImGui::MenuItem((string(ICON_FA_ADDRESS_CARD) + u8" О авторе...").c_str())) {

				}
				if (ImGui::MenuItem((string(ICON_FA_CIRCLE_INFO) + u8" О программе...").c_str())) {

				}
				if (ImGui::BeginMenu((string(ICON_FA_BOOK_BOOKMARK) + u8" Примеры программ").c_str())){
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
			



			if (ImGui::Button(ICON_FA_PLAY,ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x*4,0)))
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


				const ImU32 col = ImColor(ImVec4(1.f,1.f,1.f,1.f));

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







	void InitWidgets() {
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
	void InitSaveManager() {
		saveSystemManager->AddObjectPtr( (SaveSystem*) settings);
		saveSystemManager->AddObjectPtr( (SaveSystem*) &LastPathManager);
		saveSystemManager->AddObjectPtr( (SaveSystem*) WorkspaceManager );
	}


	TextEditor editor;

	SaveSystemManager*			  saveSystemManager = nullptr;

	NotificationManager*		  notificationManager = nullptr;
	FontManager*			      font_manager = nullptr;
	WindowManager*				  window_manager = nullptr;
	Setting*					  settings = nullptr;

	LastPathManager				  LastPathManager;
	I8080_WorkspaceManager*		  WorkspaceManager = nullptr;
	I8080_WidgetManager			  WidgetManager;


	// base widgets
	Widget_Help*				  widget_Help = nullptr;
	Widget_HexViewer*			  widget_HexViewer = nullptr;
	Widget_MnemocodeViewer*		  widget_MnemocodeViewer = nullptr;
	Widget_RegisterFlagsInfo*	  widget_RegisterFlagsInfo = nullptr;
	Widget_EmulatorInfo*		  widget_EmulatorInfo = nullptr;
	Widget_VarList*				  widget_VarList = nullptr;
	Widget_MarkerList*			  widget_MarkerList = nullptr;
	Widget_ConstList*			  widget_ConstList = nullptr;
	Widget_CodeEditor*			  widget_CodeEditor = nullptr; 

	// port widgets
	Widget_Input0x08*			  widget_input0x08 = nullptr;
	Widget_Output0x02*			  widget_output0x02 = nullptr;
	Widget_Timer*				  widget_timer = nullptr;
	Widget_Keyboard*			  widget_keyboard = nullptr;
	Widget_PixelScreen*			  widget_PixelScreen = nullptr;
	Widget_PixelScreenTwoBuffers* widget_PixelScreenTwoBuffers = nullptr;
	Widget_SymbolScreen*		  widget_SymbolScreen = nullptr;

	// port widgets (helper)
	Widget_ColorPicker*			  widget_ColorPicker = nullptr;
	Widget_SymbolPicker*		  widget_SymbolPicker = nullptr;
};



#endif // !I8080_UI_H