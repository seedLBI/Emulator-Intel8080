#include "EmulationThread.h"



std::string toString(SpeedMode mode) {
	switch (mode) {
	case SpeedMode::Infinity:
		return "Infinity";
	case SpeedMode::Intel8080:
		return "Intel8080";
	case SpeedMode::Intel8085:
		return "Intel8085";
	case SpeedMode::Custom:
		return "Custom";
	default:
		return "Unknown";
	}
}

void EmulationThread::SetControlMode(const ControlMode& mode) {

	if (mode == Control)
		return;

	while (isThreadWorking() == true) {
		processor->ActiveFlagStop();
	}

	Control = mode;
}

void EmulationThread::SetSpeedMode(const SpeedMode& mode) {

#ifdef WITH_DEBUG_OUTPUT
	cout << "SetSpeedMode: " << (int)mode << std::endl;
#endif



	if (mode == Speed && UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerSecond == targetTicksPerSecond)
		return;

	ControlMode lastControlMode = Control;


	while (isThreadWorking() == true) {
		processor->ActiveFlagStop();
	}

	Control = ControlMode::Stop;



	Speed = mode;

	if (Speed == SpeedMode::Intel8080){
		targetTicksPerSecond = 3'000'000;
		targetTicksPerFrame = targetTicksPerSecond / 1'000;
	}
	else if (Speed == SpeedMode::Intel8085) {
		targetTicksPerSecond = 6'000'000;
		targetTicksPerFrame = targetTicksPerSecond / 1'000;
	}
	else if (Speed == SpeedMode::Custom) {
		targetTicksPerSecond = UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerSecond;
		targetTicksPerFrame = UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerFrame;
	}


	if (flag_ReturnStateAfterChangeSpeed) {

		if (lastControlMode == ControlMode::Continous)
			processor->ResetFlagStop();

		Control = lastControlMode;
	}
}


void EmulationThread::WaitThread() {
	while (isThreadWorking()) {}
}

bool EmulationThread::isThreadWorking() {
	return flag_ThreadWorking;
}

EmulationThread::EmulationThread(I8080* processor) : ISettingObject(u8"Эмуляция",u8"Общие") {
#ifdef WITH_DEBUG_OUTPUT
	cout << "Creating second thread for processor\n";
#endif

	this->processor = processor;
	threadObject = new thread(&EmulationThread::ThreadLoop, this);
}

EmulationThread::~EmulationThread() {

}

SpeedMode EmulationThread::GetSpeedMode() {
	return Speed;
}
ControlMode EmulationThread::GetControlMode() {
	return Control;
}

void EmulationThread::ThreadLoop() {


	while (true) {

		if (Control == ControlMode::Continous) {
			flag_ThreadWorking = true;


			if (Speed == SpeedMode::Infinity){

				while (1) {
					processor->NextStep();

					if (processor->PC_on_BreakPoint() || *processor->IsStop()) {
						Control = ControlMode::Stop;
						break;
					}
				}

			}
			if (Speed != SpeedMode::Infinity){
				auto		startTime		  = std::chrono::high_resolution_clock::now();
				uint64_t	startTicks		  = processor->GetCountTicks();
				long double TimeTickPerSecond = 1.0 / (long double)targetTicksPerSecond;

				while (1) {
					uint64_t						   CurrentTicks   = processor->GetCountTicks() - startTicks;
					std::chrono::duration<long double> CurrentTime    = std::chrono::high_resolution_clock::now() - startTime;
					uint64_t						   CountTicksNeed = CurrentTime.count() / TimeTickPerSecond;


					if (CurrentTicks <= CountTicksNeed)
						processor->NextStep();

					if (processor->PC_on_BreakPoint() || *processor->IsStop()) {
						Control = ControlMode::Stop;
						break;
					}

				}
			}
			
			flag_ThreadWorking = false;
		}


		this_thread::sleep_for(chrono::milliseconds(100));
	}
}


