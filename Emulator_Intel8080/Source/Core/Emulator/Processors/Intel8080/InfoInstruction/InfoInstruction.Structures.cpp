#include "InfoInstruction.Structures.h"

CommandArguments ENUM_Arguments_to_CommandArguments(const InstructionArguments& object) {
	switch (object)
	{
	case InstructionArguments::Register8:
		return CommandArguments{ u8"���.8",{"B","C","D","E","H","L","M","A"} };
		break;
	case InstructionArguments::Register16_WithSP:
		return CommandArguments{ u8"���.16",{"B","D","H","SP"} };
		break;
	case InstructionArguments::Register16_WithSP_low:
		return CommandArguments{ u8"���.16.����",{"C","E","L",u8"SP.����"} };
		break;
	case InstructionArguments::Register16_WithSP_high:
		return CommandArguments{ u8"���.16.����",{"B","D","H",u8"SP.����"} };
		break;
	case InstructionArguments::Register16_WithPSW:
		return CommandArguments{ u8"���.16",{"B","D","H","PSW"} };
		break;
	case InstructionArguments::Register16_WithPSW_low:
		return CommandArguments{ u8"���.16.����",{"C","E","L","A"} };
		break;
	case InstructionArguments::Register16_WithPSW_high:
		return CommandArguments{ u8"���.16.����",{"B","D","H","PSW"} };
		break;
	case InstructionArguments::Register16_OnlyBD:
		return CommandArguments{ u8"���.16",{"B","D"} };
		break;
	case InstructionArguments::Value8:
		return CommandArguments{ u8"�����.8",{"0-255","0x00-0xff"} };
		break;
	case InstructionArguments::Value16:
		return CommandArguments{ u8"�����.16",{"0-65535","0x0000-0xffff"} };
		break;
	case InstructionArguments::Value16_low :
		return CommandArguments{ u8"�����.16.����",{} };
		break;
	case InstructionArguments::Value16_high:
		return CommandArguments{ u8"�����.16.����",{} };
		break;
	case InstructionArguments::ValueSpecial:
		return CommandArguments{ u8"�����.����",{"0-8","0x00-0x08"} };
		break;
	default:
		return CommandArguments{ u8"����������",{} };
		break;
	}

}

std::string ENUM_Bytes_to_str(const InstructionBytes& object) {
	switch (object) {
	case InstructionBytes::Opcode:
		return u8"�����";
		break;
	case InstructionBytes::Value:
		return u8"�����";
		break;
	case InstructionBytes::Value_low:
		return u8"�����.����.";
		break;
	case InstructionBytes::Value_high:
		return u8"�����.����.";
		break;
	case InstructionBytes::Adress_low:
		return u8"�����.����.";
		break;
	case InstructionBytes::Adress_high:
		return u8"�����.����.";
		break;
	default:
		break;
	}
	return "";
}

std::string ENUM_FlagsState_to_str(const InstructionFlagsState& object) {
	switch (object) {
	case InstructionFlagsState::Unaffected:
		return u8"�� ����������";
		break;
	case InstructionFlagsState::Affected:
		return u8"����������";
		break;
	case InstructionFlagsState::Reset:
		return u8"��������������� 0";
		break;
	case InstructionFlagsState::Set:
		return u8"��������������� 1";
		break;
	default:
		break;
	}

	return "";
}

std::string Get_info_ticks_mean(std::vector<int> ticks, InstructionTicksMean mean) {
	if (mean == InstructionTicksMean::Condition)
		return std::to_string(ticks[0]) + u8" - ����������� �������.\n" + std::to_string(ticks[1]) + u8" - �����.";
	else if (mean == InstructionTicksMean::M_Used)
		return std::to_string(ticks[0]) + u8" - ������������ ������� M.\n" + std::to_string(ticks[1]) + u8" - �����.";
	else if (mean == InstructionTicksMean::Always)
		return std::to_string(ticks[0]) + u8" - ������.";

	return std::to_string(ticks[0]) + u8" - ����������.";
}

std::string ENUM_Branching_to_str(const InstructionBranching& object) {
	switch (object){
	case InstructionBranching::IF:
		return u8"���� ������� �����������:";
		break;
	case InstructionBranching::ELSE:
		return u8"�����:";
		break;
	default:
		return u8"����������";
		break;
	}
}