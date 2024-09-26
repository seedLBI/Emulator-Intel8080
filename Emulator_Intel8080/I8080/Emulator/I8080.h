#define SIZE_MEMORY 65536

#include "Config_Compilier.h"
#include "Utils\TextUtils.h"

#ifndef I8080_H
#define I8080_H

#include "Port\I8080.Port.SymbolScreen.h"
#include "Port\I8080.Port.GeneratorRandomValues.h"
#include "Port\I8080.Port.Timer.h"
#include "Port\I8080.Port.PixelScreen.h"
#include "Port\I8080.Port.PixelScreenTwoBuffers.h"
#include "Port\I8080.Port.AsyncKeyboard.h"

#include "DataStructures\TypeTranslatorError.h"
#include "DataStructures\OpcodeAdressed.h"
#include "DataStructures\VarsDebug.h"
#include "DataStructures\TranslatorOutput.h"
#include "DataStructures\CurrentStateProcessor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <array>
#include <chrono>
#include <list>
#include "robin_hood.h"
#include <unordered_map>
#include <unordered_set>
using namespace std;





inline bool FindInVector(const vector<string>& arr,const string& toFind) {
    return std::find(arr.begin(), arr.end(), toFind) != arr.end();

    //for (string element : arr) {
    //    if (element == toFind)
    //        return true;
    //}
    //return false;
}


inline vector<string> tokenize(string line) {
    vector<string> result;

    EraseAllSymbolType(line, '\t');
    SaveUniqueSpacesWithoutQuotes(line);
    EraseSideSpaces(line);

    string temp = "";
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == ';')
            break;
        else if (line[i] == ':') {
            temp += line[i];
            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (line[i] == ' ') {
            if (temp.size() == 0)
                continue;
            else if (temp.size() == 1 && temp[0] == '.')
                continue;
            if (line.size() > i && line[i + 1] == ':')
                continue;



            result.emplace_back(temp);
            temp = "";
            continue;
        }
        else if (line[i] == ',') {
            if (temp.size() == 0)
                continue;
            result.emplace_back(temp);
            temp = "";
            continue;
        }

        temp += line[i];
    }

    if (temp.size() != 0)
        result.emplace_back(temp);

    return result;
}

inline bool IsAllSpecialSymbols(const string& command) {
    vector<char> special_symbols = { '.',',',':','>','<','\\','/','|' };

    vector<int> flags(command.size(), 0);
    for (int i = 0; i < command.size(); i++) {
        for (int j = 0; j < special_symbols.size(); j++) {
            if (command[i] == special_symbols[j]) {
                flags[i] = 1;
            }
        }
    }

    bool all_command_its_special_symbols = false;

    bool all = true;
    for (int i = 0; i < flags.size(); ++i) {
        if (flags[i] == 0)
        {
            return false;
        }

    }


    return true;

}

