#include "InfoInstruction.Data.h"




const robin_hood::unordered_flat_map<std::string, InstructionInfo> map_InstructionInfo = {
	// HLT------------------------------------------
		{"hlt",{
		{},{},
		u8"��������� ������ ����������.",
		u8"Stop",
		{7},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// NOP------------------------------------------
		{"nop",{
		{},
		{},
		u8"������ ������� ������� �������� ���� ����",
		u8"1. [PC] = [PC] + 1",
		{4},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// IN------------------------------------------
		{"in",{
		{ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"������ �������� � ����������� �� �������� �����",
		u8"1. [A]  = Port[�����.8]\n"
		  "2. [PC] = [PC] + 2",
		{10},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// OUT------------------------------------------
		{"out",{
		{ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"�������� �������� �� ������������ �� ������� ����",
		u8"1. Port[�����.8] = [A]\n"
		  "2. [PC]          = [PC] + 2",
		{10},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// MOV------------------------------------------
		{"mov",{
		{ENUM_Arguments::Register8,ENUM_Arguments::Register8},
		{},
		u8"����������� �������� ����� ���������� ��� �������(�� ������ HL)",
		u8"1. [���.8] = [���.8]\n"
		  "2. [PC]    = [PC] + 1",
		{7,5},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// MVI------------------------------------------
		{"mvi",{
		{ENUM_Arguments::Register8,ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"������ ��������� � ������� ��� ������",
		u8"1. [���.8] = [�����.8]\n"
		  "2. [PC]    = [PC] + 2",
		{10,7},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},

	// CMP------------------------------------------
		{"cmp",{
		{ENUM_Arguments::Register8},
		{},
		u8"��������� �������� ����� ������������� � ���������� ��� �������(�� ������ HL)",
		u8"1. Temp    = ([A] - [���.8])\n"
		  "2. [Zero]  = [Temp == 0]\n"
		  "3. [Carry] = [A] < [���.8]\n"
		  "4. [PC]    = [PC] + 1",
		{7,4},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected}}
	},

	// CPI------------------------------------------
	{ "cpi",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"��������� �������� ������������ � ����������",
	u8"1. Temp    = [A] - [�����.8]\n"
	  "2. [Zero]  = [Temp == 0]\n"
	  "3. [Carry] = [A] < [�����.8]\n"
	  "4. [PC]    = [PC] + 1",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},

	// ANA------------------------------------------
	{ "ana",{
	{ENUM_Arguments::Register8},
	{},
	u8"���������� � �������� ������������ � ��������� ��� �������(�� ������ HL)",
	u8"1. [A]     = [A] & [���.8]\n"
	  "2. [Zero]  = ([A] == 0)\n"
	  "3. [Carry] = 0\n"
	  "4. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},


	// ANI------------------------------------------
	{ "ani",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"���������� � ������������ � ����������",
	u8"1. [A]     = [A] & [�����.8]\n"
	  "2. [Zero]  = ([A] == 0)\n"
	  "3. [Carry] = 0\n"
	  "4. [PC]    = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
		FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},

	// ORA------------------------------------------
	{ "ora",{
	{ENUM_Arguments::Register8},
	{},
	u8"���������� ��� �������� ������������ � ��������� ��� �������(�� ������ HL)",
	u8"1. [A]     = [A] | [���.8]\n"
	  "2. [Zero]  = ([A] == 0)\n"
	  "3. [Carry] = 0\n"
	  "4. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
		FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},

	// ORI------------------------------------------
	{ "ori",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"���������� ��� �������� ������������ � ����������",
	u8"1. [A]           = [A] | [�����.8]\n"
	  "2. [Zero]        = ([A] == 0)\n"
	  "3. [Carry]       = 0\n"
	  "4. [Auxilary C.] = 0\n"
	  "5. [PC]          = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},

	// XRA------------------------------------------
	{ "xra",{
	{ENUM_Arguments::Register8},
	{},
	u8"���������� ����������� ��� �������� ������������ � ��������� ��� �������(�� ������ HL)",
	u8"1. [A]           = [A] ^ [���.8]\n"
	  "2. [Zero]        = ([A] == 0)\n"
	  "3. [Carry]       = 0\n"
	  "4. [Auxilary C.] = 0\n"
	  "5. [PC] = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},

	// XRI------------------------------------------
	{ "xri",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"���������� ����������� ��� �������� ������������ � ����������",
	u8"1. [A]           = [A] ^ [�����.8]\n"
	  "2. [Zero]        = ([A] == 0)\n"
	  "3. [Carry]       = 0\n"
	  "4. [Auxilary C.] = 0\n"
	  "5. [PC]          = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset}}
	},

	// RLC------------------------------------------
	{ "rlc",{
	{},
	{},
	u8"��� ���� ������������ ���������� ����� �� ���� ���. �������� ���������� ���������� ���� ��������������� � ���� Carry � ��������������� � ������ ��� ������������",
	u8"1. [Carry] = A[7]\n"
	  "2. [A]     = (A << 1) | Carry\n"
	  "3. [PC]    = PC + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected}}
	},

	// RAL------------------------------------------
	{ "ral",{
	{},
	{},
	u8"��� ���� ������������ ���������� ����� �� ���� ���. ��������� ����� Carry ��������������� � ������ ��� ������������. �������� ���������� ���� (�� ���������� ������������) ��������������� � ���� Carry",
	u8"1. Temp    = A[7]\n"
	  "2. [A]     = (A << 1) | Carry\n"
	  "3. [Carry] = Temp\n"
	  "4. [PC]    = PC + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected}}
	},

	// RRC------------------------------------------
	{ "rrc",{
	{},
	{},
	u8"��� ���� ������������ ���������� ������ �� ���� ���. �������� ������� ���� ������������ ��������������� � ���� Carry � ��������������� � ��������� ��� ������������",
	u8"1. Carry = A[0]\n"
	  "2. [A]   = (A >> 1) | (Carry << 7)\n"
	  "3. [PC]  = PC + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected}}
	},

	// RAR------------------------------------------
	{ "rar",{
	{},
	{},
	u8"��� ���� ������������ ���������� ������ �� ���� ���. ��������� ����� Carry ��������������� � ��������� ��� ������������. �������� ������� ���� (�� ���������� ������������) ��������������� � ���� Carry",
	u8"1. Temp = A[0]\n"
	  "2. [A] = (A >> 1) | (Carry << 7)\n"
	  "3. [Carry] = Temp\n"
	  "4. [PC] = PC + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected}}
	},

	// STC------------------------------------------
	{ "stc",{
	{},
	{},
	u8"������������� ���� Carry � ��������� True.",
	u8"1. [Carry] = [True]\n"
	  "2. [PC]    = [PC] + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Set}}
	},

	// CMA------------------------------------------
	{ "cma",{
	{},
	{},
	u8"����������� �������� �������� ������������.",
	u8"1. [A]  = ![A]\n"
	  "2. [PC] = [PC] + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// CMC------------------------------------------
	{ "cmc",{
	{},
	{},
	u8"����������� ���� Carry.",
	u8"1. [Carry] = ![Carry]\n"
	  "2. [PC]    = [PC] + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected }}
	},

	// RET------------------------------------------
	{ "ret",{
	{},
	{},
	u8"������ �� ����� ���������� � �������� �����.",
	u8"1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RZ------------------------------------------
	{ "rz",{
	{},
	{},
	u8"���� ���� Zero = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RC------------------------------------------
	{ "rc",{
	{},
	{},
	u8"���� ���� Carry = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RPE------------------------------------------
	{ "rpe",{
	{},
	{},
	u8"���� ���� Paruty = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RM------------------------------------------
	{ "rm",{
	{},
	{},
	u8"���� ���� Sign = 1, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RNZ------------------------------------------
	{ "rnz",{
	{},
	{},
	u8"���� ���� Zero = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RNC------------------------------------------
	{ "rnc",{
	{},
	{},
	u8"���� ���� Carry = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// RPO------------------------------------------
	{ "rpo",{
	{},
	{},
	u8"���� ���� Paruty = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	"1. [PC].low  = M[SP]\n"
	"2. [PC].high = M[SP + 1]\n"
	"3. [SP]      = [SP] + 2\n"
	"�����:\n"
	"1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
		},
	// RP------------------------------------------
	{ "rp",{
	{},
	{},
	u8"���� ���� Sign = 0, �� ������ �� ����� ���������� � �������� ����� � ���������� ����� �� ���, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 1",
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// JMP------------------------------------------
	{ "jmp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"������ PC �� ������ �������� ���������",
	u8"1. [PC] = [�����.16]",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// JZ------------------------------------------
	{ "jz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Zero = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// JC------------------------------------------
	{ "jc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Carry = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// JPE------------------------------------------
	{ "jpe",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Paruty = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},

	// JM------------------------------------------
	{ "jm",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Sign = 1, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "jnz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Zero = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "jnc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Carry = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "jpo",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Paruty = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	"1. [PC] = [�����.16]\n"
	"�����:\n"
	"1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "jp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ����  Sign = 0, �� ������ PC �� ������ �������� ���������, ����� ������� �������",
	u8"���� ������� ����������:\n"
	  "1. [PC] = [�����.16]\n"
	  "�����:\n"
	  "1. [PC] = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "call",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]",
	{17},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Zero = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Carry = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cpe",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Paruty = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cm",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Sign = 1, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},


	{ "cnz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Zero = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cnc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Carry = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cpo",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Paruty = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "cp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"���� ���� Sign = 0, �� ���������� ���������� ������ ������� � ���� � ������ PC �� ����� ��������� ����������",
	u8"���� ������� ����������:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [�����.16]\n"
	  "�����:\n"
	  "1. [PC]      = [PC] + 3",
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "push",{
	{ENUM_Arguments::Register16_WithPSW},
	{},
	u8"���������� ������������� ����� �� ���� ��������� � �������� �����",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP + 1] = [���.16].high\n"
	  "3. M[SP]     = [���.16].low.\n"
	  "4. [PC]      = [PC] + 1",
	{11},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "pop",{
	{ENUM_Arguments::Register16_WithPSW},
	{},
	u8"���������� �� �������� ����� ������������� ����� � ���� ���������",
	u8"1. M[SP]     = [���.16].low\n"
	  "2. M[SP + 1] = [���.16].high\n"
	  "3. [SP]      = [SP] + 2\n"
	  "4. [PC]      = [PC] + 1",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "shld",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"��������� ������������ �������� ���� ��������� HL �� ������ ������ �������� ����������",
	u8"1. M[�����.16]     = [L]\n"
	  "2. M[�����.16 + 1] = [H]\n"
	  "3. [PC]            = [PC] + 3",
	{16},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "lhld",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"��������� ������������ �������� �� ������ ������ �������� ���������� � ���� ��������� HL",
	u8"1. [L]  = M[�����.16]\n"
	  "2. [H]  = M[�����.16 + 1]\n"
	  "3. [PC] = [PC] + 3",
	{16},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


		{ "stax",{
		{ENUM_Arguments::Register16_OnlyBD},
		{},
		u8"��������� �������� ������������ � ������ �� ������ ���� ���������",
		u8"1. M[���.16] = [A]\n"
		  "2. [PC]      = [PC] + 1",
		{7},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},


	{ "ldax",{
	{ENUM_Arguments::Register16_OnlyBD},
	{},
	u8"��������� ����� �� ������ ���� ��������� � �����������",
	u8"1. [A]  = M[���.16]\n"
	  "2. [PC] = [PC] + 1",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},


	{ "sta",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"��������� �������� �� ����������� �� ������ ������ �������� ����������",
	u8"1. M[�����.16] = [A]\n"
	  "2. [PC]        = [PC] + 3",
	{13},
	ENUM_TicksMean::Always,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected}}
	},


	{ "lda",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"��������� �������� �� ������ �� ������ �������� ���������� � �����������",
	u8"1. [A]  = M[�����.16]\n"
	  "2. [PC] = [PC] + 3",
	{13},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "lxi",{
	{ENUM_Arguments::Register16_WithSP,ENUM_Arguments::Value16},
	{ENUM_Bytes::Value_low,ENUM_Bytes::Value_high},
	u8"���������� ������������ ��������� � ���� ���������",
	u8"1. [���.16] = [�����.16]\n"
	  "2. [PC]     = [PC] + 3",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "xchg",{
	{},
	{},
	u8"������ ������� �������� ������������ ����� ��� ��������� DE � HL",
	u8"1. swap([DE], [HL])\n"
	  "2. [PC] = [PC] + 1",
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},



	{ "xthl",{
	{},
	{},
	u8"������ ������� �������� ������ �� ������ SP c ��������� �������� L, � ����� � ������� ������ (SP + 1) � ��������� H. ������ ����������, � �������� SP �� ����������",
	u8"1. swap([H], Memory[SP + 1])\n"
	  "2. swap([L], Memory[SP])\n"
	  "3. [PC] = [PC] + 1",
	{18},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "pchl",{
	{},
	{},
	u8"��������� �������� ����� �� ��� ��������� HL � ����� ������� ������� ���������� PC",
	u8"1. [PC] = [HL]",
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "sphl",{
	{},
	{},
	u8"��������� �������� ���� �������� ����� ���� ��������� HL � ���� SP. ��� ���� SP ���������� �� ���",
	u8"1. [SP] = [HL]\n"
	  "2. [PC] = [PC] + 1",
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "dad",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"����������� � ����� �� ���� ��������� HL, ����� �� ��������� ���� ���������",
	u8"1. Temp    = [HL] + [���.16]\n"
	  "2. [Carry] = (Temp > 0xffff)\n"
	  "3. [HL]    = Temp\n"
	  "4. [PC]    = [PC] + 1",
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected}}
	},


	{ "inx",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"���������� �� ������� ����� ����������� � ���� ���������",
	u8"1. [���.16] = [���.16] + 1\n"
	  "2. [PC]     = [PC] + 1",
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "inr",{
	{ENUM_Arguments::Register8},
	{},
	u8"���������� �������� ��� ������ �� �������",
	u8"1. [���.8] = [���.8] + 1\n"
	  "2. [Zero]  = ([���.8] == 0)\n"
	  "3. [PC]    = [PC] + 1",
	{10,5},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "dcx",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"���������� �� ������� ����� ����������� � ���� ���������",
	u8"1. [���.16] = [���.16] - 1\n"
	  "2. [PC]     = [PC] + 1",
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "dcr",{
	{ENUM_Arguments::Register8},
	{},
	u8"���������� �������� ��� ������ �� �������",
	u8"1. [���.8] = [���.8] - 1\n"
	  "2. [Zero]  = ([���.8] == 0)\n"
	  "3. [PC]    = [PC] + 1",
	{10,5},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "add",{
	{ENUM_Arguments::Register8},
	{},
	u8"�������������� �������� �������� ������������ � �������� ��� ������(�� ������ HL)",
	u8"1. Temp    = [A] + [���.8]\n"
	  "2. [A]     = Temp\n"
	  "3. [Carry] = (Temp> 0xff)\n"
	  "4. [Zero]  = (A == 0)\n"
	  "5. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "adc",{
	{ENUM_Arguments::Register8},
	{},
	u8"�������������� �������� �������� ������������ � (�������� ��� ������(�� ������ HL)) � ������ Carry",
	u8"1. Temp    = [A] + [���.8] + [Carry]\n"
	  "2. [A]     = Temp\n"
	  "3. [Carry] = (Temp > 0xff)\n"
	  "4. [Zero]  = (A == 0)\n"
	  "5. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
		},


		{ "adi",{
		{ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"�������������� �������� �������� ������������ � ����������",
		u8"1. Temp    = [A] + [�����.8]\n"
		  "2. [A]     = Temp\n"
		  "3. [Carry] = (Temp> 0xff)\n"
		  "4. [Zero]  = (A == 0)\n"
		  "5. [PC]    = [PC] + 2",
		{7},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected}}
	},


	{ "aci",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"�������������� �������� �������� ������������ � ���������� � ������ Carry",
	u8"1. Temp    = [A] + [�����.8] + [Carry]\n"
	  "2. [A]     = Temp\n"
	  "3. [Carry] = (Temp > 0xff)\n"
	  "4. [Zero]  = (A == 0)\n"
	  "5. [PC]    = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "sub",{
	{ENUM_Arguments::Register8},
	{},
	u8"�������������� ��������� �� �������� ������������ �������� ������(�� ������ HL) ��� ��������",
	u8"1. [Carry] = (A < ���.8)\n"
	  "2. [A]     = [A] - [���.8]\n"
	  "3. [Zero]  = (A == 0)\n"
	  "4. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "sbb",{
	{ENUM_Arguments::Register8},
	{},
	u8"�������������� ��������� �� �������� ������������ �������� (������(�� ������ HL) ��� ��������) � ������ Carry",
	u8"1. [Carry] = (A < ���.8 + Carry)\n"
	  "2. [A]     = [A] - [���.8] - [Carry]\n"
	  "3. [Zero]  = (A == 0)\n"
	  "4. [PC]    = [PC] + 1",
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "sui",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"�������������� ��������� �� �������� ������������ ���������",
	u8"1. [Carry] = (A < �����.8)\n"
	  "2. [A]     = [A] - [���.8]\n"
	  "3. [Zero]  = (A == 0)\n"
	  "4. [PC]    = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "sbi",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"�������������� ��������� �� �������� ������������ ��������� � ����� Carry",
	u8"1. [Carry] = (A < �����.8 + Carry)\n"
	  "2. [A]     = [A] - [�����.8] - [Carry]\n"
	  "3. [Zero]  = (A == 0)\n"
	  "4. [PC]    = [PC] + 2",
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected}}
	},


	{ "rst",{
	{ENUM_Arguments::ValueSpecial},
	{ENUM_Bytes::Value},
	u8"Call [����� * 8]",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [����� * 8]",
	{11},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	 },



	 { "daa",{
	 {},
	 {},
	 u8"������������ ���������� �������� A ��� ������������ ������� BCD",
	 u8"�� ���� ��� ��� �������.",
	 {4},
	 ENUM_TicksMean::Always,
	 FlagsList{
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected }}

	},

	{ "ei",{
	{},
	{},
	u8"�������� ����������",
	u8"��� ���������� �� �����������.",
	{ 4 },
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected}}
	},


	{ "di",{
	{},
	{},
	u8"��������� ����������",
	u8"��� ���������� �� �����������.",
	{ 4 },
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected }}

	}

};

