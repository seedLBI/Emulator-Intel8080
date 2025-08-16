#include "MainMenuBar.h"

MainMenuBar::MainMenuBar(OpenGL_WindowManager* windowManager, I8080_WidgetManager* widgetManager) {
	this->windowManager = windowManager;
	this->widgetManager = widgetManager;
	window = windowManager->GetMainWindow()->GetHandle();
	LoadIcon();
}

MainMenuBar::~MainMenuBar() {

}

void MainMenuBar::Draw() {


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

		
		if (ImGui::BeginMenu(u8" Файл ")) {
			


			ImGui::EndMenu();
		}
		PushSizeButtonIntoList();


		if (ImGui::BeginMenu(u8" Эмулятор ")) {

			ImGui::EndMenu();
		}
		PushSizeButtonIntoList();

		if (ImGui::BeginMenu( u8" Окна ")) {

			if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" Закрыть все окна").c_str()))
				widgetManager->CloseAll();
			if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" Открыть все окна").c_str()))
				widgetManager->OpenAll();

			ImGui::EndMenu();
		}
		PushSizeButtonIntoList();

		if (ImGui::BeginMenu(u8" Помощь ")) {

			ImGui::EndMenu();
		}
		PushSizeButtonIntoList();

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

			//ImGui::Text(u8"Привет мир:)");

			// code...


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
	float buttonWidth = 40.0f;
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
	icon_logo.LoadTexture(logo_transparent_data.data(), logo_transparent_data.size());
	icon_logo.Init();

}
