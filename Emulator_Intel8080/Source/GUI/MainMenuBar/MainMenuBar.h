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

#include "logo_transparent.h"

#include <string>

class MainMenuBar {
private:
	ImVec4 colorLogo = ImVec4(0.476, 0.631, 0.820, 1.f);
public:
	MainMenuBar(OpenGL_WindowManager* windowManager, I8080_WidgetManager* widgetManager);
	~MainMenuBar();

	void Draw();
	bool IsPointOverTitleButton(const POINT& pt) const;
private:
	OpenGL_WindowManager* windowManager = nullptr;
	I8080_WidgetManager* widgetManager = nullptr;

	void DrawLogo();
	void DrawWindowButtons();

	void Draw_MainMenu();
	void Draw_SecondaryMenu();
	void Draw_DownMenu();

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