void EmulationThread::LoadNextSpeed() {
	if (Speed == SpeedMode::Infinity)
		SetSpeedMode(SpeedMode::Intel8080);
	else if (Speed == SpeedMode::Intel8080)
		SetSpeedMode(SpeedMode::Intel8085);
	else if (Speed == SpeedMode::Intel8085) {
		if (UserSpeeds.empty())
			SetSpeedMode(SpeedMode::Infinity);
		else {
			IndexChoosedCustomSpeedMode = 0;
			SetSpeedMode(SpeedMode::Custom);
		}
	}
	else if (Speed == SpeedMode::Custom) {
		if (IndexChoosedCustomSpeedMode + 1 <= UserSpeeds.size() - 1){
			IndexChoosedCustomSpeedMode++;
			SetSpeedMode(SpeedMode::Custom);
		}
		else 
			SetSpeedMode(SpeedMode::Infinity);
	}
}

void EmulationThread::LoadPreviousSpeed() {
	if (Speed == SpeedMode::Intel8085)
		SetSpeedMode(SpeedMode::Intel8080);
	else if (Speed == SpeedMode::Intel8080)
		SetSpeedMode(SpeedMode::Infinity);
	else if (Speed == SpeedMode::Infinity) {
		if (UserSpeeds.empty())
			SetSpeedMode(SpeedMode::Intel8085);
		else {
			IndexChoosedCustomSpeedMode = UserSpeeds.size() - 1;
			SetSpeedMode(SpeedMode::Custom);
		}
	}
	else if (Speed == SpeedMode::Custom){
		if (IndexChoosedCustomSpeedMode - 1 >= 0) {
			IndexChoosedCustomSpeedMode--;
			SetSpeedMode(SpeedMode::Custom);
		}
		else
			SetSpeedMode(SpeedMode::Intel8085);
	}
}


int EmulationThread::InputTextCallback(ImGuiInputTextCallbackData* data) {
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter) {
		if (data->EventChar < '0' || data->EventChar > '9') {
			return 1;
		}
	}

	if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
		if (data->BufTextLen > 0) {
			uint64_t value = std::stoull(data->Buf);

			if (value > 100'000'000'000) {
				if (data->BufTextLen > 0) {
					data->Buf[data->BufTextLen - 1] = '\0';
					data->BufDirty = true;
					data->BufTextLen--;
				}
			}

			if (data->BufTextLen > 1 && data->Buf[0] == '0') {
				for (int i = 0; i < data->BufTextLen; ++i) {
					data->Buf[i] = data->Buf[i + 1];
				}
				data->Buf[data->BufTextLen - 1] = '\0';
				data->BufTextLen--;
				data->BufDirty = true;
			}

		}
	}

	return 0;  // Возвращаем 0, если все ок
}


void EmulationThread::DrawMainMenu() {
	if (Speed == SpeedMode::Infinity)
		ImGui::Text(("  " + std::string(ICON_FA_INFINITY) + u8" Гц").c_str());
	else
		ImGui::Text(("  " + TicksToString(targetTicksPerSecond)).c_str());

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(u8"Установленное ограничение на кол-во тактов, которое может выполнить процессор за секунду времени.\nЭто ограничение можно убрать или изменить в настройках.");
}

