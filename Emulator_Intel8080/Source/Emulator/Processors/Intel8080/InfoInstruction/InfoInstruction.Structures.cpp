#include "InfoInstruction.Structures.h"

CommandArguments ENUM_Arguments_to_CommandArguments(const ENUM_Arguments& object) {
	switch (object)
	{
	case ENUM_Arguments::Register8:
		return CommandArguments{ u8"Рег.8",{"A","B","C","D","E","H","L","M"} };
		break;
	case ENUM_Arguments::Register16_WithSP:
		return CommandArguments{ u8"Рег.16",{"B","D","H","SP"} };
		break;
	case ENUM_Arguments::Register16_WithSP_low:
		return CommandArguments{ u8"Рег.16.Млад",{"C","E","L",u8"SP.Млад"} };
		break;
	case ENUM_Arguments::Register16_WithSP_high:
		return CommandArguments{ u8"Рег.16.Стар",{"B","D","H",u8"SP.Стар"} };
		break;
	case ENUM_Arguments::Register16_WithPSW:
		return CommandArguments{ u8"Рег.16",{"B","D","H","PSW"} };
		break;
	case ENUM_Arguments::Register16_WithPSW_low:
		return CommandArguments{ u8"Рег.16.Млад",{"C","E","L","A"} };
		break;
	case ENUM_Arguments::Register16_WithPSW_high:
		return CommandArguments{ u8"Рег.16.Стар",{"B","D","H","PSW"} };
		break;
	case ENUM_Arguments::Register16_OnlyBD:
		return CommandArguments{ u8"Рег.16",{"B","D"} };
		break;
	case ENUM_Arguments::Value8:
		return CommandArguments{ u8"Число.8",{"0-255","0x00-0xff"} };
		break;
	case ENUM_Arguments::Value16:
		return CommandArguments{ u8"Число.16",{"0-65535","0x0000-0xffff"} };
		break;
	case ENUM_Arguments::Value16_low :
		return CommandArguments{ u8"Число.16.Млад",{} };
		break;
	case ENUM_Arguments::Value16_high:
		return CommandArguments{ u8"Число.16.Стар",{} };
		break;
	case ENUM_Arguments::ValueSpecial:
		return CommandArguments{ u8"Число.Спец",{"0-8","0x00-0x08"} };
		break;
	default:
		break;
	}

}

std::string ENUM_Bytes_to_str(const ENUM_Bytes& object) {
	switch (object) {
	case ENUM_Bytes::Opcode:
		return u8"Опкод";
		break;
	case ENUM_Bytes::Value:
		return u8"Число";
		break;
	case ENUM_Bytes::Value_low:
		return u8"Число.Млад.";
		break;
	case ENUM_Bytes::Value_high:
		return u8"Число.Стар.";
		break;
	case ENUM_Bytes::Adress_low:
		return u8"Адрес.Млад.";
		break;
	case ENUM_Bytes::Adress_high:
		return u8"Число.Стар.";
		break;
	default:
		break;
	}
	return "";
}

std::string ENUM_FlagsState_to_str(const ENUM_FlagsState& object) {
	switch (object) {
	case ENUM_FlagsState::Unaffected:
		return u8"Не изменяется";
		break;
	case ENUM_FlagsState::Affected:
		return u8"Изменяется";
		break;
	case ENUM_FlagsState::Reset:
		return u8"Устанавливается 0";
		break;
	case ENUM_FlagsState::Set:
		return u8"Устанавливается 1";
		break;
	default:
		break;
	}

	return "";
}

std::string Get_info_ticks_mean(std::vector<int> ticks, ENUM_TicksMean mean) {
	if (mean == ENUM_TicksMean::Condition)
		return std::to_string(ticks[0]) + u8" - Выполняется условие.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
	else if (mean == ENUM_TicksMean::M_Used)
		return std::to_string(ticks[0]) + u8" - Используется регистр M.\n" + std::to_string(ticks[1]) + u8" - Иначе.";
	else if (mean == ENUM_TicksMean::Always)
		return std::to_string(ticks[0]) + u8" - Всегда.";
}

std::string ENUM_Branching_to_str(const ENUM_Branching& object) {
	switch (object){
	case ENUM_Branching::IF:
		return u8"Если условие выполняется:";
		break;
	case ENUM_Branching::ELSE:
		return u8"Иначе:";
		break;
	default:
		break;
	}
}