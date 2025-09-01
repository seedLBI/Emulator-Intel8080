#include "InfoInstruction.Structures.h"

CommandArguments ENUM_Arguments_to_CommandArguments(const InstructionArguments& object) {
	switch (object)
	{
	case InstructionArguments::Register8:
		return CommandArguments{ u8"Рег.8",{"B","C","D","E","H","L","M","A"} };
		break;
	case InstructionArguments::Register16_WithSP:
		return CommandArguments{ u8"Рег.16",{"B","D","H","SP"} };
		break;
	case InstructionArguments::Register16_WithSP_low:
		return CommandArguments{ u8"Рег.16.Млад",{"C","E","L",u8"SP.Млад"} };
		break;
	case InstructionArguments::Register16_WithSP_high:
		return CommandArguments{ u8"Рег.16.Стар",{"B","D","H",u8"SP.Стар"} };
		break;
	case InstructionArguments::Register16_WithPSW:
		return CommandArguments{ u8"Рег.16",{"B","D","H","PSW"} };
		break;
	case InstructionArguments::Register16_WithPSW_low:
		return CommandArguments{ u8"Рег.16.Млад",{"C","E","L","A"} };
		break;
	case InstructionArguments::Register16_WithPSW_high:
		return CommandArguments{ u8"Рег.16.Стар",{"B","D","H","PSW"} };
		break;
	case InstructionArguments::Register16_OnlyBD:
		return CommandArguments{ u8"Рег.16",{"B","D"} };
		break;
	case InstructionArguments::Value8:
		return CommandArguments{ u8"Число.8",{"0-255","0x00-0xff"} };
		break;
	case InstructionArguments::Value16:
		return CommandArguments{ u8"Число.16",{"0-65535","0x0000-0xffff"} };
		break;
	case InstructionArguments::Value16_low :
		return CommandArguments{ u8"Число.16.Млад",{} };
		break;
	case InstructionArguments::Value16_high:
		return CommandArguments{ u8"Число.16.Стар",{} };
		break;
	case InstructionArguments::ValueSpecial:
		return CommandArguments{ u8"Число.Спец",{"0-8","0x00-0x08"} };
		break;
	default:
		return CommandArguments{ u8"Неизвестно",{} };
		break;
	}

}

std::string ENUM_Bytes_to_str(const InstructionBytes& object) {
	switch (object) {
	case InstructionBytes::Opcode:
		return u8"Опкод";
		break;
	case InstructionBytes::Value:
		return u8"Число";
		break;
	case InstructionBytes::Value_low:
		return u8"Число.Млад.";
		break;
	case InstructionBytes::Value_high:
		return u8"Число.Стар.";
		break;
	case InstructionBytes::Adress_low:
		return u8"Адрес.Млад.";
		break;
	case InstructionBytes::Adress_high:
		return u8"Число.Стар.";
		break;
	default:
		break;
	}
	return "";
}

std::string ENUM_FlagsState_to_str(const InstructionFlagsState& object) {
	switch (object) {
	case InstructionFlagsState::Unaffected:
		return u8"Не изменяется";
		break;
	case InstructionFlagsState::Affected:
		return u8"Изменяется";
		break;
	case InstructionFlagsState::Reset:
		return u8"Устанавливается 0";
		break;
	case InstructionFlagsState::Set:
		return u8"Устанавливается 1";
		break;
	default:
		break;
	}

	return "";
}

std::string Get_info_ticks_mean(std::vector<int> ticks, InstructionTicksMean mean) {
	if (mean == InstructionTicksMean::Condition)
		return std::to_string(ticks[0]) + u8" - Выполняется условие.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
	else if (mean == InstructionTicksMean::M_Used)
		return std::to_string(ticks[0]) + u8" - Используется регистр M.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
	else if (mean == InstructionTicksMean::Always)
		return std::to_string(ticks[0]) + u8" - Всегда.";

	return std::to_string(ticks[0]) + u8" - Неизвестно.";
}

std::string ENUM_Branching_to_str(const InstructionBranching& object) {
	switch (object){
	case InstructionBranching::IF:
		return u8"Если условие выполняется:";
		break;
	case InstructionBranching::ELSE:
		return u8"Иначе:";
		break;
	default:
		return u8"Неизвестно";
		break;
	}
}