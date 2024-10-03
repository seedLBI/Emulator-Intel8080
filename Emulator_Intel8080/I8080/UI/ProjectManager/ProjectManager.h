#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H


#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include "SaveSystem/SaveSystem.h"
#include "Emulator/I8080.h"
#include "Emulator/EmulationThread/EmulationThread.h"
#include "Emulator/Compilier/Stable/Compiler.Stable.h"

#include "DataStructures/TranslatorOutput.h"
#include "TextEditor.h"
#include "Notification/NotificationManager.h"
#include "UI/LastPathManager/LastPathManager.h"

#include "Utils/File_Utils.h"


#include "UI\Widgets\I8080.UI.MnemoCodeViewer.h"
#include "UI\Widgets\I8080.UI.RegisterFlagsInfo.h"
#include "UI\Widgets\I8080.UI.CodeEditor.h"

#include "robin_hood.h"



#include <string>
#include <vector>
#include <chrono>


enum class AutoSaveTiming {
	ThirtySeconds,
	OneMinute,
	FiveMinute,
	TenMinute,
	FifteenMinute,
	ThirtyMinute,
	OneHour,
	Never
};


class ProjectManager : public SaveSystem
{
public:
	ProjectManager(GLFWwindow* window,I8080* processor,NotificationManager* notificationManager,LastPathManager* LastPathManager,EmulationThread* emulationThread,CompilerStable* Compiler);

	~ProjectManager();

	void InitWidgets(
		Widget_MnemocodeViewer* widget_MnemocodeViewer,
		Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo,
		Widget_CodeEditor* widget_CodeEditor);

	void NewFile();
	bool OpenFileWithPath(const std::string& path);
	void OpenFile();
	void SaveFile();
	void SaveFileAs();

	void Compile();

	void DrawSetting();
	void Update();

	TranslatorOutput* GetPtrTranslatorOutput();


	std::string Save() override;
	void Load(const std::string& Data) override;

private:
	GLFWwindow* window = nullptr;
	I8080* processor = nullptr;
	NotificationManager* notificationManager = nullptr;
	LastPathManager* lastPathManager = nullptr;
	EmulationThread* emulationThread = nullptr;
	CompilerStable* Compiler = nullptr;

	Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo = nullptr;
	Widget_CodeEditor* widget_CodeEditor = nullptr;
	Widget_MnemocodeViewer* widget_MnemocodeViewer = nullptr;

	bool wasFirstUpdate = false;

	std::string Path_LoadedFile;


	std::vector<std::string> LinesCode;
	TranslatorOutput translatorOutput;


	bool flag_OpenLastFileWithOpenProgramm = false;
	bool flag_SaveAfterCompile = true;
	bool flag_CompileAfterOpen = true;
	AutoSaveTiming setedAutoTiming = AutoSaveTiming::OneMinute;



	std::string AutoSaveTiming_To_string(const AutoSaveTiming& ast) {
		switch (ast)
		{
		case AutoSaveTiming::ThirtySeconds:
			return u8"30 секунд";
			break;
		case AutoSaveTiming::OneMinute:
			return u8"1 минута";
			break;
		case AutoSaveTiming::FiveMinute:
			return u8"5 минут";
			break;
		case AutoSaveTiming::TenMinute:
			return u8"10 минут";
			break;
		case AutoSaveTiming::FifteenMinute:
			return u8"15 минут";
			break;
		case AutoSaveTiming::ThirtyMinute:
			return u8"30 минут";
			break;
		case AutoSaveTiming::OneHour:
			return u8"1 час";
			break;
		case AutoSaveTiming::Never:
			return u8"Ќикогда";
			break;
		default:
			break;
		}
	}
	AutoSaveTiming string_To_AutoSaveTiming(const std::string text) {
		robin_hood::unordered_flat_map<std::string, AutoSaveTiming> values = {
			{u8"30 секунд", AutoSaveTiming::ThirtySeconds},
			{u8"1 минута", AutoSaveTiming::OneMinute},
			{u8"5 минут", AutoSaveTiming::FiveMinute},
			{u8"10 минут", AutoSaveTiming::TenMinute},
			{u8"15 минут", AutoSaveTiming::FifteenMinute},
			{u8"30 минут", AutoSaveTiming::ThirtyMinute},
			{u8"1 час", AutoSaveTiming::OneHour},
			{u8"Ќикогда", AutoSaveTiming::Never}
		};

		if (values.contains(text))
			return values[text];
		else
			return AutoSaveTiming::Never;

	}


	bool AutoTimingAchived(const float& timeStart);



	void ReadFile(const std::string& path);

	void TryTranslateCode();

	void UpdateTitleWindow();
};




#endif
