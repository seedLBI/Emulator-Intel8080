#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <robin_hood.h>
#include <string>
#include <vector>
#include <chrono>

#include "Core/Setting/interfaces/ISettingObject.h"
#include "Core/SaveSystem/SaveSystem.h"

#include "DataStructures/TranslatorOutput.h"

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


struct GLFWwindow;
class I8080;
class NotificationManager;
class LastPathManager;
class EmulationThread;
class Compiler;
class Caretaker_Momento;

class Widget_MnemocodeViewer;
class Widget_RegisterFlagsInfo;
class Widget_CodeEditor;

class ProjectManager : public ISettingObject
{
public:
	ProjectManager(
		GLFWwindow* window,
		I8080* processor,
		NotificationManager* notificationManager,
		LastPathManager* LastPathManager,
		EmulationThread* emulationThread,
		Compiler* ñompiler, 
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
	Compiler* ñompiler = nullptr;
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



	std::string		AutoSaveTiming_To_string(const AutoSaveTiming& ast);
	AutoSaveTiming	string_To_AutoSaveTiming(const std::string text);

	bool AutoTimingAchived(const float& timeStart);



	void ReadFile(const std::string& path);

	void TryTranslateCode();

	void UpdateTitleWindow();
};




#endif
