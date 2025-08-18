#include "Application.h"

LRESULT CALLBACK custom_wndproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Application::Application() {

	Init_OpenGL();
	Init_IconApplication();
	Init_BorderWindow();
	Init_ImGui();

	fps_limiter = new FPS_Timer;
	fps_limiter->SetTargetFPS(60);

	saveSystemManager = new SaveSystemManager(GetPathDirectory() + L"\\SettingData.save");

	WidgetManager = new I8080_WidgetManager(fps_limiter);

	notificationManager = new NotificationManager(fps_limiter, windowManager->GetMainWindow()->GetHandle());
	WorkspaceManager = new I8080_WorkspaceManager(WidgetManager);
	lastPathManager = new LastPathManager();
	keyCombination_handler = new KeyCombinationHandler(fps_limiter, windowManager->GetMainWindow()->GetHandle(),notificationManager);
	fontManager = new FontManager;
	window_manager = new WindowManager(windowManager->GetMainWindow()->GetHandle(),fps_limiter);
	themeManager = new ThemeManager();
	baseColors = new BaseColors();
	settings = new Setting();

	processor = new I8080();
	processorCaratakerMomento = new I8080_Caretaker_Momento(processor);
	Compiler = new I8080_Compiler();
	emulationThread = new EmulationThread(processor, processorCaratakerMomento);

	introManager = new IntroManager();


	projectManager = new ProjectManager(
		windowManager->GetMainWindow()->GetHandle(),
		processor,
		notificationManager,
		lastPathManager,
		emulationThread,
		Compiler,
		processorCaratakerMomento);

	Init_Widgets();

	emulationControls = new EmulationControls(
		processor,
		processorCaratakerMomento,
		emulationThread,
		projectManager,
		widget_RegisterFlagsInfo,
		widget_MnemocodeViewer,
		widget_CodeEditor);



	Init_Setting();
	Init_SaveManager();
	Init_KeyCombinationHandler();
	Init_ThemeManager();

	projectManager->InitWidgets(
		widget_MnemocodeViewer,
		widget_RegisterFlagsInfo,
		widget_CodeEditor);

	saveSystemManager->Load();

	mainMenuBar = new MainMenuBar(
		windowManager,
		WidgetManager,
		lastPathManager,
		settings,
		projectManager,
		window_manager,
		keyCombination_handler,
		emulationControls,
		emulationThread,
		WorkspaceManager,
		processor);
}



