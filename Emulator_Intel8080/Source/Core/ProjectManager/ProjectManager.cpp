#include "ProjectManager.h"

#include "Core/Emulator/Processors/Intel8080/I8080.h"
#include "Core/Emulator/History/Caretaker.Momento.h"
#include "Core/Emulator/EmulationThread/EmulationThread.h"
#include "Core/Emulator/Compiler/Compiler.h"
#include "Core/LastPathManager/LastPathManager.h"


#include "GUI/Widgets/CodeEditor/TextEditor.h"

#include "Utils/File/File.h"
#include "Utils/Text/Encoding/Wstring/Wstring.h"

#include "GUI/Notification/NotificationManager.h"
#include "GUI/Widgets/MnemoCodeViewer/Widget.MnemoCodeViewer.h"
#include "GUI/Widgets/RegisterFlagsInfo/Widget.RegisterFlagsInfo.h"
#include "GUI/Widgets/CodeEditor/Widget.CodeEditor.h"


ProjectManager::ProjectManager(
	GLFWwindow* window,
	I8080* processor,
	NotificationManager* notificationManager,
	LastPathManager* lastPathManager,
	EmulationThread* emulationThread,
	Compiler* сompiler,
	Caretaker_Momento* processor_CaretakerMomento) : ISettingObject(u8"Проект",u8"Проект") {

	this->window = window;
	this->processor = processor;
	this->notificationManager = notificationManager;
	this->lastPathManager = lastPathManager;
	this->emulationThread = emulationThread;
	this->сompiler = сompiler;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
}

ProjectManager::~ProjectManager() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "ProjectManager::~ProjectManager()\n";
#endif // !WITH_DEBUG_OUTPUT
}

std::string ProjectManager::AutoSaveTiming_To_string(const AutoSaveTiming& ast) {
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
		return u8"Никогда";
		break;
	}
}
AutoSaveTiming  ProjectManager::string_To_AutoSaveTiming(const std::string text) {
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


void ProjectManager::InitWidgets(
	Widget_MnemocodeViewer* widget_MnemocodeViewer,
	Widget_RegisterFlagsInfo* widget_RegisterFlagsInfo,
	Widget_CodeEditor* widget_CodeEditor) {

	this->widget_MnemocodeViewer = widget_MnemocodeViewer;
	this->widget_RegisterFlagsInfo = widget_RegisterFlagsInfo;
	this->widget_CodeEditor = widget_CodeEditor;
}

void ProjectManager::NewFile() {
	translatorOutput.Clear();
	LinesCode.clear();

	widget_CodeEditor->GetPtrTextEditor()->SetTextLines(std::vector<std::string>{""});
	widget_CodeEditor->GetPtrTextEditor()->SetTextNotChanged();
	widget_CodeEditor->GetPtrTextEditor()->DeleteAllErrorMarkers();
	widget_CodeEditor->GetPtrTextEditor()->SetReadOnly(false);

	processor->ActiveFlagStop();
	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->Reset();
	processor->RemoveAllBreakPoints();
	processor->EraseMemory();

	processor->SetModeProject(ModeProject::USER);

	processor_CaretakerMomento->ClearHistory();

	widget_MnemocodeViewer->FollowCursor(0);

	Path_LoadedFile.clear();
	widget_RegisterFlagsInfo->InitLastState();

	UpdateTitleWindow();



	static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
	static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

	std::string text = u8"Создан новый проект.";

	notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
		new N_Message(color_WHITE, text)
	},
		nullptr));

}
bool ProjectManager::OpenFileWithPath(const std::string& path) {
	if (path.size() != 0) {

		translatorOutput.Clear();
		LinesCode.clear();

		std::string ExtensionFile = path.substr(path.find_last_of('.') + 1);
		ToLowerAll(ExtensionFile);


		processor->ActiveFlagStop();
		emulationThread->SetControlMode(ControlMode::Stop);
		emulationThread->WaitThread();
		processor->ActiveFlagStop();
		processor->Reset();
		processor->RemoveAllBreakPoints();
		processor->EraseMemory();
		widget_RegisterFlagsInfo->InitLastState();
		processor_CaretakerMomento->ClearHistory();

		widget_MnemocodeViewer->FollowCursor(0);

		Path_LoadedFile = path;
		UpdateTitleWindow();
		lastPathManager->AddPath(path);


		if (ExtensionFile == "i8080")
		{
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllErrorMarkers();
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();
			widget_CodeEditor->GetPtrTextEditor()->SetReadOnly(false);

			ReadFile(path);

			if (flag_CompileAfterOpen == true)
				TryTranslateCode();

			widget_CodeEditor->SetFlagWindow(0);

		}
		else if (ExtensionFile == "com") {
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllErrorMarkers();
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();
			widget_CodeEditor->GetPtrTextEditor()->SetTextLines({});
			widget_CodeEditor->GetPtrTextEditor()->SetReadOnly(true);

			auto data = ReadFileToByteArray(path);

			processor->LoadMemoryFromCOM(data);
		}
		else if (ExtensionFile == "bin") {

			widget_CodeEditor->GetPtrTextEditor()->DeleteAllErrorMarkers();
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();
			widget_CodeEditor->GetPtrTextEditor()->SetTextLines({});
			widget_CodeEditor->GetPtrTextEditor()->SetReadOnly(true);

			auto data = ReadFileToByteArray(path);

			processor->LoadMemoryFromBinary(data);
		}

		
		if (wasFirstUpdate) {

			static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

			std::string text = u8"Файл успешно открыт.";

			notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, text)
			},
				nullptr));

		}


		return true;
	}
	return false;
}
void ProjectManager::OpenFile() {
	std::wstring path = Open_FileDialog(L"Выбери файл проекта для открытия",L"Файл с ассемблерным кодом (.I8080)\0*.I8080;*.BIN;*.COM\0");
	OpenFileWithPath(wstring_to_stringUTF8(path));
}



