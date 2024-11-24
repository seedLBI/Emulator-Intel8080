
#include "I8080.Port.AsyncKeyboard.h"

I8080_AsyncKeyboard::I8080_AsyncKeyboard() : I8080_Port(0x10) {
#ifdef WITH_DEBUG_OUTPUT
	std::cout << "init port Async keyboard: 0x10" << std::endl;
#endif
}

void I8080_AsyncKeyboard::SetInput(uint8_t value) {
	switch (count_input)
	{
	case 0:
		currentKey = value;
		break;
	default:
		break;
	}
	count_input++;

	if (count_input > 1) {
		count_input = 0;
	}
}

uint8_t I8080_AsyncKeyboard::GetOutput() {
	if (count_input == 1) {
		if (currentKey >= 0 && currentKey <= 57) {
			count_input = 0;
			ImGuiKey ArrayKeys[58] = { ImGuiKey_0,ImGuiKey_1,ImGuiKey_2,ImGuiKey_3,ImGuiKey_4,ImGuiKey_5,
					ImGuiKey_6,ImGuiKey_7,ImGuiKey_8,ImGuiKey_9,ImGuiKey_Escape,ImGuiKey_Minus,
					ImGuiKey_Equal,ImGuiKey_Backspace,ImGuiKey_Tab,ImGuiKey_Q,ImGuiKey_W,
					ImGuiKey_E,ImGuiKey_R,ImGuiKey_T, ImGuiKey_Y, ImGuiKey_U, ImGuiKey_I,
					ImGuiKey_O, ImGuiKey_P, ImGuiKey_LeftBracket, ImGuiKey_RightBracket, ImGuiKey_Backslash,
					ImGuiKey_CapsLock, ImGuiKey_A, ImGuiKey_S, ImGuiKey_D, ImGuiKey_F,
					ImGuiKey_G, ImGuiKey_H, ImGuiKey_J, ImGuiKey_K, ImGuiKey_L, ImGuiKey_Semicolon,
					ImGuiKey_Apostrophe, ImGuiKey_Enter, ImGuiKey_LeftShift, ImGuiKey_Z, ImGuiKey_X,
					ImGuiKey_C, ImGuiKey_V, ImGuiKey_B, ImGuiKey_N, ImGuiKey_M, ImGuiKey_Comma, ImGuiKey_Period,
					ImGuiKey_Slash, ImGuiKey_RightShift, ImGuiKey_LeftCtrl, ImGuiKey_LeftAlt, ImGuiKey_Space,
					ImGuiKey_RightAlt, ImGuiKey_RightCtrl };
			if (ImGui::IsKeyDown(ArrayKeys[currentKey]))
				return 1;
		}
	}
	return 0;
}
uint8_t I8080_AsyncKeyboard::GetPort() {
	return I8080_Port::GetPort();
}

void I8080_AsyncKeyboard::Reset() {
	currentKey = -1;
	count_input = 0;
}


std::shared_ptr<Momento> I8080_AsyncKeyboard::SaveState() {
	return std::shared_ptr<Momento>(new AsyncKeyboard_Momento(count_input,currentKey) );
}
void I8080_AsyncKeyboard::RestoreState(const std::shared_ptr<Momento>& momento) {
	auto data = dynamic_cast<AsyncKeyboard_Momento*>(momento.get());
	count_input = data->Get_count_input();
	currentKey = data->Get_currentKey();
}
