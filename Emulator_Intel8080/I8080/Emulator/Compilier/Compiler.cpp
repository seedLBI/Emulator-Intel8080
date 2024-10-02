#include "Emulator/Compilier/Compiler.h"


Compiler::Compiler() = default;
Compiler::~Compiler() = default;
TranslatorOutput Compiler::Compile(const std::vector<std::string>& Code) { return TranslatorOutput{}; }
void Compiler::Clear() {};



//TODO: Доделать логику для разбиение строк на символы
std::vector<std::string> Compiler::split_line(const std::string& line){
    std::vector<std::string> result;

    const static std::string DoubleQuote = "\"";
    const static std::string CommentSymbol = ";";

    bool InQuote = false;

    UTF8_SPLITER_ERROR splitter_error = UTF8_SPLITER_ERROR::NOTHING;
    auto splitted_line = utf8_splitter(line, splitter_error);

    if (splitter_error != UTF8_SPLITER_ERROR::NOTHING) {
        CompilerOutput.Error = ERROR_UNSUPPORTED_SYMBOL;
        return result;
    }

    std::string temp = "";
    for (int i = 0; i < splitted_line.size(); i++) {

        const std::string symbol = splitted_line[i];

        if (symbol == CommentSymbol) {
            break;
        }

        if (symbol == DoubleQuote) {
            InQuote = true;
            i++;

            bool LastWasSlash = false;


            while (InQuote) {
                if (i > line.size() - 1)
                    break;

                if (splitted_line[i] == DoubleQuote) {
                    if (LastWasSlash) {
                        auto t = convert_utf8_toUTF8cp1251(splitted_line[i]);
                        if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL) {
                            CompilerOutput.Error = ERROR_UNSUPPORTED_SYMBOL;
                            return result;
                        }
                        i++;
                        continue;
                    }
                    else {
                        InQuote = false;
                        break;
                    }
                }
                else if (splitted_line[i] == "\\") {

                    if (LastWasSlash == false) {
                        LastWasSlash = true;
                    }
                    else {
                        auto t = convert_utf8_toUTF8cp1251(splitted_line[i]);
                        if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL){
                            CompilerOutput.Error = ERROR_UNSUPPORTED_SYMBOL;
                            return result;
                        }
                        result.push_back(std::to_string(t.first));
                        i++;
                        continue;
                    }
                }
                else {
                    auto t = convert_utf8_toUTF8cp1251(splitted_line[i]);
                    if (t.second == UTF8_to_CP1251_CONVERTER_ERROR::UNSUPPORTED_SYMBOL) {
                        CompilerOutput.Error = ERROR_UNSUPPORTED_SYMBOL;
                        return result;
                    }
                    result.push_back(std::to_string(t.first));
                }

                LastWasSlash = false;


                i++;
            }

            if (InQuote){
                CompilerOutput.Error = ERROR_WHERE_SECOND_DOUBLE_QUOTE;
                return result;
            }

            continue;
        }

        if (symbol == ":") {
            temp += symbol;
            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (symbol == " " || symbol == "\t") {
            if (temp.size() == 0)
                continue;
            else if (temp.size() == 1 && temp[0] == '.')
                continue;
            if (symbol.size() > i && splitted_line[i + 1] == ":")
                continue;



            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (symbol == ",") {
            if (temp.size() == 0)
                continue;
            result.emplace_back(temp);
            temp = "";
            continue;
        }

        temp += symbol;
    }

	if (temp.size() != 0)
		result.emplace_back(temp);


    return result;
}


std::vector<std::vector<std::string>> Compiler::split_code(const std::vector<std::string>& code) {
    std::vector<std::vector<std::string>> result(code.size());

    for (int i = 0; i < code.size(); ++i) {
        result[i] = split_line(code[i]);
        if (CompilerOutput.Error != TypeTranslatorError::NOTHING) {
            CompilerOutput.LineError = i;
            return result;
        }
    }

    return result;
}


bool Compiler::IsAllSpecialSymbols(const string& command) {

    static const robin_hood::unordered_flat_set<char> special_symbols = { '.', ',', ':', '[', ']', '>', '<', '\\', '/', '|','\'','\"'};

    int count = 0;
    for (char c : command) {
        if (special_symbols.contains(c))
            count++;
    }


    return command.size() == count;

}

