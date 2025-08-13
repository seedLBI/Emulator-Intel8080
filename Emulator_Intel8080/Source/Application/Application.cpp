#include "Application.h"

LRESULT CALLBACK custom_wndproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Application::Application() {

	Init_OpenGL();
	Init_BorderWindow();
	Init_ImGui();

	mainMenuBar = new MainMenuBar(windowManager);

	fontManager = new FontManager;
	fontManager->ReloadFont();

	fps_limiter = new FPS_Timer;
	fps_limiter->SetTargetFPS(60);


}



void Application::Init_OpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	windowManager = new WindowManager(Title, 1280, 720, 100, 100);

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

	ImGui::GetIO().IniFilename = NULL;
	ImGui::GetIO().LogFilename = NULL;
}

Application::~Application() {

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
}
void Application::Update() {

}

void Application::BeginDraw() {
	glfwPollEvents();

	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glClear(BufferBit::COLOR_BUFFER_BIT | BufferBit::DEPTH_BUFFER_BIT);

	fontManager->ReloadFont();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}

void Application::EndDraw() {

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(windowManager->GetMainWindow()->GetHandle());

	fps_limiter->wait();
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