#include "InfoInstruction.Data.h"


const robin_hood::unordered_flat_map<std::string, InstructionInfo> map_InstructionInfo = {
	// HLT------------------------------------------
		{"hlt",{
		{},{},
		u8"Остановка работы процессора.",
		{
			{u8"Стоп"}
		},
		{7},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::CONTROL}}
	},

	// NOP------------------------------------------
		{"nop",{
		{},
		{},
		u8"Пустая команда которая занимает один байт",
		{
			{"[PC]","=","[PC] + 1"}
		},
		{4},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::CONTROL}}
	},

	// IN------------------------------------------
		{"in",{
		{ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"Чтение значения в аккумулятор из внешнего порта",
		{
			{"[A]",		"=", "Port[", ENUM_Arguments::Value8, "]"},
			{"[PC]",	"=", "[PC] + 2"}
		},
		{10},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::INPUT_OUTPUT}}
	},

	// OUT------------------------------------------
		{"out",{
		{ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"Отправка значения из аккумулятора во внешний порт",
		{
			{"Port[", ENUM_Arguments::Value8,"]",	"=", "[A]"},
			{"[PC]",								"=", "[PC] + 2" }
		},
		{10},
		ENUM_TicksMean::Always,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::INPUT_OUTPUT}}
	},

	// MOV------------------------------------------
		{"mov",{
		{ENUM_Arguments::Register8,ENUM_Arguments::Register8},
		{},
		u8"Перемешение значений между регистрами или памятью(по адресу HL)",
		{
			{ENUM_Arguments::Register8,	"=", ENUM_Arguments::Register8},
			{"[PC]",					"=", "[PC] + 1"}
		},
		{7,5},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::MOVE_LOAD_STORE}}
	},

	// MVI------------------------------------------
		{"mvi",{
		{ENUM_Arguments::Register8,ENUM_Arguments::Value8},
		{ENUM_Bytes::Value},
		u8"Запись константы в регистр или память",
		{
			{ENUM_Arguments::Register8,	"=",ENUM_Arguments::Value8},
			{"[PC]",					"=", "[PC] + 2"}
		},
		{10,7},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::MOVE_LOAD_STORE}}
	},

	// CMP------------------------------------------
		{"cmp",{
		{ENUM_Arguments::Register8},
		{},
		u8"Сравнение значений между акуммулятором и регистрами или памятью(по адресу HL)",
		{
			{"Temp",    "=", "([A] - ",ENUM_Arguments::Register8,")"},
			{"[Zero]",  "=", "[Temp == 0]"},
			{"[Carry]", "=", "[A] < ",ENUM_Arguments::Register8},
			{"[PC]",    "=", "[PC] + 1"}
		},
		{7,4},
		ENUM_TicksMean::M_Used,
		FlagsList{
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected,
			ENUM_FlagsState::Affected},
	{ENUM_Category::LOGICAL}}
	},

	// CPI------------------------------------------
	{ "cpi",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Сравнение значения аккумулятора с константой",
	{
		{"Temp",   "=", "[A] - ",ENUM_Arguments::Value8},
		{"[Zero]", "=", "[Temp == 0]"},
		{"[Carry]","=", "[A] < ",ENUM_Arguments::Value8},
		{"[PC]",   "=", "[PC] + 1"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::LOGICAL}}
	},

	// ANA------------------------------------------
	{ "ana",{
	{ENUM_Arguments::Register8},
	{},
	u8"Логическое И значения аккумулятора с регистром или памятью(по адресу HL)",
	{
		{"[A]",    "=", "[A] & ",ENUM_Arguments::Register8},
		{"[Zero]", "=", "([A] == 0)"},
		{"[Carry]","=", "0"},
		{"[PC]",   "=", "[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},


	// ANI------------------------------------------
	{ "ani",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Логическое И аккумулятора с константой",
	{
		{"[A]",    "=","[A] & ",ENUM_Arguments::Value8},
		{"[Zero]", "=","([A] == 0)"},
		{"[Carry]","=","0"},
		{"[PC]",   "=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
		FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},

	// ORA------------------------------------------
	{ "ora",{
	{ENUM_Arguments::Register8},
	{},
	u8"Логическое ИЛИ значения аккумулятора с регистром или памятью(по адресу HL)",
	{
		{"[A]",    "=","[A] | ",ENUM_Arguments::Register8},
		{"[Zero]", "=","([A] == 0)"},
		{"[Carry]","=","0"},
		{"[PC]",   "=","[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
		FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},

	// ORI------------------------------------------
	{ "ori",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Логическое ИЛИ значения аккумулятора с константой",
	{
		{"[A]",				"=","[A] | ", ENUM_Arguments::Value8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},

	// XRA------------------------------------------
	{ "xra",{
	{ENUM_Arguments::Register8},
	{},
	u8"Логическое исключающее ИЛИ значение аккумулятора с регистром или памятью(по адресу HL)",
	{
		{"[A]",				"=","[A] ^ ",ENUM_Arguments::Register8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},

	// XRI------------------------------------------
	{ "xri",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Логичиское исключающее ИЛИ значение аккумулятора с константой",
	{
		{"[A]",				"=","[A] ^ ",ENUM_Arguments::Value8},
		{"[Zero]",			"=","([A] == 0)"},
		{"[Carry]",			"=","0"},
		{"[Auxilary C.]",	"=","0"},
		{"[PC]",			"=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Reset},
	{ENUM_Category::LOGICAL}}
	},

	// RLC------------------------------------------
	{ "rlc",{
	{},
	{},
	u8"Все биты аккумулятора сдвигаются влево на один бит. Значение последнего сдвинутого бита устанавливается в флаг Carry и устанавливается в первый бит аккумулятора",
	{
		{"[Carry]",	"=","A[7]"},
		{"[A]",		"=","([A] << 1) | [Carry]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ROTATE}}
	},

	// RAL------------------------------------------
	{ "ral",{
	{},
	{},
	u8"Все биты аккумулятора сдвигаются влево на один бит. Состояние флага Carry устанавливается в первый бит аккумулятора. Значение последнего бита (не сдвинутого аккумулятора) устанавливается в флаг Carry",
	{
		{"Temp",	"=","A[7]"},
		{"[A]",		"=","(A << 1) | [Carry]"},
		{"[Carry]",	"=","Temp"},
		{"[PC]",	"=","PC + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ROTATE}}
	},

	// RRC------------------------------------------
	{ "rrc",{
	{},
	{},
	u8"Все биты аккумулятора сдвигаются вправо на один бит. Значение первого бита аккумулятора устанавливается в флаг Carry и устанавливается в последний бит аккумулятора",
	{
		{"[Carry]",	"=","A[0]"},
		{"[A]",		"=","([A] >> 1) | ([Carry] << 7)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ROTATE}}
	},

	// RAR------------------------------------------
	{ "rar",{
	{},
	{},
	u8"Все биты аккумулятора сдвигаются вправо на один бит. Состояние флага Carry устанавливается в последний бит аккумулятора. Значение первого бита (не сдвинутого аккумулятора) устанавливается в флаг Carry",
	{
		{"Temp",	"=","A[0]"},
		{"[A]",		"=","([A] >> 1) | ([Carry] << 7)"},
		{"[Carry]",	"=","Temp"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ROTATE}}
	},

	// STC------------------------------------------
	{ "stc",{
	{},
	{},
	u8"Устанавливает флаг Carry в состояние True.",
	{
		{"[Carry]",	"=","True"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Set},
	{ENUM_Category::SPECIALS}}
	},

	// CMA------------------------------------------
	{ "cma",{
	{},
	{},
	u8"Инвентирует побитово значение аккумулятора.",
	{
		{"[A]",		"=", "![A]"},
		{"[PC]",	"=", "[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::SPECIALS}}
	},

	// CMC------------------------------------------
	{ "cmc",{
	{},
	{},
	u8"Инвентирует флаг Carry.",
	{
		{"[Carry]",	"=", "![Carry]"},
		{"[PC]",	"=", "[PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected },
	{ENUM_Category::SPECIALS}}
	},

	// RET------------------------------------------
	{ "ret",{
	{},
	{},
	u8"Прыжок на адрес записанный в верхушке стэка.",
	{
		{"[PC].low",	"=","M[SP]"},
		{"[PC].high",	"=","M[SP + 1]" },
		{"[SP]",		"=","[SP] + 2"},
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RZ------------------------------------------
	{ "rz",{
	{},
	{},
	u8"Если флаг Zero = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RC------------------------------------------
	{ "rc",{
	{},
	{},
	u8"Если флаг Carry = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RPE------------------------------------------
	{ "rpe",{
	{},
	{},
	u8"Если флаг Paruty = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RM------------------------------------------
	{ "rm",{
	{},
	{},
	u8"Если флаг Sign = 1, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RNZ------------------------------------------
	{ "rnz",{
	{},
	{},
	u8"Если флаг Zero = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RNC------------------------------------------
	{ "rnc",{
	{},
	{},
	u8"Если флаг Carry = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// RPO------------------------------------------
	{ "rpo",{
	{},
	{},
	u8"Если флаг Paruty = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},
	// RP------------------------------------------
	{ "rp",{
	{},
	{},
	u8"Если флаг Sign = 0, то Прыжок на адрес записанный в верхушке стэка и уменьшение стэка на два, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC].low",	"=","M[SP]"},
			{"[PC].high",	"=","M[SP + 1]" },
			{"[SP]",		"=","[SP] + 2"},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 1"}
	},
	{11,5},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RETURN}}
	},

	// JMP------------------------------------------
	{ "jmp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Прыжок PC по адресу заданной константы",
	{
		{"[PC]", "=", ENUM_Arguments::Value16}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},

	// JZ------------------------------------------
	{ "jz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Zero = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},

	// JC------------------------------------------
	{ "jc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Carry = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},

	// JPE------------------------------------------
	{ "jpe",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Paruty = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},

	// JM------------------------------------------
	{ "jm",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Sign = 1, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "jnz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Zero = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "jnc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Carry = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "jpo",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Paruty = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "jp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг  Sign = 0, то Прыжок PC по адресу заданной константы, иначе пропуск команды",
	{
		{ENUM_Branching::IF},
			{"[PC]",	"=", ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",	"=", "[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "call",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{"[SP]",		"=","[SP] - 2"},
		{"M[SP]",		"=","([PC] + 3).low"},
		{"M[SP + 1]",	"=","([PC] + 3).high"},
		{"[PC]",		"=",ENUM_Arguments::Value16}
	},
	{17},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Zero = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Carry = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cpe",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Paruty = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cm",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Sign = 1, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cnz",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Zero = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cnc",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Carry = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cpo",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Paruty = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "cp",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Если флаг Sign = 0, то Сохранение следующего адреса команды в стек и прыжок PC на адрес указанный константой",
	{
		{ENUM_Branching::IF},
			{"[SP]",		"=","[SP] - 2"},
			{"M[SP]",		"=","(PC + 3).low"},
			{"M[SP + 1]",	"=","(PC + 3).high"},
			{"[PC]",		"=",ENUM_Arguments::Value16},
		{ENUM_Branching::ELSE},
			{"[PC]",		"=","[PC] + 3"}
	},
	{17,11},
	ENUM_TicksMean::Condition,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::CALL}}
	},


	{ "push",{
	{ENUM_Arguments::Register16_WithPSW},
	{},
	u8"Сохранение двухбайтового числа из пары регистров в верхушку стэка",
	{
		{"[SP]",			"=","[SP] - 2"},
		{"M[SP + 1]",		"=",ENUM_Arguments::Register16_WithPSW_high},
		{"M[SP]",			"=",ENUM_Arguments::Register16_WithPSW_low},
		{"[PC]",			"=","[PC] + 1"}
	},
	{11},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::STACK_OPS}}
	},


	{ "pop",{
	{ENUM_Arguments::Register16_WithPSW},
	{},
	u8"Извлечение из верхушки стэка двухбайтового числа в пару регистров",
	{
		{ENUM_Arguments::Register16_WithPSW_low,	"=", "M[SP]"},
		{ENUM_Arguments::Register16_WithPSW_high,	"=", "M[SP + 1]"},
		{"[SP]",									"=", "[SP] + 2"},
		{"[PC]",									"=", "[PC] + 1"}
},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::STACK_OPS}}
	},


	{ "shld",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Сохраняет двухбайтовое значение пары регистров HL по адресу памяти заданной константой",
	{
		{"M[",ENUM_Arguments::Value16,"]",		"=","[L]"},
		{"M[",ENUM_Arguments::Value16," + 1]",	"=","[H]"},
		{"[PC]",								"=","[PC] + 3"}
	},
	{16},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "lhld",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Загружает двухбайтовое значение по адресу памяти заданной константой в пару регистров HL",
	{
		{"[L]",		"=","M[",ENUM_Arguments::Value16 ,"]"},
		{"[H]",		"=","M[",ENUM_Arguments::Value16," + 1]"},
		{"[PC]",	"=","[PC] + 3" }
	},
	{16},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "stax",{
	{ENUM_Arguments::Register16_OnlyBD},
	{},
	u8"Сохраняет значение аккумулятора в память по адресу пары регистров",
	{
		{"M[",ENUM_Arguments::Register16_OnlyBD,"]","=","[A]"},
		{"[PC]",									"=","[PC] + 1"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "ldax",{
	{ENUM_Arguments::Register16_OnlyBD},
	{},
	u8"Загружает число по адресу пары регистров в аккумулятор",
	{
		{"[A]",		"=","M[",ENUM_Arguments::Register16_OnlyBD,"]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "sta",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Сохраняет значение из аккумулятор по адресу памяти заданной константой",
	{
		{"M[",ENUM_Arguments::Value16,"]",	"=","[A]"},
		{"[PC]",							"=","[PC] + 3"}
	},
	{13},
	ENUM_TicksMean::Always,
	FlagsList{
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected,
			ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "lda",{
	{ENUM_Arguments::Value16},
	{ENUM_Bytes::Adress_low,ENUM_Bytes::Adress_high},
	u8"Загружает значение из памяти по адресу заданной константой в аккумулятор",
	{
		{"[A]",		"=","M[",ENUM_Arguments::Value16,"]"},
		{"[PC]",	"=","[PC] + 3"}
	},
	{13},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},


	{ "lxi",{
	{ENUM_Arguments::Register16_WithSP,ENUM_Arguments::Value16},
	{ENUM_Bytes::Value_low,ENUM_Bytes::Value_high},
	u8"Записывает двухбайтовую константу в пару регистров",
	{
		{ENUM_Arguments::Register16_WithSP_low,	"=",ENUM_Arguments::Value16_low},
		{ENUM_Arguments::Register16_WithSP_high,"=",ENUM_Arguments::Value16_high},
		{"[PC]",								"=","[PC] + 3"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE, ENUM_Category::STACK_OPS}}
	},


	{ "xchg",{
	{},
	{},
	u8"Меняет местами значения двухбайтовых чисел пар регистров DE и HL",
	{
		{"swap([DE], [HL])"},
		{"[PC] = [PC] + 1"}
	},
	{4},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::MOVE_LOAD_STORE}}
	},



	{ "xthl",{
	{},
	{},
	u8"Меняет местами значение памяти по адресу SP c значением регистра L, и также с адресом памяти (SP + 1) и регистром H. Память поменяется, а значение SP не поменяется",
	{
		{"swap([H], Memory[SP + 1])"},
		{"swap([L], Memory[SP])"},
		{"[PC] = [PC] + 1"}
	},
	{18},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::STACK_OPS}}
	},


	{ "pchl",{
	{},
	{},
	u8"Загружает значение числа из пар регистров HL в адрес текущей позиции процессора PC",
	{
		{"[PC] = [HL]"}
	},
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::JUMP}}
	},


	{ "sphl",{
	{},
	{},
	u8"Загружает значение двух байтвого числа пары регистров HL в стэк SP. При этом SP увеличится на два",
	{
		{"[SP]",	"=","[HL]"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::STACK_OPS}}
	},


	{ "dad",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"Прибавляние к числу из пары регистров HL, числа из указанной пары регистров",
	{
		{"Temp",		"=","[HL] + ",ENUM_Arguments::Register16_WithSP},
		{"[Carry]",		"=","(Temp > 0xffff)"},
		{"[HL]",		"=","Temp" },
		{"[PC]",		"=","[PC] + 1"}
	},
	{10},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ADD}}
	},


	{ "inx",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"Увелечение на единицу числа записанного в паре регистров",
	{
		{ENUM_Arguments::Register16_WithSP,	"=",ENUM_Arguments::Register16_WithSP," + 1"},
		{"[PC]",							"=","[PC] + 1"}
	},
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::INCREMENT,ENUM_Category::STACK_OPS}}
	},


	{ "inr",{
	{ENUM_Arguments::Register8},
	{},
	u8"Увелечение регистра или памяти на единицу",
	{
		{ENUM_Arguments::Register8,	"=",ENUM_Arguments::Register8," + 1"},
		{"[Zero]",					"=","(",ENUM_Arguments::Register8," == 0)"},
		{"[PC]",					"=","[PC] + 1"}
	},
	{10,5},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::INCREMENT}}
	},


	{ "dcx",{
	{ENUM_Arguments::Register16_WithSP},
	{},
	u8"Уменьшение на единицу числа записанного в паре регистров",
	{
		{ENUM_Arguments::Register16_WithSP,	"=",ENUM_Arguments::Register16_WithSP," - 1"},
		{"[PC]",							"=","[PC] + 1" }
	},
	{5},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ ENUM_Category::DECREMENT, ENUM_Category::STACK_OPS}}
	},


	{ "dcr",{
	{ENUM_Arguments::Register8},
	{},
	u8"Уменьшение регистра или памяти на единицу",
	{
		{ENUM_Arguments::Register8,	"=",ENUM_Arguments::Register8," - 1"},
		{"[Zero]",					"=","(",ENUM_Arguments::Register8," == 0)"},
		{"[PC]",					"=","[PC] + 1"}
	},
	{10,5},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::DECREMENT}}
	},


	{ "add",{
	{ENUM_Arguments::Register8},
	{},
	u8"Арифмитическое сложение значения аккумулятора и регистра или памяти(по адресу HL)",
	{
		{"Temp",	"=","[A] + ",ENUM_Arguments::Register8},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)" },
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::ADD}}
	},


	{ "adc",{
	{ENUM_Arguments::Register8},
	{},
	u8"Арифмитическое сложение значения аккумулятора и (регистра или памяти(по адресу HL)) с флагом Carry",
	{
		{"Temp",	"=","[A] + ",ENUM_Arguments::Register8," + [Carry]"},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ADD}}
	},


	{ "adi",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Арифмитическое сложение значения аккумулятора с константой",
	{
		{"Temp",	"=","[A] + ",ENUM_Arguments::Value8},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
	{ENUM_Category::ADD}}
	},


	{ "aci",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Арифмитическое сложение значения аккумулятора с константой и флагом Carry",
	{
		{"Temp",	"=","[A] + ",ENUM_Arguments::Value8," + [Carry]"},
		{"[A]",		"=","Temp"},
		{"[Carry]",	"=","(Temp > 0xff)"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::ADD}}
	},


	{ "sub",{
	{ENUM_Arguments::Register8},
	{},
	u8"Арифмитическое вычитание из значения аккумулятора значение памяти(по адресу HL) или регистра",
	{
		{"[Carry]",	"=","([A] < ",ENUM_Arguments::Register8,")"},
		{"[A]",		"=","[A] - ",ENUM_Arguments::Register8},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1"}
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::SUBTRACT}}
	},


	{ "sbb",{
	{ENUM_Arguments::Register8},
	{},
	u8"Арифмитическое вычитание из значения аккумулятора значение (памяти(по адресу HL) или регистра) с флагом Carry",
	{
		{"[Carry]",	"=","([A] < ",ENUM_Arguments::Register8," + [Carry])"},
		{"[A]",		"=","[A] - ",ENUM_Arguments::Register8," - [Carry]"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 1" }
	},
	{7,4},
	ENUM_TicksMean::M_Used,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::SUBTRACT}}
	},


	{ "sui",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Арифмитическое вычитание из значения аккумулятора константы",
	{
		{"[Carry]",	"=","([A] < ",ENUM_Arguments::Value8,")"},
		{"[A]",		"=","[A] - ",ENUM_Arguments::Value8},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","[PC] + 2"}
	},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::SUBTRACT}}
	},


	{ "sbi",{
	{ENUM_Arguments::Value8},
	{ENUM_Bytes::Value},
	u8"Арифмитическое вычитание из значения аккумулятора константы и флага Carry",
	{
		{"[Carry]",	"=","([A] < ",ENUM_Arguments::Value8," + [Carry])"},
		{"[A]",		"=","([A] - ",ENUM_Arguments::Value8," - [Carry])"},
		{"[Zero]",	"=","([A] == 0)"},
		{"[PC]",	"=","([PC] + 2)"}
},
	{7},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected,
		ENUM_FlagsState::Affected},
		{ENUM_Category::SUBTRACT}}
	},


	{ "rst",{
	{ENUM_Arguments::ValueSpecial},
	{ENUM_Bytes::Value},
	u8"Call [Число * 8]",
	{
		{"[SP]",			"=","[SP] - 2"},
		{"M[SP]",			"=","([PC] + 3).low"},
		{"M[SP + 1]",		"=","([PC] + 3).high"},
		{"[PC]",			"=","(",ENUM_Arguments::ValueSpecial," * 8)"}
	},
	{11},
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
		{ENUM_Category::RESTART}}
	 },



	 { "daa",{
	 {},
	 {},
	 u8"Корректирует содержимое регистра A для соответствия формату BCD",
	 {
		 {u8"Не знаю как это описать."}
	 },
	 {4},
	 ENUM_TicksMean::Always,
	 FlagsList{
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected,
		 ENUM_FlagsState::Affected },
	{ENUM_Category::SPECIALS}}

	},

	{ "ei",{
	{},
	{},
	u8"Включает прерывание",
	{
		{u8"Эта инструкция не реализована."}
	},
	{ 4 },
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected},
	{ENUM_Category::CONTROL}}
	},


	{ "di",{
	{},
	{},
	u8"Отключает прерывание",
	{
		{u8"Эта инструкция не реализована."}
	},
	{ 4 },
	ENUM_TicksMean::Always,
	FlagsList{
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected,
		ENUM_FlagsState::Unaffected },
	{ENUM_Category::CONTROL}}
	}

};

