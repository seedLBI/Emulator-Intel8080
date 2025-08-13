#include "InfoInstruction.Data.h"

const robin_hood::unordered_flat_map<std::string, InstructionInfo> map_InstructionInfo = {
	// HLT------------------------------------------
		{"hlt",{
		{},{},
		u8"��������� ������ ����������.",
		{
			{u8"����"}
		},
		{7},
		InstructionTicksMean::Always,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::CONTROL},
		{0x76}}
	},

	// NOP------------------------------------------
		{"nop",{
		{},
		{},
		u8"������ ������� ������� �������� ���� ����",
		{
			{"[PC]","=","[PC] + 1"}
		},
		{4},
		InstructionTicksMean::Always,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::CONTROL},
		{0x00,0x08,0x10,0x18,0x20,0x28,0x30,0x38}}
	},

	// IN------------------------------------------
		{"in",{
		{InstructionArguments::Value8},
		{InstructionBytes::Value},
		u8"������ �������� � ����������� �� �������� �����",
		{
			{"[A]",		"=", "Port[", InstructionArguments::Value8, "]"},
			{"[PC]",	"=", "[PC] + 2"}
		},
		{10},
		InstructionTicksMean::Always,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::INPUT_OUTPUT},
		{0xDB}}
	},

	// OUT------------------------------------------
		{"out",{
		{InstructionArguments::Value8},
		{InstructionBytes::Value},
		u8"�������� �������� �� ������������ �� ������� ����",
		{
			{"Port[", InstructionArguments::Value8,"]",	"=", "[A]"},
			{"[PC]",								"=", "[PC] + 2" }
		},
		{10},
		InstructionTicksMean::Always,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::INPUT_OUTPUT},
		{0xD3}}
	},

	// MOV------------------------------------------
		{"mov",{
		{InstructionArguments::Register8,InstructionArguments::Register8},
		{},
		u8"����������� �������� ����� ���������� ��� �������(�� ������ HL)",
		{
			{InstructionArguments::Register8,	"=", InstructionArguments::Register8},
			{"[PC]",					"=", "[PC] + 1"}
		},
		{7,5},
		InstructionTicksMean::M_Used,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::MOVE_LOAD_STORE},
		{0x40,0x40,0x75,0x77,0x77,0x7F}}
	},

	// MVI------------------------------------------
		{"mvi",{
		{InstructionArguments::Register8,InstructionArguments::Value8},
		{InstructionBytes::Value},
		u8"������ ��������� � ������� ��� ������",
		{
			{InstructionArguments::Register8,	"=",InstructionArguments::Value8},
			{"[PC]",					"=", "[PC] + 2"}
		},
		{10,7},
		InstructionTicksMean::M_Used,
		FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::MOVE_LOAD_STORE},
		{0x06,0x0E,0x16,0x1E,0x26,0x2E,0x36,0x3E}}
	},

	// CMP------------------------------------------
		{"cmp",{
		{InstructionArguments::Register8},
		{},
		u8"��������� �������� ����� ������������� � ���������� ��� �������(�� ������ HL)",
		{
			{"Temp",    "=", "([A] - ",InstructionArguments::Register8,")"},
			{"[Zero]",  "=", "[Temp == 0]"},
			{"[Carry]", "=", "[A] < ",InstructionArguments::Register8},
			{"[PC]",    "=", "[PC] + 1"}
		},
		{7,4},
		InstructionTicksMean::M_Used,
		FlagsList{
			InstructionFlagsState::Affected,
			InstructionFlagsState::Affected,
			InstructionFlagsState::Affected,
			InstructionFlagsState::Affected,
			InstructionFlagsState::Affected},
		{InstructionCategory::LOGICAL},
		{0xB8,0xB8,0xBF}}
	},

	// CPI------------------------------------------
	{ "cpi",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"��������� �������� ������������ � ����������",
	{
		{"Temp",   "=", "[A] - ",InstructionArguments::Value8},
		{"[Zero]", "=", "[Temp == 0]"},
		{"[Carry]","=", "[A] < ",InstructionArguments::Value8},
		{"[PC]",   "=", "[PC] + 1"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
	{InstructionCategory::LOGICAL},
	{0xFE}}
	},

	// ANA------------------------------------------
	{ "ana",{
	{InstructionArguments::Register8},
	{},
	u8"���������� � �������� ������������ � ��������� ��� �������(�� ������ HL)",
	{
		{"[A]",    "=", "[A] & ",InstructionArguments::Register8},
		{"[Zero]", "=", "([A] == 0)"},
		{"[Carry]","=", "0"},
		{"[PC]",   "=", "[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xA0,0xA0,0xA7}}
	},


	// ANI------------------------------------------
	{ "ani",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"���������� � ������������ � ����������",
	{
		{"[A]",    "=","[A] & ",InstructionArguments::Value8},
		{"[Zero]", "=","([A] == 0)"},
		{"[Carry]","=","0"},
		{"[PC]",   "=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
		FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xE6}}
	},

	// ORA------------------------------------------
	{ "ora",{
	{InstructionArguments::Register8},
	{},
	u8"���������� ��� �������� ������������ � ��������� ��� �������(�� ������ HL)",
	{
		{"[A]",    "=","[A] | ",InstructionArguments::Register8},
		{"[Zero]", "=","([A] == 0)"},
		{"[Carry]","=","0"},
		{"[PC]",   "=","[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
		FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xB0,0xB0,0xB7}}
	},

	// ORI------------------------------------------
	{ "ori",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"���������� ��� �������� ������������ � ����������",
	{
		{"[A]",				"=","[A] | ", InstructionArguments::Value8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xF6}}
	},

	// XRA------------------------------------------
	{ "xra",{
	{InstructionArguments::Register8},
	{},
	u8"���������� ����������� ��� �������� ������������ � ��������� ��� �������(�� ������ HL)",
	{
		{"[A]",				"=","[A] ^ ",InstructionArguments::Register8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xA8,0xA8,0xAF}}
	},

	// XRI------------------------------------------
	{ "xri",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"���������� ����������� ��� �������� ������������ � ����������",
	{
		{"[A]",				"=","[A] ^ ",InstructionArguments::Value8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Reset},
	{InstructionCategory::LOGICAL},
	{0xEE}}
	},

	// RLC------------------------------------------
	{ "rlc",{
	{},
	{},
	u8"��� ���� ������������ ���������� ����� �� ���� ���. �������� ���������� ���������� ���� ��������������� � ���� Carry � ��������������� � ������ ��� ������������\nRLC - Rotate Left Circular",
	{
		{"[Carry]",	"=","A[7]"},
		{"[A]",		"=","([A] << 1) | [Carry]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ROTATE},
	{0x07}}
	},

	// RAL------------------------------------------
	{ "ral",{
	{},
	{},
	u8"��� ���� ������������ ���������� ����� �� ���� ���. ��������� ����� Carry ��������������� � ������ ��� ������������. �������� ���������� ���� (�� ���������� ������������) ��������������� � ���� Carry\nRAL - Rotate Accumulator Left through Carry",
	{
		{"Temp",	"=","A[7]"},
		{"[A]",		"=","(A << 1) | [Carry]"},
		{"[Carry]",	"=","Temp"},
		{"[PC]",	"=","PC + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ROTATE},
	{0x17}}
	},

	// RRC------------------------------------------
	{ "rrc",{
	{},
	{},
	u8"��� ���� ������������ ���������� ������ �� ���� ���. �������� ������� ���� ������������ ��������������� � ���� Carry � ��������������� � ��������� ��� ������������\nRRC - Rotate Right Circular",
	{
		{"[Carry]",	"=","A[0]"},
		{"[A]",		"=","([A] >> 1) | ([Carry] << 7)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ROTATE},
	{0x0F}}
	},

	// RAR------------------------------------------
	{ "rar",{
	{},
	{},
	u8"��� ���� ������������ ���������� ������ �� ���� ���. ��������� ����� Carry ��������������� � ��������� ��� ������������. �������� ������� ���� (�� ���������� ������������) ��������������� � ���� Carry\nRAR - Rotate Accumulator Right through Carry",
	{
		{"Temp",	"=","A[0]"},
		{"[A]",		"=","([A] >> 1) | ([Carry] << 7)"},
		{"[Carry]",	"=","Temp"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ROTATE},
	{0x1F}}
	},

	// STC------------------------------------------
	{ "stc",{
	{},
	{},
	u8"������������� ���� Carry � ��������� True.",
	{
		{"[Carry]",	"=","True"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Set},
	{InstructionCategory::SPECIALS},
	{0x37}}
	},

	// CMA------------------------------------------
	{ "cma",{
	{},
	{},
	u8"����������� �������� �������� ������������.",
	{
		{"[A]",		"=", "![A]"},
		{"[PC]",	"=", "[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::SPECIALS},
	{0x2F}}
	},

	// CMC------------------------------------------
	{ "cmc",{
	{},
	{},
	u8"����������� ���� Carry.",
	{
		{"[Carry]",	"=", "![Carry]"},
		{"[PC]",	"=", "[PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected },
	{InstructionCategory::SPECIALS},
	{0x3F}}
	},

	// RET------------------------------------------
	{ "ret",{
	{},
	{},
	u8"������ �� ����� ���������� � �������� �����.",
	{
		{"[PC].low",	"=","M[SP]"},
		{"[PC].high",	"=","M[SP + 1]" },
		{"[SP]",		"=","[SP] + 2"},
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xC9,0xD9}}
	},

	// RZ------------------------------------------
	{ "rz",{
	{},
	{},
	u8"���� ���� Zero = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRZ - Return if Zero",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xC8}}
	},

	// RC------------------------------------------
	{ "rc",{
	{},
	{},
	u8"���� ���� Carry = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRC - Return if Carry",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xD8}}
	},

	// RPE------------------------------------------
	{ "rpe",{
	{},
	{},
	u8"���� ���� Parity = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRPE - Return if Paritu Even",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xE8}}
	},

	// RM------------------------------------------
	{ "rm",{
	{},
	{},
	u8"���� ���� Sign = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRM - Return if Minus.",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xF8}}
	},

	// RNZ------------------------------------------
	{ "rnz",{
	{},
	{},
	u8"���� ���� Zero = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRNZ - Return if Not Zero",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xC0}}
	},

	// RNC------------------------------------------
	{ "rnc",{
	{},
	{},
	u8"���� ���� Carry = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRNC - Return if Not Carry",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xD0}}
	},

	// RPO------------------------------------------
	{ "rpo",{
	{},
	{},
	u8"���� ���� Parity = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRPO - Return if Parity Odd",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xE0}}
	},
	// RP------------------------------------------
	{ "rp",{
	{},
	{},
	u8"���� ���� Sign = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������.\nRP - Return if Positive",
	{
		{InstructionBranching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RETURN},
		{0xF0}}
	},

	// JMP------------------------------------------
	{ "jmp",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"������ PC �� ������ �������� ���������",
	{
		{"[PC]", "=", InstructionArguments::Value16}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xC3,0xCB}}
	},

	// JZ------------------------------------------
	{ "jz",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Zero = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJZ - Jump if Zero",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xCA}}
	},

	// JC------------------------------------------
	{ "jc",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Carry = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJC - Jump if Carry",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xDA}}
	},

	// JPE------------------------------------------
	{ "jpe",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Parity = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJPE - Jump if Parity Even",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xEA}}
	},

	// JM------------------------------------------
	{ "jm",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Sign = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJM - Jump if Minus.",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xFA}}
	},


	{ "jnz",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Zero = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJNZ - Jump if Not Zero",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xC2}}
	},


	{ "jnc",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Carry = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJNC - Jump if Not Carry",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xD2}}
	},


	{ "jpo",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Parity = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJPO - Jump if Parity Odd",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xE2}}
	},


	{ "jp",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ����  Sign = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������.\nJP - Jump if Positive",
	{
		{InstructionBranching::IF},
			{"[PC]",	"=", InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
		{0xF2}}
	},


	{ "call",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	{
		{"[SP]",		"=","[SP] - 2"},
		{"M[SP]",		"=","([PC] + 3).low"},
		{"M[SP + 1]",	"=","([PC] + 3).high"},
		{"[PC]",		"=",InstructionArguments::Value16}
	},
	{17},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xCD,0xDD,0xED,0xFD}}
	},


	{ "cz",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Zero = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCZ - Call if Zero",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xCC}}
	},


	{ "cc",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Carry = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCC - Call if Carry",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xDC}}
	},


	{ "cpe",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Parity = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCPE - Call if Parity Even",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xEC}}
	},


	{ "cm",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Sign = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCM - Call if Minus",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xFC}}
	},


	{ "cnz",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Zero = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCNZ - Call if Not Zero",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xC4}}
	},


	{ "cnc",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Carry = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCNC - Call if Not Carry",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xD4}}
	},


	{ "cpo",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Parity = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCPO - Call if Parity Odd",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xE4}}
	},


	{ "cp",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"���� ���� Sign = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������.\nCP - Call if Positive",
	{
		{InstructionBranching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",InstructionArguments::Value16},
		{InstructionBranching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	InstructionTicksMean::Condition,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::CALL},
		{0xF4}}
	},


	{ "push",{
	{InstructionArguments::Register16_WithPSW},
	{},
	u8"���������� ������������� ����� �� ���� ��������� � �������� �����",
	{
		{"[SP]",			"=","[SP] - 2"},
		{"M[SP + 1]",		"=",InstructionArguments::Register16_WithPSW_high},
		{"M[SP]",			"=",InstructionArguments::Register16_WithPSW_low},
		{"[PC]",			"=","[PC] + 1"}
	},
	{11},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::STACK_OPS},
		{0xC5,0xD5,0xE5,0xF5}}
	},


	{ "pop",{
	{InstructionArguments::Register16_WithPSW},
	{},
	u8"���������� �� �������� ����� ������������� ����� � ���� ���������",
	{
		{InstructionArguments::Register16_WithPSW_low,	"=", "M[SP]"},
		{InstructionArguments::Register16_WithPSW_high,	"=", "M[SP + 1]"},
		{"[SP]",									"=", "[SP] + 2"},
		{"[PC]",									"=", "[PC] + 1"}
},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::STACK_OPS},
		{0xC1,0xD1,0xE1,0xF1}}
	},


	{ "shld",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"��������� ������������ �������� ���� ��������� HL �� ������ ������ �������� ����������",
	{
		{"M[",InstructionArguments::Value16,"]",		"=","[L]"},
		{"M[",InstructionArguments::Value16," + 1]",	"=","[H]"},
		{"[PC]",								"=","[PC] + 3"}
	},
	{16},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x22}}
	},


	{ "lhld",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"��������� ������������ �������� �� ������ ������ �������� ���������� � ���� ��������� HL",
	{
		{"[L]",		"=","M[",InstructionArguments::Value16 ,"]"},
		{"[H]",		"=","M[",InstructionArguments::Value16," + 1]"},
		{"[PC]",	"=","[PC] + 3" }
	},
	{16},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x2A}}
	},


	{ "stax",{
	{InstructionArguments::Register16_OnlyBD},
	{},
	u8"��������� �������� ������������ � ������ �� ������ ���� ���������",
	{
		{"M[",InstructionArguments::Register16_OnlyBD,"]","=","[A]"},
		{"[PC]",									"=","[PC] + 1"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x02,0x12}}
	},


	{ "ldax",{
	{InstructionArguments::Register16_OnlyBD},
	{},
	u8"��������� ����� �� ������ ���� ��������� � �����������",
	{
		{"[A]",		"=","M[",InstructionArguments::Register16_OnlyBD,"]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x0A,0x1A}}
	},


	{ "sta",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"��������� �������� �� ����������� �� ������ ������ �������� ����������",
	{
		{"M[",InstructionArguments::Value16,"]",	"=","[A]"},
		{"[PC]",							"=","[PC] + 3"}
	},
	{13},
	InstructionTicksMean::Always,
	FlagsList{
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected,
			InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x32}}
	},


	{ "lda",{
	{InstructionArguments::Value16},
	{InstructionBytes::Adress_low,InstructionBytes::Adress_high},
	u8"��������� �������� �� ������ �� ������ �������� ���������� � �����������",
	{
		{"[A]",		"=","M[",InstructionArguments::Value16,"]"},
		{"[PC]",	"=","[PC] + 3"}
	},
	{13},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0x3A}}
	},


	{ "lxi",{
	{InstructionArguments::Register16_WithSP,InstructionArguments::Value16},
	{InstructionBytes::Value_low,InstructionBytes::Value_high},
	u8"���������� ������������ ��������� � ���� ���������",
	{
		{InstructionArguments::Register16_WithSP_low,	"=",InstructionArguments::Value16_low},
		{InstructionArguments::Register16_WithSP_high,"=",InstructionArguments::Value16_high},
		{"[PC]",								"=","[PC] + 3"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE, InstructionCategory::STACK_OPS},
	{0x01,0x11,0x21,0x31}}
	},


	{ "xchg",{
	{},
	{},
	u8"������ ������� �������� ������������ ����� ��� ��������� DE � HL",
	{
		{"swap([DE], [HL])"},
		{"[PC] = [PC] + 1"}
	},
	{4},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::MOVE_LOAD_STORE},
	{0xEB}}
	},



	{ "xthl",{
	{},
	{},
	u8"������ ������� �������� ������ �� ������ SP c ��������� �������� L, � ����� � ������� ������ (SP + 1) � ��������� H. ������ ����������, � �������� SP �� ����������",
	{
		{"swap([H], Memory[SP + 1])"},
		{"swap([L], Memory[SP])"},
		{"[PC] = [PC] + 1"}
	},
	{18},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::STACK_OPS},
	{0xE3}}
	},


	{ "pchl",{
	{},
	{},
	u8"��������� �������� ����� �� ��� ��������� HL � ����� ������� ������� ���������� PC",
	{
		{"[PC] = [HL]"}
	},
	{5},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::JUMP},
	{0xE9}}
	},


	{ "sphl",{
	{},
	{},
	u8"��������� �������� ���� �������� ����� ���� ��������� HL � ���� SP. ��� ���� SP ���������� �� ���",
	{
		{"[SP]",	"=","[HL]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{5},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::STACK_OPS},
	{0xF9}}
	},


	{ "dad",{
	{InstructionArguments::Register16_WithSP},
	{},
	u8"����������� � ����� �� ���� ��������� HL, ����� �� ��������� ���� ���������",
	{
		{"Temp",		"=","[HL] + ",InstructionArguments::Register16_WithSP},
		{"[Carry]",		"=","(Temp > 0xffff)"},
		{"[HL]",		"=","Temp" },
		{"[PC]",		"=","[PC] + 1"}
	},
	{10},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ADD},
	{0x09,0x19,0x29,0x39}}
	},


	{ "inx",{
	{InstructionArguments::Register16_WithSP},
	{},
	u8"���������� �� ������� ����� ����������� � ���� ���������",
	{
		{InstructionArguments::Register16_WithSP,	"=",InstructionArguments::Register16_WithSP," + 1"},
		{"[PC]",							"=","[PC] + 1"}
	},
	{5},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::INCREMENT,InstructionCategory::STACK_OPS},
	{0x03,0x13,0x23,0x33}}
	},


	{ "inr",{
	{InstructionArguments::Register8},
	{},
	u8"���������� �������� ��� ������ �� �������",
	{
		{InstructionArguments::Register8,	"=",InstructionArguments::Register8," + 1"},
		{"[Zero]",					"=","(",InstructionArguments::Register8," == 0)"},
		{"[PC]",					"=","[PC] + 1"}
	},
	{10,5},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::INCREMENT},
	{0x04,0x0C,0x14,0x1C,0x24,0x2C,0x34,0x3C}}
	},


	{ "dcx",{
	{InstructionArguments::Register16_WithSP},
	{},
	u8"���������� �� ������� ����� ����������� � ���� ���������",
	{
		{InstructionArguments::Register16_WithSP,	"=", InstructionArguments::Register16_WithSP," - 1"},
		{"[PC]",									"=", "[PC] + 1" }
	},
	{5},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{ InstructionCategory::DECREMENT, InstructionCategory::STACK_OPS},
	{0x0B,0x1B,0x2B,0x3B}}
	},


	{ "dcr",{
	{InstructionArguments::Register8},
	{},
	u8"���������� �������� ��� ������ �� �������",
	{
		{InstructionArguments::Register8,	"=",InstructionArguments::Register8," - 1"},
		{"[Zero]",					"=","(",InstructionArguments::Register8," == 0)"},
		{"[PC]",					"=","[PC] + 1"}
	},
	{10,5},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::DECREMENT},
	{0x05,0x0D,0x15,0x1D,0x25,0x2D,0x35,0x3D}}
	},


	{ "add",{
	{InstructionArguments::Register8},
	{},
	u8"�������������� �������� �������� ������������ � �������� ��� ������(�� ������ HL)",
	{
		{"Temp",	"=","[A] + ",InstructionArguments::Register8},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)" },
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::ADD},
	{0x80,0x80,0x87}}
	},


	{ "adc",{
	{InstructionArguments::Register8},
	{},
	u8"�������������� �������� �������� ������������ � (�������� ��� ������(�� ������ HL)) � ������ Carry",
	{
		{"Temp",	"=","[A] + ",InstructionArguments::Register8," + [Carry]"},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ADD},
	{0x88,0x88,0x8F}}
	},


	{ "adi",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"�������������� �������� �������� ������������ � ����������",
	{
		{"Temp",	"=","[A] + ",InstructionArguments::Value8},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
	{InstructionCategory::ADD},
	{0xC6}}
	},


	{ "aci",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"�������������� �������� �������� ������������ � ���������� � ������ Carry",
	{
		{"Temp",	"=","[A] + ",InstructionArguments::Value8," + [Carry]"},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::ADD},
	{0xCE}}
	},


	{ "sub",{
	{InstructionArguments::Register8},
	{},
	u8"�������������� ��������� �� �������� ������������ �������� ������(�� ������ HL) ��� ��������",
	{
		{"[Carry]",	"=","([A] < ",InstructionArguments::Register8,")"},
		{"[A]",		"=","[A] - ",InstructionArguments::Register8},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::SUBTRACT},
	{0x90,0x90,0x97}}
	},


	{ "sbb",{
	{InstructionArguments::Register8},
	{},
	u8"�������������� ��������� �� �������� ������������ �������� (������(�� ������ HL) ��� ��������) � ������ Carry",
	{
		{"[Carry]",	"=","([A] < ",InstructionArguments::Register8," + [Carry])"},
		{"[A]",		"=","[A] - ",InstructionArguments::Register8," - [Carry]"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1" }
	},
	{7,4},
	InstructionTicksMean::M_Used,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::SUBTRACT},
	{0x98,0x98,0x9F}}
	},


	{ "sui",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"�������������� ��������� �� �������� ������������ ���������",
	{
		{"[Carry]",	"=","([A] < ",InstructionArguments::Value8,")"},
		{"[A]",		"=","[A] - ",InstructionArguments::Value8},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::SUBTRACT},
	{0xD6}}
	},


	{ "sbi",{
	{InstructionArguments::Value8},
	{InstructionBytes::Value},
	u8"�������������� ��������� �� �������� ������������ ��������� � ����� Carry",
	{
		{"[Carry]",	"=","([A] < ",InstructionArguments::Value8," + [Carry])"},
		{"[A]",		"=","([A] - ",InstructionArguments::Value8," - [Carry])"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","([PC] + 2)"}
},
	{7},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected,
		InstructionFlagsState::Affected},
		{InstructionCategory::SUBTRACT},
	{0xDE}}
	},


	{ "rst",{
	{InstructionArguments::ValueSpecial},
	{InstructionBytes::Value},
	u8"Call [����� * 8]",
	{
		{"[SP]",			"=","[SP] - 2"},
		{"M[SP]",			"=","([PC] + 3).low"},
		{"M[SP + 1]",		"=","([PC] + 3).high"},
		{"[PC]",			"=","(",InstructionArguments::ValueSpecial," * 8)"}
	},
	{11},
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
		{InstructionCategory::RESTART},
	{0xC7,0xCF,0xD7,0xDF,0xE7,0xEF,0xF7,0xFF}}
	 },



	 { "daa",{
	 {},
	 {},
	 u8"������������ ���������� �������� A ��� ������������ ������� BCD",
	 {
		 {u8"�� ���� ��� ��� �������."}
	 },
	 {4},
	 InstructionTicksMean::Always,
	 FlagsList{
		 InstructionFlagsState::Affected,
		 InstructionFlagsState::Affected,
		 InstructionFlagsState::Affected,
		 InstructionFlagsState::Affected,
		 InstructionFlagsState::Affected },
	{InstructionCategory::SPECIALS},
	{0x27}}

	},

	{ "ei",{
	{},
	{},
	u8"�������� ����������",
	{
		{u8"��� ���������� �� �����������."}
	},
	{ 4 },
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected},
	{InstructionCategory::CONTROL},
	{0xFB}}
	},


	{ "di",{
	{},
	{},
	u8"��������� ����������",
	{
		{u8"��� ���������� �� �����������."}
	},
	{ 4 },
	InstructionTicksMean::Always,
	FlagsList{
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected,
		InstructionFlagsState::Unaffected },
	{InstructionCategory::CONTROL},
	{0xF3}}
	}

};

