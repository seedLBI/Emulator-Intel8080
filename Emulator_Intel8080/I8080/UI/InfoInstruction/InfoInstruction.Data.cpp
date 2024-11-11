#include "InfoInstruction.Data.h"




const robin_hood::unordered_flat_map<std::string, InstructionInfo> map_InstructionInfo = {
	// HLT------------------------------------------
		{"hlt",{
		{},{},
		u8"Остановка работы процессора.",
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
		u8"Пустая команда которая занимает один байт",
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
		u8"Чтение значения в аккумулятор из внешнего порта",
		u8"1. [A]  = Port[Число.8]\n"
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
		u8"Отправка значения из аккумулятора во внешний порт",
		u8"1. Port[Число.8] = [A]\n"
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
		u8"Перемешение значений между регистрами или памятью(по адресу HL)",
		u8"1. [Рег.8] = [Рег.8]\n"
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
		u8"Запись константы в регистр или память",
		u8"1. [Рег.8] = [Число.8]\n"
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
		u8"Сравнение значений между акуммулятором и регистрами или памятью(по адресу HL)",
		u8"1. Temp    = ([A] - [Рег.8])\n"
		  "2. [Zero]  = [Temp == 0]\n"
		  "3. [Carry] = [A] < [Рег.8]\n"
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
	u8"Сравнение значения аккумулятора с константой",
	u8"1. Temp    = [A] - [Число.8]\n"
	  "2. [Zero]  = [Temp == 0]\n"
	  "3. [Carry] = [A] < [Число.8]\n"
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
	u8"Логическое И значения аккумулятора с регистром или памятью(по адресу HL)",
	u8"1. [A]     = [A] & [Рег.8]\n"
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
	u8"Логическое И аккумулятора с константой",
	u8"1. [A]     = [A] & [Число.8]\n"
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
	u8"Логическое ИЛИ значения аккумулятора с регистром или памятью(по адресу HL)",
	u8"1. [A]     = [A] | [Рег.8]\n"
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
	u8"Логическое ИЛИ значения аккумулятора с константой",
	u8"1. [A]           = [A] | [Число.8]\n"
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
	u8"Логическое исключающее ИЛИ значение аккумулятора с регистром или памятью(по адресу HL)",
	u8"1. [A]           = [A] ^ [Рег.8]\n"
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
	u8"Логичиское исключающее ИЛИ значение аккумулятора с константой",
	u8"1. [A]           = [A] ^ [Число.8]\n"
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
	u8"Все биты аккумулятора сдвигаются влево на один бит. Значение последнего сдвинутого бита устанавливается в флаг Carry и устанавливается в первый бит аккумулятора",
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
	u8"Все биты аккумулятора сдвигаются влево на один бит. Состояние флага Carry устанавливается в первый бит аккумулятора. Значение последнего бита (не сдвинутого аккумулятора) устанавливается в флаг Carry",
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
	u8"Все биты аккумулятора сдвигаются вправо на один бит. Значение первого бита аккумулятора устанавливается в флаг Carry и устанавливается в последний бит аккумулятора",
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
	u8"Все биты аккумулятора сдвигаются вправо на один бит. Состояние флага Carry устанавливается в последний бит аккумулятора. Значение первого бита (не сдвинутого аккумулятора) устанавливается в флаг Carry",
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
	u8"Устанавливает флаг Carry в состояние True.",
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
	u8"Инвентирует побитово значение аккумулятора.",
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
	u8"Инвентирует флаг Carry.",
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
	u8"Прыжок на адрес записанный в верхушке стэка.",
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
	u8"Если флаг Zero = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Sign = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Zero = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	"1. [PC].low  = M[SP]\n"
	"2. [PC].high = M[SP + 1]\n"
	"3. [SP]      = [SP] + 2\n"
	"Иначе:\n"
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
	u8"Если флаг Sign = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC].low  = M[SP]\n"
	  "2. [PC].high = M[SP + 1]\n"
	  "3. [SP]      = [SP] + 2\n"
	  "Иначе:\n"
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
	u8"Прыжок PC по адресу заданной константы",
	u8"1. [PC] = [Число.16]",
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
	u8"Если флаг Zero = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Sign = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Zero = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	"1. [PC] = [Число.16]\n"
	"Иначе:\n"
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
	u8"Если флаг  Sign = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	u8"Если условие выполненно:\n"
	  "1. [PC] = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]",
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
	u8"Если флаг Zero = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Sign = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Zero = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Carry = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Paruty = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Если флаг Sign = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	u8"Если условие выполненно:\n"
	  "1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число.16]\n"
	  "Иначе:\n"
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
	u8"Сохранение двухбайтового числа из пары регистров в верхушку стэка",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP + 1] = [Рег.16].high\n"
	  "3. M[SP]     = [Рег.16].low.\n"
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
	u8"Извлечение из верхушки стэка двухбайтового числа в пару регистров",
	u8"1. M[SP]     = [Рег.16].low\n"
	  "2. M[SP + 1] = [Рег.16].high\n"
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
	u8"Сохраняет двухбайтовое значение пары регистров HL по адресу памяти заданной константой",
	u8"1. M[Число.16]     = [L]\n"
	  "2. M[Число.16 + 1] = [H]\n"
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
	u8"Загружает двухбайтовое значение по адресу памяти заданной константой в пару регистров HL",
	u8"1. [L]  = M[Число.16]\n"
	  "2. [H]  = M[Число.16 + 1]\n"
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
		u8"Сохраняет значение аккумулятора в память по адресу пары регистров",
		u8"1. M[Рег.16] = [A]\n"
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
	u8"Загружает число по адресу пары регистров в аккумулятор",
	u8"1. [A]  = M[Рег.16]\n"
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
	u8"Сохраняет значение из аккумулятор по адресу памяти заданной константой",
	u8"1. M[Число.16] = [A]\n"
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
	u8"Загружает значение из памяти по адресу заданной константой в аккумулятор",
	u8"1. [A]  = M[Число.16]\n"
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
	u8"Записывает двухбайтовую константу в пару регистров",
	u8"1. [Рег.16] = [Число.16]\n"
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
	u8"Меняет местами значения двухбайтовых чисел пар регистров DE и HL",
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
	u8"Меняет местами значение памяти по адресу SP c значением регистра L, и также с адресом памяти (SP + 1) и регистром H. Память поменяется, а значение SP не поменяется",
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
	u8"Загружает значение числа из пар регистров HL в адрес текущей позиции процессора PC",
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
	u8"Загружает значение двух байтвого числа пары регистров HL в стэк SP. При этом SP увеличится на два",
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
	u8"Прибавляние к числу из пары регистров HL, числа из указанной пары регистров",
	u8"1. Temp    = [HL] + [Рег.16]\n"
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
	u8"Увелечение на единицу числа записанного в паре регистров",
	u8"1. [Рег.16] = [Рег.16] + 1\n"
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
	u8"Увелечение регистра или памяти на единицу",
	u8"1. [Рег.8] = [Рег.8] + 1\n"
	  "2. [Zero]  = ([Рег.8] == 0)\n"
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
	u8"Уменьшение на единицу числа записанного в паре регистров",
	u8"1. [Рег.16] = [Рег.16] - 1\n"
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
	u8"Уменьшение регистра или памяти на единицу",
	u8"1. [Рег.8] = [Рег.8] - 1\n"
	  "2. [Zero]  = ([Рег.8] == 0)\n"
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
	u8"Арифмитическое сложение значения аккумулятора и регистра или памяти(по адресу HL)",
	u8"1. Temp    = [A] + [Рег.8]\n"
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
	u8"Арифмитическое сложение значения аккумулятора и (регистра или памяти(по адресу HL)) с флагом Carry",
	u8"1. Temp    = [A] + [Рег.8] + [Carry]\n"
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
		u8"Арифмитическое сложения значения аккумулятора с константой",
		u8"1. Temp    = [A] + [Число.8]\n"
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
	u8"Арифмитическое сложения значения аккумулятора с константой и флагом Carry",
	u8"1. Temp    = [A] + [Число.8] + [Carry]\n"
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
	u8"Арифмитическое вычитание из значения аккумулятора значение памяти(по адресу HL) или регистра",
	u8"1. [Carry] = (A < Рег.8)\n"
	  "2. [A]     = [A] - [Рег.8]\n"
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
	u8"Арифмитическое вычитание из значения аккумулятора значение (памяти(по адресу HL) или регистра) с флагом Carry",
	u8"1. [Carry] = (A < Рег.8 + Carry)\n"
	  "2. [A]     = [A] - [Рег.8] - [Carry]\n"
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
	u8"Арифмитическое вычитание из значения аккумулятора константы",
	u8"1. [Carry] = (A < Число.8)\n"
	  "2. [A]     = [A] - [Рег.8]\n"
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
	u8"Арифмитическое вычитание из значения аккумулятора константы и флага Carry",
	u8"1. [Carry] = (A < Число.8 + Carry)\n"
	  "2. [A]     = [A] - [Число.8] - [Carry]\n"
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
	u8"Call [Число * 8]",
	u8"1. [SP]      = [SP] - 2\n"
	  "2. M[SP]     = [PC + 3].low\n"
	  "3. M[SP + 1] = [PC + 3].high\n"
	  "4. [PC]      = [Число * 8]",
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
	 u8"Корректирует содержимое регистра A для соответствия формату BCD",
	 u8"Не знаю как это описать.",
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
	u8"Включает прерывание",
	u8"Эта инструкция не реализована.",
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
	u8"Отключает прерывание",
	u8"Эта инструкция не реализована.",
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