void ProjectManager::SaveFile() {

	if (processor->GetModeProject() != ModeProject::USER){

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		std::string text = u8"Нельзя сохранять бинарные файлы их можно лишь открыть.";

		notificationManager->AddNottification(Notification(color_RED, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));

		return;
	}

	if (Path_LoadedFile.empty()) {
		SaveFileAs();
	}
	else {
		LinesCode = widget_CodeEditor->GetPtrTextEditor()->GetTextLines();

		widget_CodeEditor->SetFlagWindow(0);
		std::ofstream ofn;
		ofn.open(stringUTF8_to_wstring(Path_LoadedFile));

		for (int i = 0; i < LinesCode.size(); i++){
			if (i == LinesCode.size() - 1)
				ofn << LinesCode[i];
			else
				ofn << LinesCode[i] << std::endl;
		}

		ofn.close();

		if (wasFirstUpdate)
		{
			static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

			std::string text = u8"Файл сохранён.";

			notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, text)
			},
				nullptr));
		}

	}
}
void ProjectManager::SaveFileAs() {

	if (processor->GetModeProject() != ModeProject::USER) {

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		std::string text = u8"Нельзя сохранять бинарные файлы их можно лишь открыть.";

		notificationManager->AddNottification(Notification(color_RED, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));

		return;
	}


	std::string nameFile = Save_FileDialog(u8"Выбери путь для сохранения", u8"Файл с ассемблерным кодом (.I8080)\0*.I8080;");

	if (nameFile.empty()) {
		return;
	}

	widget_CodeEditor->SetFlagWindow(0);

	std::string Path2NewFile = nameFile + ".I8080";

	lastPathManager->AddPath(Path2NewFile);

	LinesCode = widget_CodeEditor->GetPtrTextEditor()->GetTextLines();
	std::ofstream ofn;
	ofn.open(stringUTF8_to_wstring(Path2NewFile));


	for (int i = 0; i < LinesCode.size(); i++) {
		if (i == LinesCode.size() - 1)
			ofn << LinesCode[i];
		else
			ofn << LinesCode[i] << std::endl;
	}


	ofn.close();


	if (wasFirstUpdate)
	{
		static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		std::string text = u8"Файл сохранён.";

		notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));
	}



	Path_LoadedFile = Path2NewFile;
	UpdateTitleWindow();

	ReadFile(Path_LoadedFile);
	TryTranslateCode();

	processor->Reset();
	processor->LoadMemory(translatorOutput.Opcodes);

	widget_RegisterFlagsInfo->InitLastState();

}
void ProjectManager::SaveFileIntoBinary() {

	TryTranslateCode();
	if (translatorOutput.Error != TypeTranslatorError::NOTHING)
		return;


	std::string path = Save_FileDialog(u8"Выбери путь для сохранения", u8"Бинарный файл (.BIN)\0*.BIN;");
	if (path.empty())
		return;

	path += ".BIN";

	std::vector<uint8_t> data;

	int max = 0;
	for (int i = 65535; i >= 0; i--){
		if (processor->GetMemory()[i] != 0x00){
			max = i;
			break;
		}
	}
	
	for (int i = 0; i < max + 1; i++)
		data.emplace_back(processor->GetMemory()[i]);


	std::ofstream file(stringUTF8_to_wstring(path), std::ios::binary);

	if (!file) {
#ifdef _DEBUG
		std::cerr << "Error opening file for writing: " << path << std::endl;
#endif
		return;
	}

	file.write(reinterpret_cast<const char*>(data.data()), data.size());

	file.close();



}