inline bool IsHexValue(const string& value) {
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
inline bool IsDecValue(const string& value) {
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
inline bool IsBinValue(const string& value) {
    if (value.size() <= 2)
        return false;

    //ToLowerAll(value);

    if (value[0] != '0' || (value[1] != 'b' && value[1] != 'B') )
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

inline uint64_t StrHex2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 16);
}
inline uint64_t StrDec2int(const std::string& value) {
    return std::stoull(value);
}
inline uint64_t StrBin2int(const std::string& value) {
    return std::stoull(value.substr(2), nullptr, 2);
}

inline uint64_t FromString2Int(const string& value, TypeTranslatorError& ErrorType) {
    if (IsHexValue(value)) {
        //cout << "It's Hex value" << endl;
        return StrHex2int(value);
    }
    else if (IsDecValue(value)) {
        //cout << "It's Dec value" << endl;
        return StrDec2int(value);
    }
    else if (IsBinValue(value)) {
        //cout << "It's Bin value" << endl;
        return StrBin2int(value);
    }

    ErrorType = ERROR_INCORECT_VALUE;

    return uint64_t(0);
}


inline int GetCountBytes(const string& cmd) {

    static const robin_hood::unordered_node_map<std::string, int> cmdBytes = {
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
inline int GetCountParams(const string& cmd) {

    static const robin_hood::unordered_node_map<std::string, int> cmdParams = {
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

inline bool CheckName4ConstsAndAdresses(const string& name) {

    robin_hood::unordered_node_set<std::string> Denied_names = { "a","A","b","B","c","C","d","D","e","E","H","h","l","L","sp","SP" };

    if (Denied_names.find(name) != Denied_names.end())
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




enum class CompilierType {
    Stable,
    Experimental
};


class I8080
{
public:

	I8080() {
        Init_External_Peripherals();
		InitInstructions();
	}


	void InitPointer2State(CurrentState& cs);

	void LoadMemory(const vector<OpcodeAdressed>& array);
	void EraseMemory();
	void RemoveAllBreakPoints();

	void NextStep();
	void Reset();
	void ResetFlagStop();
	bool *IsStop();
    void ActiveFlagStop();

	bool IsWaitingPortInput();
	bool PC_on_BreakPoint();

    TranslatorOutput Translate(const vector<string>& array_of_lines);

	void InputAnswer2Port(const uint8_t& Answer);

	void SetProgrammCounter(const unsigned int& index);
	void SetBreakPointPosition(const unsigned int& Position);

	uint64_t GetCountTicks();
    uint64_t GetCountInstruction();

	unsigned int GetProgrammCounter();
	vector<unsigned int> GetOutputConsole();

	vector<I8080_Port*> Get_External_Peripherals();
    bool* GetBreakpointsInMemory();
    uint8_t* GetMemory();
	bool* GetVisetedMemory();
private:

    vector<uint8_t> str_instruction_2_array_bytes(const vector<string>& splitted_command, TypeTranslatorError& ErrorType);


	vector<I8080_Port*> External_Peripherals;

	vector<unsigned int> Output;




	bool Flag_Stop = false;
	bool Flag_Waiting_Input = false;
	bool Flag_GetAnswer = false;

	uint8_t Input = 0;

    uint8_t
		A = 0, // main registers
		B = 0,
		C = 0,
		D = 0,
		E = 0,
		H = 0,
		L = 0;

	uint16_t PC = 0, // programm counter
		     SP = 0; // index register

	bool Sign = false, // flags
		 Zero = false,
		 Paruty = false,
		 Carry = false,
		 AC = false;

    uint64_t CountTicks = 0;
    uint64_t CountInstruction = 0;



	uint8_t Memory[SIZE_MEMORY] = { 0, };
	bool Viseted_Memory[SIZE_MEMORY] = { 0, };
    bool BreakPoints[SIZE_MEMORY] = { 0, };

    inline void ALU(const uint8_t& opcode);

    inline void SetSP_nextAdress(const uint16_t& next_adress);
    inline void SetPC(const int& adress);
    inline void IncrementPC(const int& count = 1);

    inline void SetVisitedMemoryFromPC(const int& count);


    inline int GetAdressHL();

    inline void _SetFlagSign(const uint8_t& value);
    inline void _SetFlagParuty(const uint8_t& value);
    inline void _SetFlagZero(const uint8_t& value);

    void _INPUT();
    void _OUTPUT();
    inline void _MOV(uint8_t& valueTo, const uint8_t& valueFrom);
    inline void _MVI(uint8_t& valueTo);
    inline void _CALL();
    inline void _JMP();
    inline void _RET();
    inline void _ADD(const uint8_t& value);
    inline void _ADC(const uint8_t& value);
    inline void _DAD(const uint8_t& pair_element1, const uint8_t& pair_element2);
    inline void _INX(uint8_t& pair_element1, uint8_t& pair_element2);
    inline void _DCX(uint8_t& pair_element1, uint8_t& pair_element2);
    inline void _SUB(const uint8_t& value);
    inline void _SBB(const uint8_t& value);
    inline void _INCREMENT(uint8_t& value);
    inline void _DECREMENT(uint8_t& value);
    inline void _COMPARE(const uint8_t& value);
    inline void _ANA(const uint8_t& value);
    inline void _ORA(const uint8_t& value);
    inline void _XRA(const uint8_t& value);
    inline void _RST(const uint8_t& N);
    void _MVI_A_imm8(); void _MVI_B_imm8(); void _MVI_C_imm8(); void _MVI_D_imm8(); void _MVI_E_imm8(); void _MVI_H_imm8(); void _MVI_L_imm8(); void _MVI_M_imm8();
    void _MOV_A_A(); void _MOV_A_B(); void _MOV_A_C(); void _MOV_A_D(); void _MOV_A_E(); void _MOV_A_H(); void _MOV_A_L(); void _MOV_A_M();
    void _MOV_B_A(); void _MOV_B_B(); void _MOV_B_C(); void _MOV_B_D(); void _MOV_B_E(); void _MOV_B_H(); void _MOV_B_L(); void _MOV_B_M();
    void _MOV_C_A(); void _MOV_C_B(); void _MOV_C_C(); void _MOV_C_D(); void _MOV_C_E(); void _MOV_C_H(); void _MOV_C_L(); void _MOV_C_M();
    void _MOV_D_A(); void _MOV_D_B(); void _MOV_D_C(); void _MOV_D_D(); void _MOV_D_E(); void _MOV_D_H(); void _MOV_D_L(); void _MOV_D_M();
    void _MOV_E_A(); void _MOV_E_B(); void _MOV_E_C(); void _MOV_E_D(); void _MOV_E_E(); void _MOV_E_H(); void _MOV_E_L(); void _MOV_E_M();
    void _MOV_H_A(); void _MOV_H_B(); void _MOV_H_C(); void _MOV_H_D(); void _MOV_H_E(); void _MOV_H_H(); void _MOV_H_L(); void _MOV_H_M();
    void _MOV_L_A(); void _MOV_L_B(); void _MOV_L_C(); void _MOV_L_D(); void _MOV_L_E(); void _MOV_L_H(); void _MOV_L_L(); void _MOV_L_M();
    void _MOV_M_A(); void _MOV_M_B(); void _MOV_M_C(); void _MOV_M_D(); void _MOV_M_E(); void _MOV_M_H(); void _MOV_M_L();
    void _INR_A(); void _INR_B(); void _INR_C(); void _INR_D(); void _INR_E(); void _INR_H(); void _INR_L(); void _INR_M();
    void _INX_B(); void _INX_D(); void _INX_H(); void _INX_SP();
    void _DCR_A(); void _DCR_B(); void _DCR_C(); void _DCR_D(); void _DCR_E(); void _DCR_H(); void _DCR_L(); void _DCR_M();
    void _DCX_B(); void _DCX_D(); void _DCX_H(); void _DCX_SP();
    void _LXI_B_imm16(); void _LXI_D_imm16(); void _LXI_H_imm16(); void _LXI_SP_imm16();
    void _RLC(); void _RAL(); void _RRC(); void _RAR();
    void _STC(); void _CMA(); void _CMC();
    void _STAX_B(); void _STAX_D(); void _SHLD_addr16(); void _STA_addr16();
    void _LDAX_B(); void _LDAX_D(); void _LHLD_addr16(); void _LDA_addr16();
    void _DAD_B(); void _DAD_D(); void _DAD_H(); void _DAD_SP();
    void _ADD_B(); void _ADD_C(); void _ADD_D(); void _ADD_E(); void _ADD_H(); void _ADD_L(); void _ADD_M(); void _ADD_A();
    void _ADC_B(); void _ADC_C(); void _ADC_D(); void _ADC_E(); void _ADC_H(); void _ADC_L(); void _ADC_M(); void _ADC_A();
    void _SUB_B(); void _SUB_C(); void _SUB_D(); void _SUB_E(); void _SUB_H(); void _SUB_L(); void _SUB_M(); void _SUB_A();
    void _SBB_B(); void _SBB_C(); void _SBB_D(); void _SBB_E(); void _SBB_H(); void _SBB_L(); void _SBB_M(); void _SBB_A();
    void _ANA_B(); void _ANA_C(); void _ANA_D(); void _ANA_E(); void _ANA_H(); void _ANA_L(); void _ANA_M(); void _ANA_A();
    void _XRA_B(); void _XRA_C(); void _XRA_D(); void _XRA_E(); void _XRA_H(); void _XRA_L(); void _XRA_M(); void _XRA_A();
    void _ORA_B(); void _ORA_C(); void _ORA_D(); void _ORA_E(); void _ORA_H(); void _ORA_L(); void _ORA_M(); void _ORA_A();
    void _CMP_B(); void _CMP_C(); void _CMP_D(); void _CMP_E(); void _CMP_H(); void _CMP_L(); void _CMP_M(); void _CMP_A();
    void _ADI_imm8();  void _ACI_imm8(); void _SUI_imm8(); void _SBI_imm8(); void _ANI_imm8(); void _XRI_imm8(); void _ORI_imm8(); void _CPI_imm8();
    void _RNZ();  void _RNC();  void _RPO();  void _RP(); void _RZ(); void _RC(); void _RPE(); void _RM();
    void _JNZ();  void _JNC();  void _JPO();  void _JP(); void _JZ(); void _JC(); void _JPE(); void _JM();
    void _CNZ();   void _CNC();  void _CPO();   void _CP(); void _CZ(); void _CC(); void _CPE(); void _CM();
    void _RST_0();   void _RST_1();  void _RST_2();  void _RST_3();  void _RST_4();   void _RST_5();  void _RST_6();  void _RST_7();
    void _XTHL();  void _XCHG();  void _PCHL();  void _SPHL();
    void _POP_B();  void _POP_D();   void _POP_H();  void _POP_PSW();
    void _PUSH_B();  void _PUSH_D();  void _PUSH_H();  void _PUSH_PSW();
    void _NOP();
    void _HLT();


    void Init_External_Peripherals();

	using InstructionHandler = void(I8080::*)();
	array <InstructionHandler, 256>  instructions;
	void InitInstructions();
};





#endif // !I8080_H