void Application::Init_OpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	windowManager = new OpenGL_WindowManager(Title, 1280, 720, 100, 100);

}
void Application::Init_IconApplication() {
	GLFWimage icon;
	icon.pixels = stbi_load_from_memory(logo48, 2404, &icon.width, &icon.height, nullptr, 4);
	if (icon.pixels) {
		glfwSetWindowIcon(windowManager->GetMainWindow()->GetHandle(), 1, &icon);
		stbi_image_free(icon.pixels);
	}
}
void Application::Init_BorderWindow() {
	GLFWwindow* win = windowManager->GetMainWindow()->GetHandle();
	
	HWND hwnd = glfwGetWin32Window(win);
	g_hwnd_to_window[hwnd] = win;

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style |= WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;
	//style |= WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;


	SetWindowLong(hwnd, GWL_STYLE, style);


	MARGINS m = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &m);


	DWM_WINDOW_CORNER_PREFERENCE pref = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND;
	DwmSetWindowAttribute(
		hwnd,
		DWMWA_WINDOW_CORNER_PREFERENCE,
		&pref,
		sizeof(pref)
	);


	orig_wndproc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)custom_wndproc);

	glfwSetWindowUserPointer(win, this);
}
void Application::Init_ImGui() {
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::StyleColorsDark();


	ImGui_ImplGlfw_InitForOpenGL(windowManager->GetMainWindow()->GetHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 330");


	auto& s = ImGui::GetStyle();
	//s.ImageBorderSize = 1.f;
	s.SeparatorTextAlign.x = 0.5f;
	s.SeparatorTextAlign.y = 0.5f;
	s.SeparatorTextBorderSize = 9;

	s.FrameRounding = 6.f;

	s.WindowBorderSize = 1.f;
	s.FrameBorderSize = 1.f;
	s.PopupBorderSize = 1.f;

	s.WindowRounding = 12.f;
	s.ChildRounding = 12.f;



	ImGui::GetIO().IniFilename = NULL;
	ImGui::GetIO().LogFilename = NULL;






}

void Application::Init_Setting() {
	settings->AddSettingObject(fontManager);
	settings->AddSettingObject(window_manager);
	settings->AddSettingObject(WorkspaceManager);
	settings->AddSettingObject(notificationManager);
	settings->AddSettingObject(emulationThread);
	settings->AddSettingObject(keyCombination_handler);
	settings->AddSettingObject(projectManager);
	settings->AddSettingObject(widget_CodeEditor->GetPtrTextEditor());
	settings->AddSettingObject(lastPathManager);
	settings->AddSettingObject(widget_MnemocodeViewer);
	settings->AddSettingObject(themeManager);
	settings->AddSettingObject(introManager);
}
void Application::Init_ThemeManager() {
	themeManager->AddObject(baseColors);
	themeManager->AddObject(widget_CodeEditor->GetPtrTextEditor());
	themeManager->AddObject(widget_RegisterFlagsInfo);
	themeManager->AddObject(widget_Help);
	themeManager->AddObject(widget_keyboard);
	themeManager->AddObject(widget_input0x08);
	themeManager->AddObject(widget_MnemocodeViewer);
	themeManager->AddObject(widget_MnemocodeViewerTargeted);
	themeManager->AddObject(widget_HexViewer->GetPtrMemoryEditor());
	themeManager->AddObject(&Singletone_InfoInstruction::Instance());
	themeManager->AddObject(&Singleton_I8080_HighlighterInstruction::Instance());
}
void Application::Init_Widgets() {
	widget_CodeEditor = new Widget_CodeEditor(fps_limiter);
	widget_HistoryInstruction = new Widget_HistoryInstruction(processor, emulationThread, processorCaratakerMomento);
	//widget_ListInstruction		= new Widget_ListInstruction();
	widget_TableInstruction = new Widget_TableInstruction();
	//widget_Disassembler			= new Widget_Disassembler(processor);
	widget_ColorPicker = new Widget_ColorPicker(widget_CodeEditor->GetPtrTextEditor());
	widget_SymbolPicker = new Widget_SymbolPicker(widget_CodeEditor->GetPtrTextEditor());
	widget_SymbolScreen = new Widget_SymbolScreen(processor);
	widget_PixelScreen = new Widget_PixelScreen(windowManager->GetMainWindow()->GetHandle(), processor);
	widget_PixelScreenTwoBuffers = new Widget_PixelScreenTwoBuffers(windowManager->GetMainWindow()->GetHandle(), processor);
	widget_input0x08 = new Widget_Input0x08(processor);
	widget_keyboard = new Widget_Keyboard(fps_limiter,widget_CodeEditor->GetPtrTextEditor());
	widget_output0x02 = new Widget_Output0x02(processor, notificationManager);
	widget_timer = new Widget_Timer(processor);
	widget_MnemocodeViewer = new Widget_MnemocodeViewer(processor, projectManager->GetPtrTranslatorOutput());
	widget_MnemocodeViewerTargeted = new Widget_MnemocodeViewerTargeted(processor, projectManager->GetPtrTranslatorOutput());
	widget_HexViewer = new Widget_HexViewer(processor, projectManager->GetPtrTranslatorOutput(), widget_MnemocodeViewer);
	widget_RegisterFlagsInfo = new Widget_RegisterFlagsInfo(processor);
	widget_EmulatorInfo = new Widget_EmulatorInfo(processor);
	widget_ListMarker = new Widget_ListMarker(processor, projectManager->GetPtrTranslatorOutput(), widget_MnemocodeViewer, notificationManager);
	widget_ListVar = new Widget_ListVar(processor, projectManager->GetPtrTranslatorOutput());
	widget_ListConst = new Widget_ListConst(projectManager->GetPtrTranslatorOutput());
	widget_Help = new Widget_Help();

	WidgetManager->AddWidgetPtr(widget_Help);
	WidgetManager->AddWidgetPtr(widget_HistoryInstruction);
	//WidgetManager->AddWidgetPtr(widget_ListInstruction);
	WidgetManager->AddWidgetPtr(widget_TableInstruction);
	//WidgetManager->AddWidgetPtr(widget_Disassembler);
	WidgetManager->AddWidgetPtr(widget_ColorPicker);
	WidgetManager->AddWidgetPtr(widget_SymbolPicker);
	WidgetManager->AddWidgetPtr(widget_SymbolScreen);
	WidgetManager->AddWidgetPtr(widget_PixelScreen);
	WidgetManager->AddWidgetPtr(widget_PixelScreenTwoBuffers);
	WidgetManager->AddWidgetPtr(widget_input0x08);
	WidgetManager->AddWidgetPtr(widget_keyboard);
	WidgetManager->AddWidgetPtr(widget_output0x02);
	WidgetManager->AddWidgetPtr(widget_timer);
	WidgetManager->AddWidgetPtr(widget_CodeEditor);
	WidgetManager->AddWidgetPtr(widget_HexViewer);
	WidgetManager->AddWidgetPtr(widget_MnemocodeViewer);
	WidgetManager->AddWidgetPtr(widget_MnemocodeViewerTargeted);
	WidgetManager->AddWidgetPtr(widget_RegisterFlagsInfo);
	WidgetManager->AddWidgetPtr(widget_EmulatorInfo);
	WidgetManager->AddWidgetPtr(widget_ListMarker);
	WidgetManager->AddWidgetPtr(widget_ListVar);
	WidgetManager->AddWidgetPtr(widget_ListConst);
}
void Application::Init_SaveManager() {
	saveSystemManager->AddObjectPtr((SaveSystem*)settings);
	saveSystemManager->AddObjectPtr((SaveSystem*)lastPathManager);
	saveSystemManager->AddObjectPtr((SaveSystem*)WorkspaceManager);
}
void Application::Init_KeyCombinationHandler() {
	keyCombination_handler->AddCombination(u8"Компилировать", KeyCombination({ GLFW_KEY_F2 }, std::bind(&ProjectManager::Compile, projectManager)));
	keyCombination_handler->AddCombination(u8"Запуск", KeyCombination({ GLFW_KEY_F5 }, std::bind(&EmulationControls::Play, emulationControls)));
	keyCombination_handler->AddCombination(u8"Пауза", KeyCombination({ GLFW_KEY_F12 }, std::bind(&EmulationControls::Pause, emulationControls)));
	keyCombination_handler->AddCombination(u8"Стоп", KeyCombination({ GLFW_KEY_ESCAPE }, std::bind(&EmulationControls::Stop, emulationControls)));
	keyCombination_handler->AddCombination(u8"Шаг вперёд", KeyCombination({ GLFW_KEY_F9 }, std::bind(&EmulationControls::Next_step, emulationControls)));
	keyCombination_handler->AddCombination(u8"Шаг назад", KeyCombination({}, std::bind(&EmulationControls::Undo_step, emulationControls)));
	keyCombination_handler->AddCombination(u8"Сбросить состояние", KeyCombination({  }, std::bind(&EmulationControls::FullReset, emulationControls)));
	keyCombination_handler->AddCombination(u8"Удалить точки останова", KeyCombination({  }, std::bind(&I8080::RemoveAllBreakPoints, processor)));

	keyCombination_handler->AddCombination(u8"Сохранить", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_S }, std::bind(&ProjectManager::SaveFile, projectManager)));
	keyCombination_handler->AddCombination(u8"Сохранить как", KeyCombination({}, std::bind(&ProjectManager::SaveFileAs, projectManager)));
	keyCombination_handler->AddCombination(u8"Сохранить в бинарный файл", KeyCombination({}, std::bind(&ProjectManager::SaveFileIntoBinary, projectManager)));

	keyCombination_handler->AddCombination(u8"Новый файл", KeyCombination({}, std::bind(&ProjectManager::NewFile, projectManager)));
	keyCombination_handler->AddCombination(u8"Открыть файл", KeyCombination({}, std::bind(&ProjectManager::OpenFile, projectManager)));

	keyCombination_handler->AddCombination(u8"Настройки", KeyCombination({}, std::bind(&Setting::Toggle, settings)));
	keyCombination_handler->AddCombination(u8"Режим сохранения истории (вкл\\выкл)", KeyCombination({}, std::bind(&Processor::ToggleHistoryMode, processor)));


	keyCombination_handler->AddCombination(u8"Полноэкранный\\Оконный", KeyCombination({ GLFW_KEY_F11 }, std::bind(&WindowManager::ToggleFullscreen, window_manager)));

	keyCombination_handler->AddCombination(u8"Постоянный фокус в просмотре памяти", KeyCombination({}, std::bind(&Widget_MnemocodeViewer::ToggleFlagAlwaysFocus, widget_MnemocodeViewer)));

	keyCombination_handler->AddCombination(u8"Cледующая скорость процессора", KeyCombination({}, std::bind(&EmulationThread::LoadNextSpeed, emulationThread)));
	keyCombination_handler->AddCombination(u8"Предыдущая скорость процессора", KeyCombination({}, std::bind(&EmulationThread::LoadPreviousSpeed, emulationThread)));

	keyCombination_handler->AddCombination(u8"Следующее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadNext, WorkspaceManager)));
	keyCombination_handler->AddCombination(u8"Предыдущее рабочее пространство", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_LEFT_BRACKET }, std::bind(&I8080_WorkspaceManager::LoadPrevious, WorkspaceManager)));

	keyCombination_handler->AddCombination(u8"Увеличить шрифт на 1", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_EQUAL }, std::bind(&FontManager::SetOneStepBigger, fontManager)));
	keyCombination_handler->AddCombination(u8"Уменьшить шрифт на 1", KeyCombination({ GLFW_KEY_LEFT_CONTROL, GLFW_KEY_MINUS }, std::bind(&FontManager::SetOneStepSmaller, fontManager)));
}