void ProjectManager::Compile() {

	if (processor->GetModeProject() != ModeProject::USER) {

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		std::string text = u8"Нельзя компилировать бинарные файлы, ведь они уже откомпилированны...";

		notificationManager->AddNottification(Notification(color_RED, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));

		return;
	}

	TryTranslateCode();
	widget_MnemocodeViewer->FollowCursorPC();
}

void ProjectManager::DrawSetting() {
	//ImGui::SeparatorText(u8"Проект");

	if (ImGui::RadioButton(u8"Сохранять при компиляции", flag_SaveAfterCompile)) {
		flag_SaveAfterCompile = !flag_SaveAfterCompile;
	}
	if (ImGui::RadioButton(u8"Загружать последний открытый файл при запуске приложения", flag_OpenLastFileWithOpenProgramm)) {
		flag_OpenLastFileWithOpenProgramm = !flag_OpenLastFileWithOpenProgramm;
	}
	if (ImGui::RadioButton(u8"Компилировать файл сразу после его открытия", flag_CompileAfterOpen)) {
		flag_CompileAfterOpen = !flag_CompileAfterOpen;
	}


	std::string Selected = AutoSaveTiming_To_string(setedAutoTiming);


	std::vector<std::pair<std::string,AutoSaveTiming>> Type_time = {
			{u8"30 секунд", AutoSaveTiming::ThirtySeconds},
			{u8"1 минута", AutoSaveTiming::OneMinute},
			{u8"5 минут", AutoSaveTiming::FiveMinute},
			{u8"10 минут", AutoSaveTiming::TenMinute},
			{u8"15 минут", AutoSaveTiming::FifteenMinute},
			{u8"30 минут", AutoSaveTiming::ThirtyMinute},
			{u8"1 час", AutoSaveTiming::OneHour},
			{u8"Никогда", AutoSaveTiming::Never}
	};

	if (ImGui::BeginCombo(u8"Время автосохранения", Selected.c_str(), ImGuiComboFlags_WidthFitPreview)) {

		for (int i = 0; i < Type_time.size(); i++)
		{
			bool selected = Selected == Type_time[i].first;

			if (ImGui::Selectable(Type_time[i].first.c_str(),&selected))
				setedAutoTiming = Type_time[i].second;

			if (selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}


}

void ProjectManager::Update() {
	wasFirstUpdate = true;

	static float startTimer = (float)glfwGetTime();

	if (AutoTimingAchived(startTimer)) {
		startTimer = (float)glfwGetTime();

		if (Path_LoadedFile.empty())
			return;

		SaveFile();
	}

}

TranslatorOutput* ProjectManager::GetPtrTranslatorOutput() {
	return &translatorOutput;
}


bool ProjectManager::AutoTimingAchived(const float& timeStart) {
	float timeCurrent = (float)glfwGetTime();
	float elapsed = timeCurrent - timeStart;

	switch (setedAutoTiming)
	{
	case AutoSaveTiming::ThirtySeconds:
		if (elapsed > 30.f)
			return true;
		break;
	case AutoSaveTiming::OneMinute:
		if (elapsed > 60.f)
			return true;
		break;
	case AutoSaveTiming::FiveMinute:
		if (elapsed > 60.f * 5.f)
			return true;
		break;
	case AutoSaveTiming::TenMinute:
		if (elapsed > 60.f * 10.f)
			return true;
		break;
	case AutoSaveTiming::FifteenMinute:
		if (elapsed > 60.f * 15.f)
			return true;
		break;
	case AutoSaveTiming::ThirtyMinute:
		if (elapsed > 60.f * 30.f)
			return true;
		break;
	case AutoSaveTiming::OneHour:
		if (elapsed > 60.f * 60.f)
			return true;
		break;
	case AutoSaveTiming::Never:
		return false;
		break;
	default:
		break;
	}
	return false;

}



void ProjectManager::ReadFile(const std::string& path) {
	LinesCode.clear();

	std::ifstream t;
	t.open(stringUTF8_to_wstring(path));
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	t.close();




	widget_CodeEditor->GetPtrTextEditor()->SetText(str);
	widget_CodeEditor->GetPtrTextEditor()->SetLanguageDefinition(TextEditor::LanguageDefinition::I8080());
	widget_CodeEditor->GetPtrTextEditor()->SetTextNotChanged();
	
}

void ProjectManager::TryTranslateCode() {
	std::chrono::system_clock::time_point clock_start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point clock_end = std::chrono::system_clock::now();

	emulationThread->SetControlMode(ControlMode::Stop);


	if (Path_LoadedFile.empty() == false && flag_SaveAfterCompile == true)
		SaveFile();

	widget_CodeEditor->SetFlagWindow(0);
	LinesCode = widget_CodeEditor->GetPtrTextEditor()->GetTextLines();

	translatorOutput = сompiler->Compile(LinesCode);


	processor->ActiveFlagStop();
	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();


	processor->Reset();
	processor->RemoveAllBreakPoints();
	processor->EraseMemory();
	processor_CaretakerMomento->ClearHistory();

	if (translatorOutput.Error != TypeTranslatorError::NOTHING) {
		translatorOutput.Opcodes.clear();

		TextEditor::ErrorMarkers line_error;

		line_error.insert({ translatorOutput.LineError + 1,GetErrorInfo(translatorOutput.Error) });
		widget_CodeEditor->GetPtrTextEditor()->SetErrorMarkers(line_error);

		TextEditor::Coordinates coord;
		coord.mLine = 0;

		widget_CodeEditor->GetPtrTextEditor()->SetCursorPosition(coord);
		coord.mLine = translatorOutput.LineError;

		widget_CodeEditor->GetPtrTextEditor()->SetCursorPosition(coord);


		if (wasFirstUpdate)
		{
			static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

			std::string UNsuccess = u8"При компиляции найдена ошибка.\nНомер строки в коде: " + std::to_string(coord.mLine + 1) + u8"\nОписание: " + GetErrorInfo(translatorOutput.Error);

			notificationManager->AddNottification(Notification(color_RED, 3.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, UNsuccess)
			},
				nullptr));
		}
	}



	widget_RegisterFlagsInfo->InitLastState();
	widget_MnemocodeViewer->FollowCursorPC();

	if (translatorOutput.LineError == 0 && translatorOutput.Error == 0) {
		processor->Reset();
		processor->RemoveAllBreakPoints();
		processor->LoadMemory(translatorOutput.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();

		auto breaks = widget_CodeEditor->GetPtrTextEditor()->GetBreakpoints();

		for (int i = 0; i < breaks.size(); i++) {

			if (breaks[i]-1 > translatorOutput.Line_and_Adress.size())
				continue;

			int adressBreak = translatorOutput.Line_and_Adress[breaks[i] - 1];
			if (adressBreak != -1)
				processor->SetBreakPointPosition(adressBreak, BreakPointStates::Enabled);
		}

	}

	clock_end = std::chrono::system_clock::now();
	float timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds> (clock_end - clock_start).count() / 1000.f;

	if (translatorOutput.LineError == 0 && translatorOutput.Error == 0) {

		// Creating Notification - Compilation Success

		if (wasFirstUpdate)
		{
			static const ImVec4 color_GREEN{ 0.2f,0.45f,0.2f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };
			std::string success = u8"Компиляция прошла успешно.";
			std::string time_info = u8"Затраченное время: " + cutFloat(std::to_string(timeElapsed), 4) + u8" сек.";

			notificationManager->AddNottification(Notification(color_GREEN, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, success),
					new N_Message(color_WHITE, time_info),
					new N_Progress(color_WHITE, u8"Память", u8" байт", (float)translatorOutput.Opcodes.size(), 65535.f, false)
			},
				nullptr));
		}

	}

}