void EmulationThread::DrawSetting() {
	ISettingObject::DrawBegin();




	if (ImGui::RadioButton(u8"Применить предыдущее состояние выполнения процессора после изменения скорости", flag_ReturnStateAfterChangeSpeed))
		flag_ReturnStateAfterChangeSpeed = !flag_ReturnStateAfterChangeSpeed;

	string Selected = "";


	const std::string str_Infinity  = u8"Неограниченная";
	const std::string str_Intel8080 = u8"(3 Мгц) Intel8080";
	const std::string str_Intel8085 = u8"(6 Мгц) Intel8085";


	if (Speed      == SpeedMode::Infinity)
		Selected = str_Infinity;
	else if (Speed == SpeedMode::Intel8080)
		Selected = str_Intel8080;
	else if (Speed == SpeedMode::Intel8085)
		Selected = str_Intel8085;
	else if (Speed == SpeedMode::Custom)
		Selected = "(" + TicksToString(UserSpeeds[IndexChoosedCustomSpeedMode].targetTicksPerSecond) + ") " + UserSpeeds[IndexChoosedCustomSpeedMode].name;


	if (ImGui::BeginCombo(u8"Скорость", Selected.c_str(), ImGuiComboFlags_WidthFitPreview)) {




		if (ImGui::Selectable(str_Infinity.c_str(), Selected == str_Infinity))
			SetSpeedMode(SpeedMode::Infinity);
		if (Selected == str_Infinity)
			ImGui::SetItemDefaultFocus();


		if (ImGui::Selectable(str_Intel8080.c_str(), Selected == str_Intel8080))
			SetSpeedMode(SpeedMode::Intel8080);
		if (Selected == str_Intel8080)
			ImGui::SetItemDefaultFocus();


		if (ImGui::Selectable(str_Intel8085.c_str(), Selected == str_Intel8085))
			SetSpeedMode(SpeedMode::Intel8085);
		if (Selected == str_Intel8085)
			ImGui::SetItemDefaultFocus();
		
		ImGuiWindow* imgui_window = ImGui::GetCurrentWindow();
		ImDrawList* draw_list = ImGui::GetForegroundDrawList();

		for (int i = 0; i < UserSpeeds.size(); i++){
			std::string Title = "(" + TicksToString(UserSpeeds[i].targetTicksPerSecond) + ") " + UserSpeeds[i].name;

			if (ButtonDelete(imgui_window, draw_list, ("userSpeeds" + std::to_string(i)).c_str(), ImColor(ImVec4(1.f, 1.f, 1.f, 1.f)))) {
				UserSpeeds.erase(UserSpeeds.begin() + i);
				i--;
				continue;
			}

			//ImGui::SameLine();
			if (ImGui::Selectable(Title.c_str(), i == IndexChoosedCustomSpeedMode && Speed == SpeedMode::Custom)) {
				IndexChoosedCustomSpeedMode = i;
				SetSpeedMode(SpeedMode::Custom);
			}
		
			if (i == IndexChoosedCustomSpeedMode && Speed == SpeedMode::Custom)
				ImGui::SetItemDefaultFocus();
		}


		if (ButtonCenteredOnLine(u8"Добавить ограничение", 0.5f))
			PopupCreation_opened = true;

		ImGui::EndCombo();
	}


	DrawPopup();
}

void EmulationThread::DrawPopup() {
	if (PopupCreation_opened == false)
		return;

	ImGui::OpenPopup(u8"Создание пользовательского ограничения");

	const ImGuiWindowFlags flagsWindow = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImVec2 size = ImGui::GetMainViewport()->WorkSize;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(u8"Создание пользовательского ограничения              ").x, ImGui::GetFontSize() * 12.5f));


	static char buf_name[120];
	static char buf_value[120];
	static bool FirstLoad = false;
	if (FirstLoad == false){
		FirstLoad = true;
		for (int i = 0; i < 120; i++) {
			buf_name[i] = 0;
			buf_value[i] = 0;
		}
	}

	if (ImGui::BeginPopupModal(u8"Создание пользовательского ограничения", &PopupCreation_opened, flagsWindow)){
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetFontSize() * 0.5f);
		center.x -= ImGui::GetCurrentWindow()->Size.x / 2;
		center.y -= ImGui::GetCurrentWindow()->Size.y / 2;
		ImGui::GetCurrentWindow()->Pos = center;

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 1.0));
		TextCenteredOnLine(u8"(необязательно)", 0, 0);
		ImGui::PopStyleColor();

		TextCenteredOnLine(u8"Название ограничения", 0, 0);
		



		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		float input_width = ImGui::CalcItemWidth();
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
		ImGui::InputText("1102", buf_name, 120, ImGuiInputTextFlags_NoLabel);

		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));


		TextCenteredOnLine(u8"Верхний порог кол-ва тактов", 0, 0);
		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));

		input_width = ImGui::CalcItemWidth();
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x - input_width) / 2.f);
		ImGui::SetNextItemWidth(input_width - ImGui::CalcTextSize(u8"колвоГЦ").x);
		ImGui::InputText("1104", buf_value, 120, ImGuiInputTextFlags_NoLabel| ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackEdit, InputTextCallback);

		ImGui::SameLine();
		if (!std::string(buf_value).empty())
			ImGui::Text(std::string(" " + TicksToString(std::stoull(std::string(buf_value)))).c_str());
		else
			ImGui::Text(std::string(" " + TicksToString(0)).c_str());

		//InputTextCallback
		ImGui::Dummy(ImVec2(0.f, ImGui::GetFontSize() * 0.25f));



		bool pressed = ButtonCenteredOnLine(u8"Принять", 0.5f);

		if (ImGui::IsKeyPressed(ImGuiKey_Enter))
			pressed = true;

		if (pressed){

			if (!std::string(buf_value).empty()){
				PopupCreation_opened = false;

				CustomSpeed tempSpeed;
				tempSpeed.name = buf_name;

				tempSpeed.targetTicksPerSecond = std::stoull(std::string(buf_value));
				tempSpeed.targetTicksPerFrame = tempSpeed.targetTicksPerSecond / 1'000;

				UserSpeeds.emplace_back(tempSpeed);

				IndexChoosedCustomSpeedMode = UserSpeeds.size() - 1;
				SetSpeedMode(SpeedMode::Custom);
			}
			else
				pressed = false;
		}

		ImGui::EndPopup();
	}

	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

