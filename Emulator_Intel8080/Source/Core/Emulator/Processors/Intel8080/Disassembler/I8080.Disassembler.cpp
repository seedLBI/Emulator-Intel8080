#include "I8080.Disassembler.h"

std::pair<std::vector<std::string>, int> Instructuion_to_String(const uint8_t& opcode, const uint8_t& firstByte, const uint8_t& secondByte) {


	std::vector < std::vector<std::string>> translate = {
		{"NOP"},      {"LXI  B, ", "16"},{"STAX  B"},   {"INX  B" },  {"INR  B"},   {"DCR  B"},   {"MVI  B, ","8"},{"RLC"},      {"*NOP"},     {"DAD  B"},   {"LDAX  B"},   {"DCX  B"},     {"INR  C"},   {"DCR  C"},     {"MVI  C, ","8"},{"RRC"},
		{"*NOP"},     {"LXI  D, ","16"}, {"STAX  D"},   {"INX  D"},   {"INR  D"},   {"DCR  D"},   {"MVI  D, ","8"},{"RAL"},      {"*NOP"},     {"DAD  D"},   {"LDAX  D"},   {"DCX  D"},     {"INR  E"},   {"DCR  E"},     {"MVI  E, ","8"},{"RAR"},
		{"*NOP"},     {"LXI  H, ","16"}, {"SHLD ","16"},{"INX  H"},   {"INR  H"},   {"DCR  H"},   {"MVI  H, ","8"},{"DAA"},      {"*NOP"},     {"DAD  H"},   {"LHLD ","16"},{"DCX  H"},     {"INR  L"},   {"DCR  L"},     {"MVI  L, ","8"},{"CMA"},
		{"*NOP"},     {"LXI  SP, ","16"},{"STA ","16"}, {"INX  SP"},  {"INR  M"},   {"DCR  M"},   {"MVI  M, ","8"},{"STC"},      {"*NOP"},     {"DAD  SP"},  {"LDA ","16"}, {"DCX  SP"},    {"INR  A"},   {"DCR  A"},     {"MVI  A, ","8"},{"CMC"},
		{"MOV  B, B"},{"MOV  B, C"},     {"MOV  B, D"}, {"MOV  B, E"},{"MOV  B, H"},{"MOV  B, L"},{"MOV  B, M"},   {"MOV  B, A"},{"MOV  C, B"},{"MOV  C, C"},{"MOV  C, D"}, {"MOV  C, E"},  {"MOV  C, H"},{"MOV  C, L"},  {"MOV  C, M"},   {"MOV  C, A"},
		{"MOV  D, B"},{"MOV  D, C"},     {"MOV  D, D"}, {"MOV  D, E"},{"MOV  D, H"},{"MOV  D, L"},{"MOV  D, M"},   {"MOV  D, A"},{"MOV  E, B"},{"MOV  E, C"},{"MOV  E, D"}, {"MOV  E, E"},  {"MOV  E, H"},{"MOV  E, L"},  {"MOV  E, M"},   {"MOV  E, A"},
		{"MOV  H, B"},{"MOV  H, C"},     {"MOV  H, D"}, {"MOV  H, E"},{"MOV  H, H"},{"MOV  H, L"},{"MOV  H, M"},   {"MOV  H, A"},{"MOV  L, B"},{"MOV  L, C"},{"MOV  L, D"}, {"MOV  L, E"},  {"MOV  L, H"},{"MOV  L, L"},  {"MOV  L, M"},   {"MOV  L, A"},
		{"MOV  M, B"},{"MOV  M, C"},     {"MOV  M, D"}, {"MOV  M, E"},{"MOV  M, H"},{"MOV  M, L"},{"HLT"},         {"MOV  M, A"},{"MOV  A, B"},{"MOV  A, C"},{"MOV  A, D"}, {"MOV  A, E"},  {"MOV  A, H"},{"MOV  A, L"},  {"MOV  A, M"},   {"MOV  A, A"},
		{"ADD  B"},   {"ADD  C"},        {"ADD  D"},    {"ADD  E"},   {"ADD  H"},   {"ADD  L"},   {"ADD  M"},      {"ADD  A"},   {"ADC  B"},   {"ADC  C"},   {"ADC D"},     {"ADC  E"},     {"ADC  H"},   {"ADC  L"},     {"ADC  M"},      {"ADC  A"},
		{"SUB  B"},   {"SUB  C"},        {"SUB  D"},    {"SUB  E"},   {"SUB  H"},   {"SUB  L"},   {"SUB  M"},      {"SUB  A"},   {"SBB  B"},   {"SBB  C"},   {"SBB D"},     {"SBB  E"},     {"SBB  H"},   {"SBB  L"},     {"SBB  M"},      {"SBB  A"},
		{"ANA  B"},   {"ANA  C"},        {"ANA  D"},    {"ANA  E"},   {"ANA  H"},   {"ANA  L"},   {"ANA  M"},      {"ANA  A"},   {"XRA  B"},   {"XRA  C"},   {"XRA D"},     {"XRA  E"},     {"XRA  H"},   {"XRA  L"},     {"XRA  M"},      {"XRA  A"},
		{"ORA  B"},   {"ORA  C"},        {"ORA  D"},    {"ORA  E"},   {"ORA  H"},   {"ORA  L"},   {"ORA  M"},      {"ORA  A"},   {"CMP  B"},   {"CMP  C"},   {"CMP D"},     {"CMP  E"},     {"CMP  H"},   {"CMP  L"},     {"CMP  M"},      {"CMP  A"},
		{"RNZ"},      {"POP  B"},        {"JNZ ","16"}, {"JMP ","16"},{"CNZ ","16"},{"PUSH B"},   {"ADI ","8"},    {"RST  0"},   {"RZ"},       {"RET"},      {"JZ ","16"},  {"*JMP ", "16"},{"CZ ","16"}, {"CALL ","16"}, {"ACI ","8"},    {"RST  1"},
		{"RNC"},      {"POP  D"},        {"JNC ","16"}, {"OUT ","8"}, {"CNC ","16"},{"PUSH D"},   {"SUI ","8"},    {"RST  2"},   {"RC"},       {"*RET"},     {"JC ","16"},  {"IN ","8"},    {"CC ","16"}, {"*CALL", "16"},{"SBI ","8"},    {"RST  3"},
		{"RPO"},      {"POP  H"},        {"JPO ","16"}, {"XTHL"},     {"CPO ","16"},{"PUSH H"},   {"ANI ","8"},    {"RST  4"},   {"RPE"},      {"PCHL"},     {"JPE ","16"}, {"XCHG"},       {"CPE ","16"},{"*CALL", "16"},{"XRI ","8"},    {"RST  5"},
		{"RP"},       {"POP  PSW"},      {"JP ","16"},  {"DI"},       {"CP ","16"}, {"PUSH PSW"}, {"ORI ","8"},    {"RST  6"},   {"RM"},       {"SPHL"},     {"JM ","16"},  {"EI"},         {"CM ","16"}, {"*CALL", "16"},{"CPI ","8"},    {"RST  7"}
	};

	std::string result = translate[opcode][0];
	if (result.size() < 5) {
		result.append(5 - result.size(), ' ');
	}


	if (translate[opcode].size() == 2){
		if (translate[opcode][1] == "8")
			return { {result, "0x" + to_hex_string(firstByte)},2};
		else if (translate[opcode][1] == "16")
			return { {result , "0x" + to_hex_string(secondByte) + to_hex_string(firstByte)},3};
	}
	

	return { {result},1 };
}