std::pair<uint64_t, Compiler::TypeValue> Compiler::FromString2Int(const string& value) {
    if (IsHexValue(value))
        return { StrHex2int(value), Compiler::TypeValue::HEX };
    else if (IsDecValue(value))
        return { StrDec2int(value), Compiler::TypeValue::DEC };
    else if (IsBinValue(value))
        return { StrBin2int(value), Compiler::TypeValue::BIN };

    return { uint64_t(0),  Compiler::TypeValue::UNKNOWN };
}



bool Compiler::CheckName(const string& name) {

    robin_hood::unordered_node_set<std::string> Denied_names = { "a","A","b","B","c","C","d","D","e","E","H","h","l","L","sp","SP" };

    if (Denied_names.contains(name) == true)
        return false;

    //vector<string> Denied_names = { "a","A","b","B","c","C","d","D","e","E","H","h","l","L","sp","SP" };
    //if (FindInVector(Denied_names, name))
    //    return false;

    if (name[0] >= '0' && name[0] <= '9')
        return false;

    for (int i = 0; i < name.size(); ++i) {
        bool is_low_latter = (name[i] >= 'a' && name[i] <= 'z');
        bool is_upper_letter = (name[i] >= 'A' && name[i] <= 'Z');
        bool is_down_slash = (name[i] == '_');
        bool is_value = (name[i] >= '0' && name[i] <= '9');

        if (is_low_latter == false && is_upper_letter == false && is_down_slash == false && is_value == false) {
            return false;
        }
    }

    return true;
}


int Compiler::GetCountBytes(const string& cmd) {

    static const robin_hood::unordered_flat_map<std::string, int> cmdBytes = {
        {"mov",1},{"hlt",1},{"xra",1},{"cmp",1},
        {"add",1},{"inr",1},{"dcr",1},{"inx",1},
        {"ora",1},{"ana",1},{"sub",1},{"ret",1},
        {"rz",1},{"rc",1},{"rpe",1},{"rm",1},
        {"rnz",1},{"rnc",1},{"rpo",1},{"rp",1},
        {"rst",1},{"push",1},{"pchl",1},{"sphl",1},
        {"pop",1},{"stax",1},{"dad",1},{"ldax",1},
        {"xchg",1},{"ei",1},{"rrc",1},{"rar",1},
        {"cma",1},{"cmc",1},{"rlc",1},{"ral",1}, {"sbb",1},
        {"daa",1},{"stc",1},{"nop",1},{"dcx",1},{"di",1},{"xthl",1},

        {"out",2},{"in",2},{"mvi",2},{"adi",2},
        {"sui",2},{"ani",2},{"ori",2},{"aci",2},
        {"sbi",2},{"xri",2},{"cpi",2},

        {"lxi",3},{"shld",3},{"sta",3},{"lhld",3},
        {"lda",3},{"call",3},{"cz",3},{"cc",3},
        {"cpe",3},{"cm",3},{"jz",3},{"jc",3},
        {"jpe",3},{"jm",3},{"cnz",3},{"cnc",3},
        {"cpo",3},{"cp",3},{"jnz",3},{"jnc",3},
        {"jpo",3},{"jp",3},{"jmp",3},
    };


    auto it = cmdBytes.find(cmd);
    if (it != cmdBytes.end())
        return it->second;

    return 0;
}
int Compiler::GetCountParams(const string& cmd) {

    static const robin_hood::unordered_flat_map<std::string, int> cmdParams = {
        {"aci",1},{"adc",1},{"add",1},{"adi",1},{"ana",1},{"ani",1},
        {"call",1},{"cc",1},{"cm",1},{"cma",0},{"cmc",0},{"cmp",1},
        {"cnc",1},{"cnz",1},{"cp",1},{"cpe",1},{"cpi",1},{"cpo",1},
        {"cz",1},{"daa",0},{"dad",1},{"dcr",1},{"dcx",1},{"di",0},
        {"ei",0},{"hlt",0},{"in",1},{"inr",1},{"inx",1},{"jc",1},
        {"jm",1},{"jmp",1},{"jnc",1},{"jnz",1},{"jp",1},{"jpe",1},
        {"jpo",1},{"jz",1},{"lda",1},{"ldax",1},{"lhld",1},{"lxi",2},
        {"mov",2},{"mvi",2},{"nop",0},{"ora",1},{"ori",1},{"out",1},
        {"pchl",0},{"pop",1},{"push",1},{"ral",0},{"rar",0},{"rc",0},
        {"ret",0},{"rlc",0},{"rm",0},{"rnc",0},{"rnz",0},{"rp",0},
        {"rpe",0},{"rpo",0},{"rrc",0},{"rst",1},{"rz",0},{"sbb",1},
        {"sbi",1},{"shld",1},{"sphl",0},{"sta",1},{"stax",1},{"stc",0},
        {"sub",1},{"sui",1},{"xchg",0},{"xra",1},{"xri",1},{"xthl",0}
    };

    auto it = cmdParams.find(cmd);
    if (it != cmdParams.end())
        return it->second;

    return -1;

}

