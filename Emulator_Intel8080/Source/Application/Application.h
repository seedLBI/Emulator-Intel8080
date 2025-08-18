#ifndef APPLICATION_H
#define APPLICATION_H

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dwmapi.lib")

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stb_image.h>
#include <dwmapi.h>
#include <windowsx.h>
#include <string>
#include <unordered_map>


#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"
#include "ThirdParty/ImGui/imgui_impl_glfw.h"
#include "ThirdParty/ImGui/imgui_impl_opengl3.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/OpenGL/Window/Manager/OpenGL.WindowManager.h"
#include "Utils/Timer/Timer.Framerate.h"
#include "Core/FontManager/FontManager.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/Processors/Intel8080/History/Caretaker/I8080.Caretaker.Momento.h"
#include "Core/Emulator/Processors/Intel8080/Compiler/I8080.Compiler.h"
#include "Core/Emulator/EmulationControls/EmulationControls.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/IntroManager/IntroManager.h"
#include "Core/SaveSystem/SaveSystemManager.h"
#include "Core/WindowManager/WindowManager.h"
#include "Core/KeyCombination/KeyCombinationHandler.h"
#include "Core/LastPathManager/LastPathManager.h"
#include "Core/Setting/Setting.h"
#include "Core/Theme/ThemeManager/ThemeManager.h"
#include "Core/Theme/BaseColors/BaseColors.h"
#include "Core/Widget/I8080.WidgetManager.h"
#include "Core/Workspaces/I8080.WorkspaceManager.h"

#include "GUI/Widgets/CodeEditor/Widget.CodeEditor.h"
#include "GUI/Widgets/ColorPicker/Widget.ColorPicker.h"
#include "GUI/Widgets/Disassembler/Widget.Disassembler.h"
#include "GUI/Widgets/EmulatorInfo/Widget.EmulatorInfo.h"
#include "GUI/Widgets/Help/Widget.Help.h"
#include "GUI/Widgets/HexViewer/Widget.HexViewer.h"
#include "GUI/Widgets/HistoryInstruction/Widget.HistoryInstruction.h"
#include "GUI/Widgets/Input0x08/Widget.Input0x08.h"
#include "GUI/Widgets/Keyboard/Widget.Keyboard.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "GUI/Widgets/MnemoCodeViewerTargeted/Widget.MnemoCodeViewerTargeted.h"
#include "GUI/Widgets/Output0x02/Widget.Output0x02.h"
#include "GUI/Widgets/PixelScreen/Widget.PixelScreen.h"
#include "GUI/Widgets/PixelScreenTwoBuffers/Widget.PixelScreenTwoBuffers.h"
#include "GUI/Widgets/RegisterFlagsInfo/Widget.RegisterFlagsInfo.h"
#include "GUI/Widgets/SymbolPicker/Widget.SymbolPicker.h"
#include "GUI/Widgets/SymbolScreen/Widget.SymbolScreen.h"
#include "GUI/Widgets/TableInstruction/Widget.TableInstruction.h"
#include "GUI/Widgets/Timer/Widget.Timer.h"
#include "GUI/Widgets/ListInstruction/Widget.ListInstruction.h"
#include "GUI/Widgets/ConstList/Widget.ListConst.h"
#include "GUI/Widgets/MarkerList/Widget.ListMarker.h"
#include "GUI/Widgets/VarList/Widget.ListVar.h"

#include "Utils/File/File.h"

#include "Data/Images/Image_LogoApplicationArrayPngBytes.h"

#include "GUI/MainMenuBar/MainMenuBar.h"

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