void ProjectManager::UpdateTitleWindow() {
	if (Path_LoadedFile.empty())
		glfwSetWindowTitle(window, u8"Эмулятор процессора I8080");
	else
		glfwSetWindowTitle(window, (u8"Эмулятор процессора I8080 -> " + Path_LoadedFile).c_str());
}



nlohmann::json ProjectManager::SaveSetting() {
	nlohmann::json result;

	result["flag_OpenLastFileWithOpenProgramm"] = flag_OpenLastFileWithOpenProgramm;
	result["flag_SaveAfterCompile"] = flag_SaveAfterCompile;
	result["flag_CompileAfterOpen"] = flag_CompileAfterOpen;
	result["setedAutoTiming"] = AutoSaveTiming_To_string(setedAutoTiming);
	if (Path_LoadedFile.empty() == false)
		result["LastLoadedPathFile"] = Path_LoadedFile;

	return result;
}

void ProjectManager::LoadSetting(const nlohmann::json& Data) {

	if (Data.contains("flag_OpenLastFileWithOpenProgramm"))
		flag_OpenLastFileWithOpenProgramm = Data["flag_OpenLastFileWithOpenProgramm"].get<bool>();

	if (Data.contains("flag_SaveAfterCompile"))
		flag_SaveAfterCompile = Data["flag_SaveAfterCompile"].get<bool>();

	if (Data.contains("flag_CompileAfterOpen"))
		flag_CompileAfterOpen = Data["flag_CompileAfterOpen"].get<bool>();

	if (Data.contains("setedAutoTiming"))
		setedAutoTiming = string_To_AutoSaveTiming(Data["setedAutoTiming"].get<std::string>());

	if (Data.contains("LastLoadedPathFile")) {
		std::string path_temp = Data["LastLoadedPathFile"].get<std::string>();

		if (path_temp.empty() == false && flag_OpenLastFileWithOpenProgramm == true) {

			if (isFileExist(path_temp))
				OpenFileWithPath(path_temp);
		}

	}

}
