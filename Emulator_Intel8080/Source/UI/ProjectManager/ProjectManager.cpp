#include "UI/ProjectManager/ProjectManager.h"


ProjectManager::ProjectManager(
	GLFWwindow* window,
	I8080* processor,
	NotificationManager* notificationManager,
	LastPathManager* lastPathManager,
	EmulationThread* emulationThread,
	CompilerStable* Compiler,
	Caretaker_Momento* processor_CaretakerMomento) : ISettingObject(u8"Проект",u8"Общие") {

	this->window = window;
	this->processor = processor;
	this->notificationManager = notificationManager;
	this->lastPathManager = lastPathManager;
	this->emulationThread = emulationThread;
	this->Compiler = Compiler;
	this->processor_CaretakerMomento = processor_CaretakerMomento;
}

ProjectManager::~ProjectManager() {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "ProjectManager::~ProjectManager()\n";
#endif // !WITH_DEBUG_OUTPUT
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

	string text = u8"Создан новый проект.";

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

			auto data = readFileToByteArray(path);

			processor->LoadMemoryFromCOM(data);
		}
		else if (ExtensionFile == "bin") {

			widget_CodeEditor->GetPtrTextEditor()->DeleteAllErrorMarkers();
			widget_CodeEditor->GetPtrTextEditor()->DeleteAllBreakpoints();
			widget_CodeEditor->GetPtrTextEditor()->SetTextLines({});
			widget_CodeEditor->GetPtrTextEditor()->SetReadOnly(true);

			auto data = readFileToByteArray(path);

			processor->LoadMemoryFromBinary(data);
		}

		
		if (wasFirstUpdate) {

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

	if (processor->GetModeProject() != ModeProject::USER){

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Нельзя сохранять бинарные файлы их можно лишь открыть.";

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

	if (processor->GetModeProject() != ModeProject::USER) {

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Нельзя сохранять бинарные файлы их можно лишь открыть.";

		notificationManager->AddNottification(Notification(color_RED, 2.f, std::vector<N_Element*>{
			new N_Message(color_WHITE, text)
		},
			nullptr));

		return;
	}


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
void ProjectManager::SaveFileIntoBinary() {

	TryTranslateCode();
	if (translatorOutput.Error != TypeTranslatorError::NOTHING)
		return;


	std::string path = SaveFileDialogROM();
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
		std::cerr << "Error opening file for writing: " << path << std::endl;
		return;
	}

	file.write(reinterpret_cast<const char*>(data.data()), data.size());

	file.close();



}


void ProjectManager::Compile() {

	if (processor->GetModeProject() != ModeProject::USER) {

		static const ImVec4 color_RED{ 0.45f,0.2f,0.2f,1.0f };
		static const ImVec4 color_WHITE{ 1.f,1.f,1.f,1.f };

		string text = u8"Нельзя компилировать бинарные файлы, ведь они уже откомпилированны...";

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
		processor->RemoveAllBreakPoints();
		processor->LoadMemory(translatorOutput.Opcodes);
		widget_RegisterFlagsInfo->InitLastState();

		auto breaks = widget_CodeEditor->GetPtrTextEditor()->GetBreakpoints();

		for (int i = 0; i < breaks.size(); i++) {

			if (breaks[i]-1 > translatorOutput.Line_and_Adress.size())
				continue;

			int adressBreak = translatorOutput.Line_and_Adress[breaks[i] - 1];
			if (adressBreak != -1)
				processor->SetBreakPointPosition(adressBreak,true);
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



std::string ProjectManager::SaveSetting() {
	std::string output = "";

	int countLines = 0;

	if (Path_LoadedFile.empty())
		countLines = 4;
	else
		countLines = 5;

	output += save_MakeBegin(countLines);
	output += save_MakeItem(string("flag_OpenLastFileWithOpenProgramm"), std::to_string(flag_OpenLastFileWithOpenProgramm));
	output += save_MakeItem(string("flag_SaveAfterCompile"), std::to_string(flag_SaveAfterCompile));
	output += save_MakeItem(string("flag_CompileAfterOpen"), std::to_string(flag_CompileAfterOpen));
	output += save_MakeItem(string("setedAutoTiming"), AutoSaveTiming_To_string(setedAutoTiming));

	if (Path_LoadedFile.empty() == false)
		output += save_MakeItem(string("LastLoadedPathFile"), Path_LoadedFile);


	return output;
}
void ProjectManager::LoadSetting(const std::string& Data) {
	auto info = load_TokenizeData(Data);

	std::string path_temp;

	for (SettingLoadData data : info) {
		if (data.NameVar == "flag_OpenLastFileWithOpenProgramm")
			flag_OpenLastFileWithOpenProgramm = stoi(data.ValueVar);
		else if (data.NameVar == "flag_SaveAfterCompile")
			flag_SaveAfterCompile = stoi(data.ValueVar);
		else if (data.NameVar == "flag_CompileAfterOpen")
			flag_CompileAfterOpen = stoi(data.ValueVar);
		else if (data.NameVar == "setedAutoTiming")
			setedAutoTiming = string_To_AutoSaveTiming(data.ValueVar);
		else if (data.NameVar == "LastLoadedPathFile")
			path_temp = data.ValueVar;
		else
			std::cout << "ProjectManager::LoadSetting -> Unknown name argument: " << data.NameVar << std::endl;
	}

	if (path_temp.empty() == false && flag_OpenLastFileWithOpenProgramm == true) {

		if(isFileExist(path_temp))
			OpenFileWithPath(path_temp);
	}

}