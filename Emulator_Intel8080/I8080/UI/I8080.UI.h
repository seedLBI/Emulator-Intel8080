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


#include "Emulator/I8080.h"
#include "Emulator/Compilier/Stable/Compiler.Stable.h"
#include "Emulator/EmulationThread/EmulationThread.h"


#include "Utils\ColorUtilities.h"

#include "Shellapi.h"
#include "PBO.h"
#include "DataStructures\TypesCommand.h"

#include "Utils\ImGui.Utils.h"



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
#include "UI\Widgets\I8080.UI.Disassembler.h"

#include "UI\Widget\I8080.WidgetManager.h"
#include "UI\Workspaces\I8080.WorkspaceManager.h"
#include "UI\LastPathManager\LastPathManager.h"

#include "SaveSystem\SaveSystemManager.h"

#include "UI\FontManager\FontManager.h"
#include "UI\WindowManager\WindowManager.h"
#include "UI\KeyCombination\KeyCombinationHandler.h"
#include "UI\ProjectManager\ProjectManager.h"
#include "UI\Setting\Setting.h"

#include "Notification/NotificationManager.h"

#include "AuthorPopup/AuthorPopup.h"



#ifndef I8080_UI_H
#define I8080_UI_H


class I8080_UserInterface
{
public:
	bool ExitButton = false;

	I8080_UserInterface(GLFWwindow* window);
	~I8080_UserInterface();

	void Draw();
	void Update();

	bool OpenFileFromPath(string path);
private:
	void BeginDraw();
	void EndDraw();



	void Emulator_Play();
	void Emulator_Pause();
	void Emulator_Stop();
	void Emulator_Next_step();
	void Emulator_FullReset();


	void DrawMainMenu();


	void InitWidgets();
	void InitSaveManager();
	void InitKeyCombinationHandler();

	AuthorPopup authorPopup;

	GLFWwindow*					  window = nullptr;
	I8080*						  processor = nullptr;
	CompilerStable*				  Compiler = nullptr;
	EmulationThread*			  emulationThread = nullptr;

	SaveSystemManager*			  saveSystemManager = nullptr;

	NotificationManager*		  notificationManager = nullptr;
	FontManager*			      font_manager = nullptr;
	WindowManager*				  window_manager = nullptr;
	KeyCombinationHandler*		  keyCombination_handler = nullptr;
	ProjectManager*				  projectManager = nullptr;
	Setting*					  settings = nullptr;

	LastPathManager*			  lastPathManager = nullptr;
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
	Widget_Disassembler*          widget_Disassembler = nullptr;

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