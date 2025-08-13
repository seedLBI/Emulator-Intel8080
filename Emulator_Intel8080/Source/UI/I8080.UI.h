#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "Config_Compilier.h"

#include "OpenglWindow/OpenglWindow.h"

#include "ThirdParty/LodePNG/lodepng.h"

#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_impl_glfw.h"
#include "ThirdParty/ImGui/imgui_impl_opengl3.h"
#include "ThirdParty/ImGui/imgui_memory_editor.h"
#include "ThirdParty/ImGui/imgui_markdown.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include "ThirdParty/IconFontCppHeaders/IconsFontAwesome6.h"
#include "ThirdParty/TextEditor.h"

#include "Utils/OpenGL/PBO/PBO.h"
#include "Utils/ImGui.Utils.h"
#include "Utils/ColorUtilities.h"

#include "DataStructures/TypesCommand.h"

#include "GUI/Widgets/I8080.UI.ColorPicker.h"
#include "GUI/Widgets/I8080.UI.SymbolPicker.h"
#include "GUI/Widgets/I8080.UI.MarkerList.h"
#include "GUI/Widgets/I8080.UI.VarList.h"
#include "GUI/Widgets/I8080.UI.ConstList.h"
#include "GUI/Widgets/I8080.UI.CodeEditor.h"
#include "GUI/Widgets/I8080.UI.HexViewer.h"
#include "GUI/Widgets/I8080.UI.Keyboard.h"
#include "GUI/Widgets/I8080.UI.Input0x08.h"
#include "GUI/Widgets/I8080.UI.Output0x02.h"
#include "GUI/Widgets/I8080.UI.Timer.h"
#include "GUI/Widgets/I8080.UI.MnemoCodeViewer.h"
#include "GUI/Widgets/I8080.UI.MnemoCodeViewerTargeted.h"
#include "GUI/Widgets/I8080.UI.RegisterFlagsInfo.h"
#include "GUI/Widgets/I8080.UI.EmulatorInfo.h"
#include "GUI/Widgets/I8080.UI.SymbolScreen.h"
#include "GUI/Widgets/I8080.UI.PixelScreen.h"
#include "GUI/Widgets/I8080.UI.PixelScreenTwoBuffers.h"
#include "GUI/Widgets/I8080.UI.Help.h"
#include "GUI/Widgets/I8080.UI.Disassembler.h"
#include "GUI/Widgets/UI.HistoryInstruction.h"
#include "GUI/Widgets/UI.ListInstruction.h"
#include "GUI/Widgets/UI.TableInstruction.h"
#include "GUI/HighlighterInstruction/I8080/I8080.HighlighterInstruction.h"
#include "GUI/Notification/NotificationManager.h"
#include "GUI/AuthorPopup/AuthorPopup.h"
#include "GUI/MainMenuBar/MainMenuBar.h"

#include "Core/Widget/I8080.WidgetManager.h"
#include "Core/Workspaces/I8080.WorkspaceManager.h"
#include "Core/LastPathManager/LastPathManager.h"
#include "Core/SaveSystem/SaveSystemManager.h"
#include "Core/FontManager/FontManager.h"
#include "Core/WindowManager/WindowManager.h"
#include "Core/KeyCombination/KeyCombinationHandler.h"
#include "Core/ProjectManager/ProjectManager.h"
#include "Core/Setting/Setting.h"
#include "Core/Theme/ThemeManager/ThemeManager.h"
#include "Core/Theme/BaseColors/BaseColors.h"
#include "Core/IntroManager/IntroManager.h"
#include "Core/Emulator/Processors/Intel8080/History/Caretaker/Caretaker.Momento.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/Processors/Intel8080/Compiler/Compiler.h"
#include "Core/Emulator/EmulationControls/EmulationControls.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"





#ifndef I8080_UI_H
#define I8080_UI_H


class I8080_UserInterface
{
public:
	bool ExitButton = false;



	I8080_UserInterface(GLFWwindow* window);
	~I8080_UserInterface();

	bool isNeedDrawIntro();

	void Draw();
	void Update();

	bool OpenFileFromPath(string path);
private:
	bool NeedDrawIntro = true;

	void BeginDraw();
	void EndDraw();

	void DrawMainMenu();

	void InitSetting();
	void InitThemeManager();
	void InitWidgets();
	void InitSaveManager();
	void InitKeyCombinationHandler();

	bool FullLoaded = false;

	AuthorPopup authorPopup;

	GLFWwindow*					  window = nullptr;
	I8080*						  processor = nullptr;
	I8080_Caretaker_Momento*	  processorCaratakerMomento = nullptr;
	I8080_Compiler*				  Compiler = nullptr;
	EmulationThread*			  emulationThread = nullptr;
	EmulationControls*			  emulationControls = nullptr;



	IntroManager*				  introManager = nullptr;
	SaveSystemManager*			  saveSystemManager = nullptr;
	NotificationManager*		  notificationManager = nullptr;
	FontManager*				  font_manager = nullptr;
	WindowManager*				  window_manager = nullptr;
	KeyCombinationHandler*		  keyCombination_handler = nullptr;
	ProjectManager*				  projectManager = nullptr;
	Setting*					  settings = nullptr;
	ThemeManager*				  themeManager = nullptr;
	BaseColors*					  baseColors = nullptr;



	LastPathManager*			  lastPathManager = nullptr;
	I8080_WorkspaceManager*		  WorkspaceManager = nullptr;
	I8080_WidgetManager			  WidgetManager;


	// base widgets
	Widget_Help*						widget_Help = nullptr;
	Widget_VarList*						widget_VarList = nullptr;
	Widget_HexViewer*					widget_HexViewer = nullptr;
	Widget_ConstList*					widget_ConstList = nullptr;
	Widget_CodeEditor*					widget_CodeEditor = nullptr;
	Widget_MarkerList*					widget_MarkerList = nullptr;
	Widget_Disassembler*				widget_Disassembler = nullptr;
	Widget_EmulatorInfo*				widget_EmulatorInfo = nullptr;
	Widget_MnemocodeViewer*				widget_MnemocodeViewer = nullptr;
	Widget_ListInstruction*				widget_ListInstruction = nullptr;
	Widget_TableInstruction*			widget_TableInstruction = nullptr;
	Widget_RegisterFlagsInfo*			widget_RegisterFlagsInfo = nullptr;
	Widget_HistoryInstruction*			widget_HistoryInstruction = nullptr;
	Widget_MnemocodeViewerTargeted*		widget_MnemocodeViewerTargeted = nullptr;

	// port widgets
	Widget_Timer*				  widget_timer = nullptr;
	Widget_Keyboard*			  widget_keyboard = nullptr;
	Widget_Input0x08*			  widget_input0x08 = nullptr;
	Widget_Output0x02*			  widget_output0x02 = nullptr;
	Widget_PixelScreen*			  widget_PixelScreen = nullptr;
	Widget_SymbolScreen*		  widget_SymbolScreen = nullptr;
	Widget_PixelScreenTwoBuffers* widget_PixelScreenTwoBuffers = nullptr;


	// port widgets (helper)
	Widget_ColorPicker*			  widget_ColorPicker = nullptr;
	Widget_SymbolPicker*		  widget_SymbolPicker = nullptr;
};



#endif // !I8080_UI_H