vector<uint8_t> Compiler::TranslateInstruction(const vector<string>& splitted_command) {
	enum TypeInstruction {
		imm8,
		imm16,
		mov, mvi,
		pop, push,
		arithmetic,
		inr, dcr, inx, dcx, dad, lxi,
		stax, ldax,
		none_param,
		rst,
	};


	const static robin_hood::unordered_flat_map<string, TypeInstruction> GetTypeInstruction = {
			{"call",imm16}, {"jmp",imm16},{"cnz",imm16},  {"jnz",imm16},
			{"cnc",imm16},  {"jnc",imm16},{"cpo",imm16},  {"jpo",imm16},
			{"cp",imm16},   {"jp",imm16},{"cz",imm16},   {"jz",imm16},
			{"cc",imm16},   {"jc",imm16},{"cpe",imm16},  {"jpe",imm16},
			{"cm",imm16},   {"jm",imm16},{"shld",imm16},{"sta",imm16},
			{"lhld",imm16},{"lda",imm16},{"mov",mov},{"mvi",mvi},
			{"rst",rst},{"inr",inr},{"dcr",dcr},{"inx",inx},{"dcx",dcx},{"dad",dad},
			{"ldax",ldax},{"stax",stax},{"pop",pop},{"push",push},{"lxi",lxi},
			{"add",arithmetic},{"sub",arithmetic},{"ana",arithmetic},{"ora",arithmetic},
			{"adc",arithmetic},{"sbb",arithmetic},{"xra",arithmetic},{"cmp",arithmetic},
			{"nop",none_param},{"hlt",none_param},{"rlc",none_param},{"ral",none_param},
			{"stc",none_param},{"rrc",none_param},{"rar",none_param},{"cma",none_param},
			{"cmc",none_param},{"rnz",none_param},{"rnc",none_param},{"rpo",none_param},
			{"rp",none_param},{"rz",none_param},{"rc",none_param},{"rpe",none_param},
			{"rm",none_param},{"ret",none_param},{"xthl",none_param},{"pchl",none_param},
			{"sphl",none_param},{"xchg",none_param},
	};
	vector<uint8_t> result;


	string command = splitted_command[0];
	ToLowerAll(command);

	int count_params = GetCountParams(command);

	vector<string> params;
	for (int i = 1; i < splitted_command.size(); i++) {
		string text_param = splitted_command[i];
		ToLowerAll(text_param);
		params.push_back(text_param);
	}

	if (count_params != params.size()) {
		CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
		return result;
	}

	TypeInstruction type_instruction;

	auto it = GetTypeInstruction.find(command);
	if (it == GetTypeInstruction.end())
		type_instruction = imm8;
	else
		type_instruction = it->second;

	static const robin_hood::unordered_flat_set<string> mov_mvi_inr_dcr_arithm_access_registers = { "a","b","c","d","e","l","h","m" };
	static const robin_hood::unordered_flat_set<string> inx_dcx_dad_lxi_access_registers = { "b","d","h","sp" };
	static const robin_hood::unordered_flat_set<string> pop_push_access_registers = { "b","d","h","psw" };



	static const robin_hood::unordered_flat_map<string, uint8_t> instruction_imm8_map = {
	{"adi",0xc6},{"aci",0xce},{"sui",0xd6},{"sbi",0xde},
	{"ani",0xe6},{"xri",0xee},{"ori",0xf6},{"cpi",0xfe},{"in",0xdb},{"out",0xd3},
	};

	static const robin_hood::unordered_flat_map<string, uint8_t> mov_a_map = { {"a",0x7f},{"b",0x78},{"c",0x79},{"d",0x7a},{"e",0x7b},{"h",0x7c},{"l",0x7d},{"m",0x7e} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_b_map = { {"a",0x47},{"b",0x40},{"c",0x41},{"d",0x42},{"e",0x43},{"h",0x44},{"l",0x45},{"m",0x46} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_c_map = { {"a",0x4f},{"b",0x48},{"c",0x49},{"d",0x4a},{"e",0x4b},{"h",0x4c},{"l",0x4d},{"m",0x4e} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_d_map = { {"a",0x57},{"b",0x50},{"c",0x51},{"d",0x52},{"e",0x53},{"h",0x54},{"l",0x55},{"m",0x56} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_e_map = { {"a",0x5f},{"b",0x58},{"c",0x59},{"d",0x5a},{"e",0x5b},{"h",0x5c},{"l",0x5d},{"m",0x5e} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_l_map = { {"a",0x6f},{"b",0x68},{"c",0x69},{"d",0x6a},{"e",0x6b},{"h",0x6c},{"l",0x6d},{"m",0x6e} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_h_map = { {"a",0x67},{"b",0x60},{"c",0x61},{"d",0x62},{"e",0x63},{"h",0x64},{"l",0x65},{"m",0x66} };
	static const robin_hood::unordered_flat_map<string, uint8_t> mov_m_map = { {"a",0x77},{"b",0x70},{"c",0x71},{"d",0x72},{"e",0x73},{"h",0x74},{"l",0x75} };

	static const robin_hood::unordered_flat_map<string, robin_hood::unordered_flat_map<string, uint8_t>> all_mov_map = {
		{"a",mov_a_map}, {"b",mov_b_map}, {"c",mov_c_map}, {"d",mov_d_map}, {"e",mov_e_map}, {"l",mov_l_map}, {"h",mov_h_map}, {"m",mov_m_map}
	};

	static const robin_hood::unordered_flat_map<string, uint8_t> instruction_imm16_map = {
		{"call",0xcd}, {"jmp",0xc3},{"cnz",0xc4},  {"jnz",0xc2},
		{"cnc",0xd4},  {"jnc",0xd2},{"cpo",0xe4},  {"jpo",0xe2},
		{"cp",0xf4},   {"jp",0xf2},{"cz",0xcc},   {"jz",0xca},
		{"cc",0xdc},   {"jc",0xda},{"cpe",0xec},  {"jpe",0xea},
		{"cm",0xfc},   {"jm",0xfa},{"shld",0x22},{"sta",0x32},{"lhld",0x2a},{"lda",0x3a},
	};

	static const robin_hood::unordered_flat_map<string, uint8_t> mvi_imm8_map = {
	{"b",0x06},{"c",0x0e},{"d",0x16},{"e",0x1e},
	{"h",0x26},{"l",0x2e},{"m",0x36},{"a",0x3e}
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> pop_map = {
	{"b",  0xc1}, {"d",  0xd1}, {"h",  0xe1}, {"psw",0xf1},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> push_map = {
	{"b",  0xc5},{"d",  0xd5},{"h",  0xe5},{"psw",0xf5},
	};

	static const robin_hood::unordered_flat_map<string, uint8_t> add_map = { {"b",0x80},{"c",0x81},{"d",0x82},{"e",0x83},{"h",0x84},{"l",0x85},{"m",0x86},{"a",0x87} };
	static const robin_hood::unordered_flat_map<string, uint8_t> sub_map = { {"b",0x90},{"c",0x91},{"d",0x92},{"e",0x93},{"h",0x94},{"l",0x95},{"m",0x96},{"a",0x97} };
	static const robin_hood::unordered_flat_map<string, uint8_t> ana_map = { {"b",0xa0},{"c",0xa1},{"d",0xa2},{"e",0xa3},{"h",0xa4},{"l",0xa5},{"m",0xa6},{"a",0xa7} };
	static const robin_hood::unordered_flat_map<string, uint8_t> ora_map = { {"b",0xb0},{"c",0xb1},{"d",0xb2},{"e",0xb3},{"h",0xb4},{"l",0xb5},{"m",0xb6},{"a",0xb7} };
	static const robin_hood::unordered_flat_map<string, uint8_t> adc_map = { {"b",0x88},{"c",0x89},{"d",0x8a},{"e",0x8b},{"h",0x8c},{"l",0x8d},{"m",0x8e},{"a",0x8f} };
	static const robin_hood::unordered_flat_map<string, uint8_t> sbb_map = { {"b",0x98},{"c",0x99},{"d",0x9a},{"e",0x9b},{"h",0x9c},{"l",0x9d},{"m",0x9e},{"a",0x9f} };
	static const robin_hood::unordered_flat_map<string, uint8_t> xra_map = { {"b",0xa8},{"c",0xa9},{"d",0xaa},{"e",0xab},{"h",0xac},{"l",0xad},{"m",0xae},{"a",0xaf} };
	static const robin_hood::unordered_flat_map<string, uint8_t> cmp_map = { {"b",0xb8},{"c",0xb9},{"d",0xba},{"e",0xbb},{"h",0xbc},{"l",0xbd},{"m",0xbe},{"a",0xbf} };

	static const robin_hood::unordered_flat_map<string, robin_hood::unordered_flat_map<string, uint8_t>> arithm_instruction_registers_map = {
		{"add",add_map},{"sub",sub_map},{"ana",ana_map},{"ora",ora_map},{"adc",adc_map},{"sbb",sbb_map},{"xra",xra_map},{"cmp",cmp_map},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> inr_map = {
			{"b",0x04},{"c",0x0c},{"d",0x14},{"e",0x1c},
			{"h",0x24},{"l",0x2c},{"m",0x34},{"a",0x3c}
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> dcr_map = {
			{"b",0x05},{"c",0x0d},{"d",0x15},{"e",0x1d},
			{"h",0x25},{"l",0x2d},{"m",0x35},{"a",0x3d}
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> inx_map = {
			{"b", 0x03},{"d", 0x13},{"h", 0x23},{"sp",0x33},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> dcx_map = {
			{"b", 0x0b},{"d", 0x1b},{"h", 0x2b},{"sp",0x3b},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> dad_map = {
			{"b", 0x09},{"d", 0x19},{"h", 0x29},{"sp",0x39},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> lxi_imm16_map = {
			{"b", 0x01},{"d", 0x11},{"h", 0x21},{"sp",0x31},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> stax_map = {
			{"b", 0x02},{"d", 0x12},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> ldax_map = {
			{"b", 0x0a},{"d", 0x1a},
	};
	static const robin_hood::unordered_flat_map <string, uint8_t> none_param_instructions_map = {
			{"nop",0x00},{"hlt",0x76},{"rlc",0x07},{"ral",0x17},{"stc",0x37},{"rrc",0x0f},{"rar",0x1f},
			{"cma",0x2f},{"cmc",0x3f},{"rnz",0xc0},{"rnc",0xd0},{"rpo",0xe0},{"rp",0xf0},{"rz",0xc8},
			{"rc",0xd8},{"rpe",0xe8},{"rm",0xf8},{"ret",0xc9},{"xthl",0xe3},{"pchl",0xe9},{"sphl",0xf9},
			{"xchg",0xeb},
	};
	static const robin_hood::unordered_flat_map<string, uint8_t> rst_map = {
			{"0",0xc7},{"1",0xcf},{"2",0xd7},{"3",0xdf},
			{"4",0xe7},{"5",0xef},{"6",0xf7},{"7",0xff},
	};

	switch (type_instruction) {
	case imm8: {

		int value = FromString2Int(params[0]).first;

		result.emplace_back(instruction_imm8_map.find(command)->second);
		result.emplace_back(value);
		break;
	}
	case imm16: {

		int value = FromString2Int(params[0]).first;

		int l_imm16 = value % 256;
		int h_imm16 = value / 256;

		result.emplace_back(instruction_imm16_map.find(command)->second);
		result.emplace_back(h_imm16);
		result.emplace_back(l_imm16);

		break;
	}
	case mov: {
		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}
		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[1]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		if (params[0] == "m" && params[1] == "m") {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}



		result.emplace_back(all_mov_map.find(params[0])->second.find(params[1])->second);
		break;
	}
	case mvi: {

		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		int value = FromString2Int(params[1]).first;

		result.emplace_back(mvi_imm8_map.find(params[0])->second);
		result.emplace_back(value);

		break;
	}
	case pop: {
		if (pop_push_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(pop_map.find(params[0])->second);
		break;
	}
	case push: {
		if (pop_push_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}


		result.emplace_back(push_map.find(params[0])->second);
		break;
	}
	case arithmetic: {
		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		result.emplace_back(arithm_instruction_registers_map.find(command)->second.find(params[0])->second);
		break;
	}
	case inr: {
		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}


		result.emplace_back(inr_map.find(params[0])->second);

		break;
	}
	case dcr: {
		if (mov_mvi_inr_dcr_arithm_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		result.emplace_back(dcr_map.find(params[0])->second);

		break;
	}
	case inx: {
		if (inx_dcx_dad_lxi_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(inx_map.find(params[0])->second);

		break;
	}
	case dcx: {
		if (inx_dcx_dad_lxi_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(dcx_map.find(params[0])->second);
		break;
	}
	case dad: {
		if (inx_dcx_dad_lxi_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(dad_map.find(params[0])->second);
		break;
	}
	case lxi: {
		if (inx_dcx_dad_lxi_access_registers.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		int value = FromString2Int(params[1]).first;

		int l_imm16 = value % 256;
		int h_imm16 = value / 256;

		result.emplace_back(lxi_imm16_map.find(params[0])->second);
		result.emplace_back(h_imm16);
		result.emplace_back(l_imm16);

		break;
	}
	case stax: {
		const static robin_hood::unordered_flat_set<string> access_register =
		{ "b","d" };
		if (access_register.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(stax_map.find(params[0])->second);
		break;
	}
	case ldax: {
		const static robin_hood::unordered_flat_set<string> access_register =
		{ "b","d" };
		if (access_register.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(ldax_map.find(params[0])->second);
		break;
	}
	case none_param: {
		result.emplace_back(none_param_instructions_map.find(command)->second);
		break;
	}
	case rst: {
		const static robin_hood::unordered_flat_set<string> access_values =
		{ "0","1","2","3","4","5","6","7","8","9" };

		if (access_values.contains(params[0]) == false) {
			CompilerOutput.Error = TypeTranslatorError::ERROR_INCORECT_VALUE;
			return result;
		}

		result.emplace_back(rst_map.find(params[0])->second);
		break;
	}
	default:
		break;
	}

	return result;

}


bool Compiler::IsHexValue(const  string& value) {
    if (value.size() <= 2)
        return false;

    //ToLowerAll(value);

    if (value[0] != '0' || (value[1] != 'x' && value[1] != 'X'))
        return false;


    // it's hex begin
    for (int i = 2; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 57);
        bool is_letter = (current_symbol >= 97 && current_symbol <= 102) || (current_symbol >= 65 && current_symbol <= 70);

        if (is_number || is_letter) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;
}
bool Compiler::IsDecValue(const  string& value) {
    if (value.size() > 1) {
        if (value[0] == '0')
        {
            return false;
        }
    }
    for (int i = 0; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 57);
        if (is_number == false) {
            return false;
        }
    }
    return true;
}
bool Compiler::IsBinValue(const  string& value) {
    if (value.size() <= 2)
        return false;

    //ToLowerAll(value);

    if (value[0] != '0' || (value[1] != 'b' && value[1] != 'B'))
        return false;

    // it's bin begin
    for (int i = 2; i < value.size(); ++i) {
        char current_symbol = value[i];

        bool is_number = (current_symbol >= 48 && current_symbol <= 49);

        if (is_number == false) {
            return false;
        }
    }

    return true;

}

uint64_t Compiler::StrHex2int(const  std::string& value) {
    return std::stoull(value.substr(2), nullptr, 16);
}
uint64_t Compiler::StrDec2int(const  std::string& value) {
    return std::stoull(value, nullptr, 10);
}
uint64_t Compiler::StrBin2int(const  std::string& value) {
    return std::stoull(value.substr(2), nullptr, 2);
}


