#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"
#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"

#include "Utils/OpenGL/Window/Manager/OpenGL.WindowManager.h"
#include "Utils/OpenGL/Texture/Texture.h"
#include "Utils/File/File.h"
#include "Utils/Text/Encoding/Wstring/Wstring.h"

#include "Core/Widget/I8080.WidgetManager.h"
#include "Core/KeyCombination/KeyCombinationHandler.h"
#include "Core/ProjectManager/ProjectManager.h"
#include "Core/LastPathManager/LastPathManager.h"
#include "Core/Setting/Setting.h"
#include "Core/Theme/interface/IThemeLoadable.h"
#include "Core/Workspaces/I8080.WorkspaceManager.h"
#include "Core/WindowManager/WindowManager.h"
#include "Core/Emulator/EmulationControls/EmulationControls.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"

#include "GUI/AuthorPopup/AuthorPopup.h"

#include "DataStructures/TypesCommand.h"

#include "logo_transparent.h"

#include <string>

class MainMenuBar : public IThemeLoadable {
private:
	ImVec4 colorLogo = ImVec4(0.476, 0.631, 0.820, 1.f);
public:
	MainMenuBar(
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
		I8080* processor);
	~MainMenuBar();

	void Draw();
	bool IsPointOverTitleButton(const POINT& pt) const;

	void LoadColors() override;
	std::vector<NamedColor> GetDefaultLightColors() override;
	std::vector<NamedColor> GetDefaultDarkColors() override;

private:
	OpenGL_WindowManager* openglWindowManager = nullptr;
	I8080_WidgetManager* widgetManager = nullptr;
	LastPathManager* lastPathManager = nullptr;
	Setting* setting = nullptr;
	ProjectManager* projectManager = nullptr;
	WindowManager* windowManager = nullptr;
	KeyCombinationHandler* keyCombinationHandler = nullptr;
	EmulationControls* emulationControls = nullptr;
	EmulationThread* emulationThread = nullptr;

	I8080_WorkspaceManager* WorkspaceManager = nullptr;
	I8080* processor = nullptr;


	AuthorPopup* authorPopup = nullptr;



	void DrawLogo();
	void DrawWindowButtons();

	void Draw_MainMenu();
	void Draw_SecondaryMenu();
	void Draw_DownMenu();


	inline void Draw_MainMenu_File();
	inline void Draw_MainMenu_View();
	inline void Draw_MainMenu_Emulator();
	inline void Draw_MainMenu_Setting();
	inline void Draw_MainMenu_About();

	void Draw_ProjectMode();
	void Draw_Speedometer();

	void LoadIcon();
	Texture icon_logo;

	ImVec2 menuBarPos;
	ImVec2 menuBarSize;


	void PushSizeButtonIntoList();

public:
	GLFWwindow* window;
	bool isDragging = false;
	POINT  dragStartPoint;
	int    windowPosStartX;
	int    windowPosStartY;
	bool wasMaximizedOnDrag = false;

	ImVector<ImRect> titleButtonRects;
};


#endif 