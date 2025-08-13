#ifndef I8085_H
#define I8085_H

#include "Emulator/Port/I8080.Port.ConsoleOutput.h"
#include "Emulator/Port/I8080.Port.SymbolScreen.h"
#include "Emulator/Port/I8080.Port.GeneratorRandomValues.h"
#include "Emulator/Port/I8080.Port.Timer.h"
#include "Emulator/Port/I8080.Port.PixelScreen.h"
#include "Emulator/Port/I8080.Port.PixelScreenTwoBuffers.h"
#include "Emulator/Port/I8080.Port.AsyncKeyboard.h"

#include "Emulator/Processors/Processor.h"
#include <cstdint>
#include <array>


class I8085 : public Processor {
public:

    I8085();
    ~I8085();

    void RemoveAllBreakPoints() override;                                                 // TODO:
    void EraseMemory() override;                                                          // TODO:
    void Reset() override;                                                                // TODO:
    void LoadMemory(const std::vector<uint8_t>& data, const bool& isBinary) override;     // TODO:
    void NextStep() override;                                                             // TODO:

    uint8_t  GetRegisterFlags();
    uint64_t GetCountTicks();
    uint64_t GetCountInstruction();

    uint16_t GetProgrammCounter();
    void     SetProgrammCounter(const uint16_t& index);

    uint16_t GetAdressHL();

    Momento* SaveState() override;
    void     RestoreState(Momento* momento) override;
private:
    
    bool Flag_Stop = false;
    bool Flag_Waiting_Input = false;
    bool Flag_GetAnswer = false;
    uint8_t Input = 0;

    std::array<I8080_Port*, UINT8_MAX> External_Peripherals;
    void InitExternal_Peripherals();

    // ---------------- PROCESSOR DATA -----------------
	std::array<uint8_t, UINT16_MAX> Memory;
	std::array<bool,    UINT16_MAX> Viseted_Memory;
	std::array<bool,    UINT16_MAX> BreakPoints;

	uint8_t A = 0, // Main registers
			B = 0,
			C = 0,
			D = 0,
			E = 0,
			H = 0,
			L = 0;

	uint16_t PC = 0, // Programm counter
		     SP = 0; // Stack register

	bool Sign           = false, // Flags
		 Zero           = false,
		 Paruty         = false,
		 Carry          = false,
		 AuxiliaryCarry = false,
		 V              = false, // Undocumented
		 K              = false; // Undocumented

	bool InterruptEnabled = false;

	uint64_t CountTicks       = 0;
	uint64_t CountInstruction = 0;

	using InstructionHandler = void(I8085::*)();
	std::array <InstructionHandler, 256>  instructions;
	void InitInstructions();


    inline void ALU(const uint8_t& opcode);

    inline void SetSP_nextAdress(const uint16_t& next_adress);
    inline void SetPC(const uint16_t& adress);
    inline void IncrementPC(const uint8_t& count = 1);
    inline void SetVisitedMemoryFromPC(const int& count);

    inline void _SetFlagSign(const uint8_t& value);
    inline void _SetFlagParuty(const uint8_t& value);
    inline void _SetFlagZero(const uint8_t& value);


    // -----------IMPLEMENTATION INSTRUCTION-----------------

    void _INPUT();
    void _OUTPUT();
    void _OUTPUT_COM();

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

    void _EI(); void _DI();
    void _DAA();
    void _RIM(); void _SIM(); // TODO:

    //Undocumented instructuions
    void _ARHL();// TODO:
    void _DSUB();// TODO:
    void _RDEL();// TODO:
    void _LDHI();// TODO:
    void _LDSI();// TODO:
    void _SHLX();// TODO:
    void _RSTV();// TODO:
    void _JNK(); // TODO:
    void _JK();  // TODO:
    void _LHLX();// TODO:
};


#endif // !I8085_H
