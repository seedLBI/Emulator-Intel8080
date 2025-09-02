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
	I8080* processor) : IThemeLoadable(u8"������� ����") {

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
			u8"�������"
		});


}

MainMenuBar::~MainMenuBar() {

}

void MainMenuBar::LoadColors() {
	for (int i = 0; i < object_colors.colors.size(); i++) {
		if (object_colors.colors[i].nameColor == u8"�������")
			colorLogo = object_colors.colors[i].color;
	}
}
std::vector<NamedColor> MainMenuBar::GetDefaultLightColors() {
	return {
		{ u8"�������",ImColor(237, 168, 79,255) }
	};
}
std::vector<NamedColor> MainMenuBar::GetDefaultDarkColors() {
	return {
		{ u8"�������",ImColor(0.476, 0.631, 0.820, 1.f) }
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
			
			const char* text_compile_button = std::string("  " + std::string(ICON_FA_MICROCHIP) + u8" �������������   ").c_str();
			if (ImGui::Button(text_compile_button, ImVec2(ImGui::CalcTextSize(text_compile_button).x, 0))) {
				projectManager->Compile();
			}
			PushSizeButtonIntoList();

			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);

			if (ImGui::Button(ICON_FA_PLAY, ImVec2(ImGui::CalcTextSize(ICON_FA_PLAY).x * 5, 0)))
				emulationControls->Play();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"������ ��������");


			if (ImGui::Button(ICON_FA_STOP, ImVec2(ImGui::CalcTextSize(ICON_FA_STOP).x * 5, 0)))
				emulationControls->Stop();
			PushSizeButtonIntoList();
			if(ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"����");


			if (ImGui::Button(ICON_FA_PAUSE, ImVec2(ImGui::CalcTextSize(ICON_FA_PAUSE).x * 5, 0)))
				emulationControls->Pause();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"�����");

			if (processor->isHistoryModeEnabled()) {
				if (ImGui::Button(ICON_FA_BACKWARD_STEP, ImVec2(ImGui::CalcTextSize(ICON_FA_BACKWARD_STEP).x * 5, 0)))
					emulationControls->Undo_step_into();
				PushSizeButtonIntoList();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip(u8"��� �����");
			}

			if (ImGui::Button(ICON_FA_FORWARD_STEP, ImVec2(ImGui::CalcTextSize(ICON_FA_FORWARD_STEP).x * 5, 0)))
				emulationControls->Next_step_into();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"��� � �������");

			if (ImGui::Button(ICON_FA_FORWARD_FAST, ImVec2(ImGui::CalcTextSize(ICON_FA_FORWARD_FAST).x * 5, 0)))
				emulationControls->Next_step_over();
			PushSizeButtonIntoList();
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip(u8"��� � �������");


			ImGui::PopStyleColor();


			ImGuiWindow* wind = nullptr;

			wind = ImGui::GetCurrentWindow();

			ImRect menuBar_rect = wind->MenuBarRect();
			ImGui::PushClipRect(menuBar_rect.Min, menuBar_rect.Max, false);

			float width = 220.f;
			ImGui::SetCursorPos(ImVec2(menuBar_rect.Max.x - width, 0.0f));
			const char* types_Workspace[2] = { u8"�����������",u8"��� �������" };
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

			width += ImGui::CalcTextSize(u8"������� ������������").x * 1.05f;


			ImGui::SetCursorPos(ImVec2(menuBar_rect.Max.x - width, 0.0f));
			ImGui::Text(u8"������� ������������");


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


			ImGui::Text(u8"������� ������ �� �����������");


			ImGui::EndMenuBar();
		}
	}
	ImGui::End();

	ImGui::PopStyleColor();
}