Application::~Application() {
	if (FullLoaded)
		saveSystemManager->Save();
}

void Application::Run() {
	while (windowManager->GetMainWindow()->IsShouldClose() == false) {

		BeginDraw();
		Draw();
		EndDraw();

		Update();

	}
}

void Application::Draw() {
	mainMenuBar->Draw();

	WidgetManager->Draw();
	notificationManager->Draw();
	settings->Draw();

}
void Application::Update() {
	projectManager->Update();
	keyCombination_handler->Update();
	WidgetManager->Update();
	WorkspaceManager->Update();
	notificationManager->Update();
}

void Application::BeginDraw() {
	glfwPollEvents();

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glClear(BufferBit::COLOR_BUFFER_BIT | BufferBit::DEPTH_BUFFER_BIT);


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

}

void Application::EndDraw() {

	ImGui::EndFrame();
	
	fontManager->ReloadFont();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(windowManager->GetMainWindow()->GetHandle());


	fps_limiter->wait();
	FullLoaded = true;
}


MainMenuBar* Application::GetPTR_MainMenuBar() {
	return mainMenuBar;
}





LRESULT CALLBACK custom_wndproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {


	switch (msg) {
	case WM_NCCALCSIZE: {
		auto params = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

		if (IsZoomed(hwnd)) {
			HMONITOR hMon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi = { sizeof(mi) };
			GetMonitorInfo(hMon, &mi);
			RECT rcWork = mi.rcWork;

			params->rgrc[0].left = rcWork.left;
			params->rgrc[0].top = rcWork.top;
			params->rgrc[0].right = rcWork.right;
			params->rgrc[0].bottom = rcWork.bottom;

			return WVR_REDRAW;
		}
		else {
			return 0;
		}
		break;
	}
	case WM_NCHITTEST: {

		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(hwnd, &pt);

		RECT rc;
		GetClientRect(hwnd, &rc);
		const int border = 4;

		bool left = pt.x < border;
		bool right = pt.x >= rc.right - border;
		bool top = pt.y < border;
		bool bottom = pt.y >= rc.bottom - border;

		if (left && top)     return HTTOPLEFT;
		if (right && top)    return HTTOPRIGHT;
		if (left && bottom)  return HTBOTTOMLEFT;
		if (right && bottom) return HTBOTTOMRIGHT;

		if (left)   return HTLEFT;
		if (right)  return HTRIGHT;
		if (top)    return HTTOP;
		if (bottom) return HTBOTTOM;


		auto it = g_hwnd_to_window.find(hwnd);
		if (it != g_hwnd_to_window.end()) {
			GLFWwindow* win = it->second;
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));

			float menuHeight = 60.f;
			if (pt.y >= 0 && pt.y < menuHeight) {
				if (app->GetPTR_MainMenuBar()->IsPointOverTitleButton(pt)) {
					return HTCLIENT;
				}
				return HTCAPTION;
			}
		}
		return HTCLIENT;
	}
	case WM_SETCURSOR: {

		if (IsZoomed(hwnd)) {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return TRUE;
		}

		int hitTest = LOWORD(lParam);
		switch (hitTest) {
		case HTLEFT:
		case HTRIGHT:
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
			return TRUE;
		case HTTOP:
		case HTBOTTOM:
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
			return TRUE;
		case HTTOPLEFT:
		case HTBOTTOMRIGHT:
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
			return TRUE;
		case HTTOPRIGHT:
		case HTBOTTOMLEFT:
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
			return TRUE;
		default:
			break;
		}
		break;
	}
	case WM_GETMINMAXINFO: {
		auto mmi = reinterpret_cast<MINMAXINFO*>(lParam);

		HMONITOR hMon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		GetMonitorInfo(hMon, &mi);

		RECT rcWork = mi.rcWork;

		mmi->ptMaxPosition.x = rcWork.left;
		mmi->ptMaxPosition.y = rcWork.top;
		mmi->ptMaxSize.x = rcWork.right - rcWork.left;
		mmi->ptMaxSize.y = rcWork.bottom - rcWork.top;

		return 0;
	}
	case WM_SETTINGCHANGE: {
		if (wParam == SPI_SETWORKAREA) {
			if (IsZoomed(hwnd)) {

				HMONITOR hMon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi = { sizeof(mi) };
				GetMonitorInfo(hMon, &mi);
				RECT rcWork = mi.rcWork;

				SetWindowPos(hwnd, NULL, rcWork.left, rcWork.top,
					rcWork.right - rcWork.left, rcWork.bottom - rcWork.top,
					SWP_NOZORDER | SWP_NOACTIVATE);
			}
		}
		break;
	}

	}

	return CallWindowProc(orig_wndproc, hwnd, msg, wParam, lParam);
}