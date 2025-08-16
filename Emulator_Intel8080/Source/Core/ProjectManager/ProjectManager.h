#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#define _HAS_STD_BYTE 0

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"
#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Compiler/Compiler.h"
#include "Core/LastPathManager/LastPathManager.h"


#include "DataStructures/TranslatorOutput.h"
#include "GUI/Widgets/CodeEditor/TextEditor.h"

#include "Utils/File/File.h"
#include "Utils/Text/Encoding/Wstring/Wstring.h"

#include "GUI/Notification/NotificationManager.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "GUI/Widgets/RegisterFlagsInfo/Widget.RegisterFlagsInfo.h"
#include "GUI/Widgets/CodeEditor/Widget.CodeEditor.h"

#include <robin_hood.h>
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


class ProjectManager : public ISettingObject
{
public:
	ProjectManager(
		GLFWwindow* window,
		I8080* processor,
		NotificationManager* notificationManager,
		LastPathManager* LastPathManager,
		EmulationThread* emulationThread,
		Compiler* сompiler, 
		Caretaker_Momento* processor_CaretakerMomento);

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
	void SaveFileIntoBinary();

	void Compile();


	void Update();

	TranslatorOutput* GetPtrTranslatorOutput();


	void DrawSetting() override;
	nlohmann::json SaveSetting() override;
	void LoadSetting(const nlohmann::json& Data) override;

private:
	GLFWwindow* window = nullptr;
	I8080* processor = nullptr;
	NotificationManager* notificationManager = nullptr;
	LastPathManager* lastPathManager = nullptr;
	EmulationThread* emulationThread = nullptr;
	Compiler* сompiler = nullptr;
	Caretaker_Momento* processor_CaretakerMomento;

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
	AutoSaveTiming setedAutoTiming = AutoSaveTiming::FiveMinute;



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
			return u8"Никогда";
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
			{u8"Никогда", AutoSaveTiming::Never}
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