std::string EmulationThread::TicksToString(const uint64_t& ticks) {

	std::string Output = "";

	uint64_t Kilo = ticks / 1'000;
	uint64_t Mega = ticks / 1'000'000;
	uint64_t Giga = ticks / 1'000'000'000;
	uint64_t Tera = ticks / 1'000'000'000'000;

	if (Tera != 0){
		Output += to_string(Tera);

		uint64_t ost = ticks - Tera * 1'000'000'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0,2);

		Output += u8" ТГц";
	}
	else if (Giga != 0){
		Output += to_string(Giga);

		uint64_t ost = ticks - Giga* 1'000'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" ГГц";
	}
	else if (Mega != 0) {
		Output += to_string(Mega);

		uint64_t ost = ticks - Mega* 1'000'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" МГц";
	}
	else if (Kilo != 0) {
		Output += to_string(Kilo);

		uint64_t ost = ticks - Kilo* 1'000;

		if (ost > 0)
			Output += "." + to_string(ost).substr(0, 2);

		Output += u8" кГц";
	}
	else {
		Output += to_string(ticks);
		Output += u8" Гц";
	}

	return Output;
}

std::string EmulationThread::SaveSetting() {
	std::string result = save_MakeBegin(2 + UserSpeeds.size()*2);


	for (int i = 0; i < UserSpeeds.size(); i++) {
		result += save_MakeItem("NameCustomSpeed", UserSpeeds[i].name);
		result += save_MakeItem("ValueCustomSpeed", std::to_string(UserSpeeds[i].targetTicksPerSecond));
	}
	result += save_MakeItem("IndexChoosedCustomSpeedMode", std::to_string(IndexChoosedCustomSpeedMode));
	result += save_MakeItem("flag_ReturnStateAfterChangeSpeed", std::to_string(flag_ReturnStateAfterChangeSpeed));
	result += save_MakeItem("SpeedMode", toString(Speed));


	return result;
}

void EmulationThread::LoadSetting(const std::string& Data) {
	auto info = load_TokenizeData(Data);

	std::string path_temp;

	CustomSpeed tempSpeed;

	for (SettingLoadData data : info) {
		if (data.NameVar == "SpeedMode") {
			if (data.ValueVar == "Infinity")
				SetSpeedMode(SpeedMode::Infinity);
			else if (data.ValueVar == "Intel8080")
				SetSpeedMode(SpeedMode::Intel8080);
			else if (data.ValueVar == "Intel8085")
				SetSpeedMode(SpeedMode::Intel8085);
			else if (data.ValueVar == "Custom")
				SetSpeedMode(SpeedMode::Custom);
			else
				std::cout << "Unknown speedmode argument: " << data.ValueVar << std::endl;
		}
		else if (data.NameVar == "NameCustomSpeed") {
			tempSpeed.name = data.ValueVar;
		}
		else if (data.NameVar == "ValueCustomSpeed") {
			tempSpeed.targetTicksPerSecond = std::stoull(data.ValueVar);
			tempSpeed.targetTicksPerFrame = tempSpeed.targetTicksPerSecond / 1'000;
			UserSpeeds.emplace_back(tempSpeed);
		}
		else if (data.NameVar == "IndexChoosedCustomSpeedMode")
			IndexChoosedCustomSpeedMode = stoi(data.ValueVar);
		else if (data.NameVar == "flag_ReturnStateAfterChangeSpeed")
			flag_ReturnStateAfterChangeSpeed = stoi(data.ValueVar);
		else
			std::cout << "EmulationThread::LoadSetting -> Unknown name argument: " << data.NameVar << std::endl;
	}

}