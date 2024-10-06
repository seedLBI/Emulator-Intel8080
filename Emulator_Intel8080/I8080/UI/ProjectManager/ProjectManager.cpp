#include "UI/ProjectManager/ProjectManager.h"


ProjectManager::ProjectManager(
	GLFWwindow* window,
	I8080* processor,
	NotificationManager* notificationManager,
	LastPathManager* lastPathManager,
	EmulationThread* emulationThread,
	CompilerStable* Compiler) : SaveSystem("ProjectManager") {

	this->window = window;
	this->processor = processor;
	this->notificationManager = notificationManager;
	this->lastPathManager = lastPathManager;
	this->emulationThread = emulationThread;
	this->Compiler = Compiler;

}

ProjectManager::~ProjectManager() {

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
	translatorOutput.Opcodes.clear();
	LinesCode.clear();

	widget_CodeEditor->GetPtrTextEditor()->SetTextLines(std::vector<std::string>{""});
	widget_CodeEditor->GetPtrTextEditor()->SetTextNotChanged();

	processor->Reset();
	processor->LoadMemory(translatorOutput.Opcodes);

	Path_LoadedFile.clear();
	widget_RegisterFlagsInfo->InitLastState();

	UpdateTitleWindow();


	static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
	static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

	string text = u8"Создан новый проект.";

	notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
		new N_Message(color_WHITE, text)
	},
		nullptr));

}
bool ProjectManager::OpenFileWithPath(const std::string& path) {
	if (path.size() != 0) {
		lastPathManager->AddPath(path);
		Path_LoadedFile = path;
		UpdateTitleWindow();
		ReadFile(path);

		if (flag_CompileAfterOpen == true)
			TryTranslateCode();


		widget_CodeEditor->SetFlagWindow(0);
		processor->Reset();
		processor->LoadMemory(translatorOutput.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();

		if (wasFirstUpdate)
		{

		static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Файл успешно открыт.";

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
	string path = OpenFileDialog();
	OpenFileWithPath(path);
}
void ProjectManager::SaveFile() {
	if (Path_LoadedFile.empty()) {
		SaveFileAs();
	}
	else {
		LinesCode = widget_CodeEditor->GetPtrTextEditor()->GetTextLines();

		widget_CodeEditor->SetFlagWindow(0);
		ofstream ofn;
		ofn.open(stringUTF8_to_wstring(Path_LoadedFile));

		for (int i = 0; i < LinesCode.size(); i++){
			if (i == LinesCode.size() - 1)
				ofn << LinesCode[i];
			else
				ofn << LinesCode[i] << endl;
		}

		ofn.close();

		if (wasFirstUpdate)
		{
			static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

			string text = u8"Файл сохранён.";

			notificationManager->AddNottification(Notification(color_GRAY, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, text)
			},
				nullptr));
		}

	}
}
void ProjectManager::SaveFileAs() {
	string nameFile = SaveFileDialogI8080();

	if (nameFile.empty()) {
		return;
	}

	widget_CodeEditor->SetFlagWindow(0);

	string Path2NewFile = nameFile + ".I8080";

	lastPathManager->AddPath(Path2NewFile);

	LinesCode = widget_CodeEditor->GetPtrTextEditor()->GetTextLines();
	ofstream ofn;
	ofn.open(stringUTF8_to_wstring(Path2NewFile));


	for (int i = 0; i < LinesCode.size(); i++) {
		if (i == LinesCode.size() - 1)
			ofn << LinesCode[i];
		else
			ofn << LinesCode[i] << endl;
	}


	ofn.close();


	if (wasFirstUpdate)
	{
		static const ImVec4 color_GRAY{ 0.3f,0.3f,0.3f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Файл сохранён.";

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

void ProjectManager::Compile() {
	TryTranslateCode();
	widget_MnemocodeViewer->FollowCursorPC();
}

void ProjectManager::DrawSetting() {
	ImGui::SeparatorText(u8"Проект");

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

	static float startTimer = glfwGetTime();

	if (AutoTimingAchived(startTimer)) {
		startTimer = glfwGetTime();

		if (Path_LoadedFile.empty())
			return;

		SaveFile();
	}

}

TranslatorOutput* ProjectManager::GetPtrTranslatorOutput() {
	return &translatorOutput;
}


bool ProjectManager::AutoTimingAchived(const float& timeStart) {
	float timeCurrent = glfwGetTime();
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

	translatorOutput = Compiler->Compile(LinesCode);


	emulationThread->SetControlMode(ControlMode::Stop);
	emulationThread->WaitThread();

	processor->ActiveFlagStop();
	processor->Reset();
	processor->EraseMemory();


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

			string UNsuccess = u8"При компиляции найдена ошибка.\nНомер строки в коде: " + std::to_string(coord.mLine + 1) + u8"\nОписание: " + GetErrorInfo(translatorOutput.Error);

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
		processor->LoadMemory(translatorOutput.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();
	}

	clock_end = std::chrono::system_clock::now();
	float timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds> (clock_end - clock_start).count() / 1000.f;

	if (translatorOutput.LineError == 0 && translatorOutput.Error == 0) {

		// Creating Notification - Compilation Success

		if (wasFirstUpdate)
		{
			static const ImVec4 color_GREEN{ 0.2f,0.45f,0.2f,1.0f };
			static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };
			string success = u8"Компиляция прошла успешно.";
			string time_info = u8"Затраченное время: " + cutFloat(std::to_string(timeElapsed), 4.f) + u8" сек.";

			notificationManager->AddNottification(Notification(color_GREEN, 2.f, std::vector<N_Element*>{
				new N_Message(color_WHITE, success),
					new N_Message(color_WHITE, time_info),
					new N_Progress(color_WHITE, u8"Память", u8" байт", translatorOutput.Opcodes.size(), 65535.f, false)
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



std::string ProjectManager::Save() {
	std::string output = "";

	int countLines = 0;

	if (Path_LoadedFile.empty())
		countLines = 4;
	else
		countLines = 5;

	output += MakeBegin(countLines);
	output += MakeSaveItem(string("flag_OpenLastFileWithOpenProgramm"), std::to_string(flag_OpenLastFileWithOpenProgramm));
	output += MakeSaveItem(string("flag_SaveAfterCompile"), std::to_string(flag_SaveAfterCompile));
	output += MakeSaveItem(string("flag_CompileAfterOpen"), std::to_string(flag_CompileAfterOpen));
	output += MakeSaveItem(string("setedAutoTiming"), AutoSaveTiming_To_string(setedAutoTiming));

	if (Path_LoadedFile.empty() == false)
		output += MakeSaveItem(string("LastLoadedPathFile"), Path_LoadedFile);


	return output;
}
void ProjectManager::Load(const std::string& Data) {
	PrintDebugInfoAboutData(Data);


	std::string path_temp;

	std::vector<std::string> Lines = split(Data, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		std::vector<std::string> info = SplitLine(Lines[i]);

		std::string name_arg = info[0];
		std::string value_arg = info[1];

		if (name_arg == "flag_OpenLastFileWithOpenProgramm")
			flag_OpenLastFileWithOpenProgramm = stoi(value_arg);
		else if (name_arg == "flag_SaveAfterCompile")
			flag_SaveAfterCompile = stoi(value_arg);
		else if (name_arg == "flag_CompileAfterOpen")
			flag_CompileAfterOpen = stoi(value_arg);
		else if (name_arg == "setedAutoTiming")
			setedAutoTiming = string_To_AutoSaveTiming(value_arg);
		else if (name_arg == "LastLoadedPathFile")
			path_temp = (value_arg);
		else
			std::cout << "Unknown name argument for widget: " << name_arg << std::endl;
	}

	if (path_temp.empty() == false && flag_OpenLastFileWithOpenProgramm == true) {

		if(isFileExist(path_temp))
			OpenFileWithPath(path_temp);
	}

}