void MainMenuBar::Draw_ProjectMode() {
	const char* tooltip = u8"����� ������ � ����������� ������:\n\n* USER - ������������ �������� ��.\n\n* BIN - �������� �������� � ����������.\n\n* COM - �������� �������� � ����������.\nPC ��������������� � 0x0100 � ���������� ���������\n���� � ������ ��������� ��� ���������� ������� ������ CP/M.";
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

	// ����������� ���� ������ �� ������� ����
	ImGui::SetCursorPosX(windowWidth - totalWidth);

	// ��������� ������� ����� ������
	ImVec4 colBtn = style.Colors[ImGuiCol_Button];
	ImVec4 colBtnHover = style.Colors[ImGuiCol_ButtonHovered];
	ImVec4 colBtnActive = style.Colors[ImGuiCol_ButtonActive];

	// ������ ���� ������ ����� ��, ��� ��� ���� (����������)
	ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_MenuBarBg]);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colBtnHover);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, colBtnActive);

	const ImVec2 buttonSize = ImVec2(buttonWidth, ImGui::GetFrameHeight() - 1.f);


	// ������
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

	// ��������������� ������ �����
	ImGui::PopStyleColor(3);
}

inline void MainMenuBar::Draw_MainMenu_File() {
	if (ImGui::BeginMenu(u8" ���� ")) {


		if (ImGui::MenuItem((std::string(ICON_FA_FILE) + u8" ����� ����").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"����� ����").c_str())) {
			projectManager->NewFile();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FOLDER_OPEN) + u8" �������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"������� ����").c_str())) {
			projectManager->OpenFile();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_BOX_ARCHIVE) + u8" ���������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"���������").c_str())) {
			projectManager->SaveFile();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FILE_EXPORT) + u8" ��������� ���...").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"��������� ���").c_str())) {
			projectManager->SaveFileAs();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_FOLDER_OPEN) + u8" ��������� � �������� ����").c_str())) {
			projectManager->SaveFileIntoBinary();
		}
		ImGui::Separator();
		if (ImGui::BeginMenu(std::string(std::string(ICON_FA_COPY) + u8" ��������� �������").c_str())) {
			if (lastPathManager->Draw()) {
				projectManager->OpenFileWithPath(lastPathManager->GetChoosedPath());
			}
			ImGui::EndMenu();
		}

		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_CIRCLE_XMARK) + u8" �����").c_str(),u8"Alt + F4")) {
			//ExitButton = true;
		}
		PushSizeButtonIntoList();




		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_View() {
	if (ImGui::BeginMenu(u8" ���� ")) {

		if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" ������� ��� ����").c_str()))
			widgetManager->CloseAll();

		ImGui::Separator();

		if (ImGui::MenuItem(std::string(std::string(ICON_FA_WINDOW_RESTORE) + u8" ������� ��� ����").c_str()))
			widgetManager->OpenAll();


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.2, 0.2, 1.0));
		ImGui::SeparatorText(u8"��������");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_CODE) + u8" �������� ����").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"�������� ����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FILE_LINES) + u8" �������� ����� ����").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"����� ���")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FILE_LINES) + u8" �������� ����� ���� (����������)").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"����� ��� (����������)")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_CUBE) + u8" Hex ��������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"�������� ������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FONT_AWESOME) + u8" �������� � �����").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"�������� � �����")->GetPtrFlagShow()
		);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.6, 0.0, 1.0));
		ImGui::SeparatorText(u8"���������������");
		ImGui::PopStyleColor();
		//ImGui::MenuItem((string(ICON_FA_CODE)				+ u8" ������������").c_str(), "", widget_Disassembler->GetPtrFlagShow());
		ImGui::MenuItem(
			(std::string(ICON_FA_GAUGE_HIGH) + u8" ��������������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"��������������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_HIGHLIGHTER) + u8" ������ ��������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"�������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_BARS) + u8" ������ ����������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"����������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_HAMMER) + u8" ������ ����������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"����������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_LIST) + u8" ������� ����������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"������� ����������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_PALETTE) + u8" ����� ������������ ������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"��� �����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_FONT) + u8" ����� ������������ ��������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"��� �������")->GetPtrFlagShow()
		);



		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.6, 0.0, 1.0));
		ImGui::SeparatorText(u8"������� �����");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" ���������� �����").c_str(),
			"0x05",
			widgetManager->GetWidgetPtr(u8"���������� �����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" ����������� ���������� �����").c_str(),
			"0x06",
			widgetManager->GetWidgetPtr(u8"����������� ���������� �����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_DISPLAY) + u8" ���������� �����").c_str(),
			"0x07",
			widgetManager->GetWidgetPtr(u8"���������� �����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_RIGHT_FROM_BRACKET) + u8" ���� ������").c_str(),
			"0x02",
			widgetManager->GetWidgetPtr(u8"���� ������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_RIGHT_TO_BRACKET) + u8" ���� �����").c_str(),
			"0x08",
			widgetManager->GetWidgetPtr(u8"���� �����")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_KEYBOARD) + u8" ���� ����������").c_str(),
			"0x10",
			widgetManager->GetWidgetPtr(u8"����������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_CLOCK) + u8" ������").c_str(),
			"0x16",
			widgetManager->GetWidgetPtr(u8"������")->GetPtrFlagShow()
		);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4, 1.0, 0.4, 1.0));
		ImGui::SeparatorText(u8"������");
		ImGui::PopStyleColor();
		ImGui::MenuItem(
			(std::string(ICON_FA_BOOK_BOOKMARK) + u8" ����������� � ���������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"�����������")->GetPtrFlagShow()
		);
		ImGui::Separator();
		ImGui::MenuItem(
			(std::string(ICON_FA_TABLE) + u8" ������� ����������").c_str(),
			"",
			widgetManager->GetWidgetPtr(u8"������� ����������")->GetPtrFlagShow()
		);

		//ImGui::MenuItem((string(ICON_FA_LIST)				+ u8" ������ ����������").c_str(), "", widget_ListInstruction->GetPtrFlagShow());


		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_Emulator() {
	if (ImGui::BeginMenu(u8" �������� ")) {

		if (ImGui::MenuItem((std::string(ICON_FA_MICROCHIP) + u8" �������������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"�������������").c_str())) {
			projectManager->Compile();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_PLAY) + u8" ������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"������").c_str())) {
			emulationControls->Play();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_FORWARD_STEP) + u8" ��� c �������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"��� c �������").c_str())) {
			emulationControls->Next_step_into();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_FORWARD_STEP) + u8" ��� c �������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"��� c �������").c_str())) {
			emulationControls->Next_step_over();
		}

		if (processor->isHistoryModeEnabled()) {
			if (ImGui::MenuItem((std::string(ICON_FA_BACKWARD_STEP) + u8" ��� �����").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"��� �����").c_str()))
				emulationControls->Undo_step_into();
		}

		if (ImGui::MenuItem((std::string(ICON_FA_PAUSE) + u8" �����").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"�����").c_str())) {
			emulationControls->Pause();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_STOP) + u8" ����").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"����").c_str())) {
			emulationControls->Stop();
		}
		ImGui::Separator();
		if (ImGui::MenuItem((std::string(ICON_FA_ROTATE_RIGHT) + u8" �������� ���������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"�������� ���������").c_str())) {
			emulationControls->FullReset();
		}
		if (ImGui::MenuItem((std::string(ICON_FA_ERASER) + u8" ������� ����� ��������").c_str(), keyCombinationHandler->GetStrCombinationByName(u8"������� ����� ��������").c_str())) {
			processor->RemoveAllBreakPoints();
		}


		ImGui::EndMenu();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_Setting() {
	if (ImGui::MenuItem(u8" ��������� ")) {
		setting->Open();
	}
	PushSizeButtonIntoList();
}
inline void MainMenuBar::Draw_MainMenu_About() {


	if (ImGui::MenuItem(u8" � ������ ")) {
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
