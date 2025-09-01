#ifndef APPLICATION_H
#define APPLICATION_H

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dwmapi.lib")

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#include <string>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class FPS_Timer;
class OpenGL_WindowManager;
class MainMenuBar;

class I8080;
class I8080_Caretaker_Momento;
class I8080_Compiler;
class EmulationThread;
class EmulationControls;

class IntroManager;
class SaveSystemManager;
class NotificationManager;
class FontManager;
class WindowManager;
class KeyCombinationHandler;
class ProjectManager;
class Setting;
class ThemeManager;
class BaseColors;

class LastPathManager;
class I8080_WorkspaceManager;
class I8080_WidgetManager;
class I8080_WidgetManager;

class Widget_Help;
class Widget_ListVar;
class Widget_HexViewer;
class Widget_ListConst;
class Widget_CodeEditor;
class Widget_ListMarker;
class Widget_Disassembler;
class Widget_EmulatorInfo;
class Widget_MnemocodeViewer;
class Widget_ListInstruction;
class Widget_TableInstruction;
class Widget_RegisterFlagsInfo;
class Widget_HistoryInstruction;
class Widget_MnemocodeViewerTargeted;

// port widgets
class Widget_Timer;
class Widget_Keyboard;
class Widget_Input0x08;
class Widget_Output0x02;
class Widget_PixelScreen;
class Widget_SymbolScreen;
class Widget_PixelScreenTwoBuffers;

// port widgets (helper)
class Widget_ColorPicker;
class Widget_SymbolPicker;

static WNDPROC orig_wndproc = nullptr;
static std::unordered_map<HWND, GLFWwindow*> g_hwnd_to_window;

enum BufferBit {
	COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
	DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
	STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT,
};

class Application {
private:
	const std::string Title = u8"Ёмул€тор Intel8080";
public:
	Application();
	~Application();

	void Run();
	MainMenuBar* GetPTR_MainMenuBar();
private:

	bool FullLoaded = false;

	FPS_Timer* fps_limiter = nullptr;
	OpenGL_WindowManager* windowManager = nullptr;
	MainMenuBar* mainMenuBar = nullptr;


	I8080* processor = nullptr;
	I8080_Caretaker_Momento* processorCaratakerMomento = nullptr;
	I8080_Compiler* Compiler = nullptr;
	EmulationThread* emulationThread = nullptr;
	EmulationControls* emulationControls = nullptr;


	IntroManager* introManager = nullptr;
	SaveSystemManager* saveSystemManager = nullptr;
	NotificationManager* notificationManager = nullptr;
	FontManager* fontManager = nullptr;
	WindowManager* window_manager = nullptr;
	KeyCombinationHandler* keyCombination_handler = nullptr;
	ProjectManager* projectManager = nullptr;
	Setting* settings = nullptr;
	ThemeManager* themeManager = nullptr;
	BaseColors* baseColors = nullptr;



	LastPathManager*			lastPathManager = nullptr;
	I8080_WorkspaceManager*		WorkspaceManager = nullptr;
	I8080_WidgetManager*		WidgetManager;


	// base widgets
	Widget_Help* widget_Help = nullptr;
	Widget_ListVar* widget_ListVar = nullptr;
	Widget_HexViewer* widget_HexViewer = nullptr;
	Widget_ListConst* widget_ListConst = nullptr;
	Widget_CodeEditor* widget_CodeEditor = nullptr;
	Widget_ListMarker* widget_ListMarker = nullptr;
	Widget_Disassembler* widget_Disassembler = nullptr;
	Widget_EmulatorInfo* widget_EmulatorInfo = nullptr;
	Widget_MnemocodeViewer* widget_MnemocodeViewer = nullptr;
	Widget_ListInstruction* widget_ListInstruction = nullptr;
	Widget_TableInstruction* widget_TableInstruction = nullptr;
	Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo = nullptr;
	Widget_HistoryInstruction* widget_HistoryInstruction = nullptr;
	Widget_MnemocodeViewerTargeted* widget_MnemocodeViewerTargeted = nullptr;

	// port widgets
	Widget_Timer* widget_timer = nullptr;
	Widget_Keyboard* widget_keyboard = nullptr;
	Widget_Input0x08* widget_input0x08 = nullptr;
	Widget_Output0x02* widget_output0x02 = nullptr;
	Widget_PixelScreen* widget_PixelScreen = nullptr;
	Widget_SymbolScreen* widget_SymbolScreen = nullptr;
	Widget_PixelScreenTwoBuffers* widget_PixelScreenTwoBuffers = nullptr;

	// port widgets (helper)
	Widget_ColorPicker* widget_ColorPicker = nullptr;
	Widget_SymbolPicker* widget_SymbolPicker = nullptr;


	void Draw();

	void BeginDraw();
	void EndDraw();

	void Update();

	void Init_OpenGL();
	void Init_IconApplication();
	void Init_BorderWindow();
	void Init_ImGui();
	void Init_Setting();
	void Init_ThemeManager();
	void Init_Widgets();
	void Init_SaveManager();
	void Init_KeyCombinationHandler();
};



#endif