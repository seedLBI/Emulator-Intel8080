#include "I8080.h"







void I8080::Init_External_Peripherals() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "init ports processor:" << endl;
#endif

	External_Peripherals.resize(255);

	for (int i = 0x00; i < 0x05; i++)
		External_Peripherals[i] = new I8080_Port(i);
	for (int i = 0x0a; i < 0x10; i++)
		External_Peripherals[i] = new I8080_Port(i);
	for (int i = 0x11; i < 0x16; i++)
		External_Peripherals[i] = new I8080_Port(i);
	for (int i = 0x17; i < 0xff; i++)
		External_Peripherals[i] = new I8080_Port(i);

	External_Peripherals[ 0x05 ] = new I8080_PixelScreen();
	External_Peripherals[ 0x06 ] = new I8080_PixelScreenTwoBuffers();
	External_Peripherals[ 0x07 ] = new I8080_SymbolScreen();
	External_Peripherals[ 0x08 ] = new I8080_Port(0x08);
	External_Peripherals[ 0x09 ] = new I8080_GeneratorRandomValues();
	External_Peripherals[ 0x10 ] = new I8080_AsyncKeyboard();
	External_Peripherals[ 0x16 ] = new I8080_Timer();

}

inline void I8080::SetSP_nextAdress(const uint16_t& next_adress) {
	Memory[SP] = next_adress & 0xff;
	Memory[SP + 1] = next_adress >> 8;
}

inline void I8080::SetPC(const int& adress) {
	Viseted_Memory[adress] = true;
	PC = adress;
}

inline void I8080::SetVisitedMemoryFromPC(const int& count) {
	for (int i = PC; i < (PC + count); ++i) {
		Viseted_Memory[i] = true;
	}
}

inline void I8080::IncrementPC(const int& count) {
	for (int i = PC; i < (PC + count); ++i) {
		Viseted_Memory[i] = true;
	}
	PC += count;
}

inline int I8080::GetAdressHL() { return (H << 8) | L; }


void I8080::EraseMemory() {
	for (unsigned int i = 0; i < SIZE_MEMORY; i++) {
		Memory[i] = 0x00;
		Viseted_Memory[i] = false;
	}
}

void I8080::LoadMemory(const vector<OpcodeAdressed>& array) {
	EraseMemory();

	for (unsigned int i = 0; i < array.size(); i++) {
		Memory[array[i].adress_h * 256 + array[i].adress_l] = array[i].opcode;
	}
}




void I8080::InitPointer2State(CurrentState& cs) {
	cs.A = &A;
	cs.B = &B;
	cs.C = &C;
	cs.D = &D;
	cs.E = &E;
	cs.H = &H;
	cs.L = &L;
	cs.CountTicks = &CountTicks;
	cs.CountInstruction = &CountInstruction;
	cs.PC = &PC;
	cs.SP = &SP;
	cs.Carry = &Carry;
	cs.Paruty = &Paruty;
	cs.Zero = &Zero;
	cs.Sign = &Sign;
	cs.AC = &AC;
}

void I8080::NextStep() {
	CountInstruction++;
	ALU(Memory[PC]);
}

void I8080::Reset() {
	SetPC(0);
	SP = 0;
	A = 0;
	B = 0;
	C = 0;
	D = 0;
	E = 0;
	H = 0;
	L = 0;
	Carry = false;
	Sign = false;
	Paruty = false;
	Zero = false;

	Flag_Stop = false;
	Flag_Waiting_Input = false;
	Flag_GetAnswer = false;

	Output.clear();
	RemoveAllBreakPoints();

	CountTicks = 0;
	CountInstruction = 0;

	for (int i = 0; i < External_Peripherals.size(); i++)
		External_Peripherals[i]->Reset();

}

bool * I8080::IsStop() {
	return &Flag_Stop;
}
void I8080::ResetFlagStop() {
	Flag_Stop = false;
}
void I8080::ActiveFlagStop() {
	Flag_Stop = true;
}
bool I8080::IsWaitingPortInput() {
	return Flag_Waiting_Input;
}
void I8080::InputAnswer2Port(const uint8_t& Answer) {
	Flag_GetAnswer = true;
	Flag_Waiting_Input = false;

	Input = Answer;
}
vector<unsigned int> I8080::GetOutputConsole() {
	return Output;
}
bool* I8080::GetBreakpointsInMemory() {
	return BreakPoints;
}
void I8080::SetBreakPointPosition(const unsigned int& Position) {
	BreakPoints[Position] = !BreakPoints[Position];
}
void I8080::RemoveAllBreakPoints() {
	for (int i = 0; i < SIZE_MEMORY; i++)
		BreakPoints[i] = false;
}
bool I8080::PC_on_BreakPoint() {
	return BreakPoints[PC];
}

uint64_t I8080::GetCountTicks() {
	return CountTicks;
}

uint64_t I8080::GetCountInstruction() {
	return CountInstruction;
}

unsigned int I8080::GetProgrammCounter() {
	return PC;
}

void I8080::SetProgrammCounter(const unsigned int& index) {
	SetPC(index);
	Flag_Stop = false;
}

std::vector<I8080_Port*> I8080::Get_External_Peripherals() {
	return External_Peripherals;
}

uint8_t* I8080::GetMemory() {
	return Memory;
}

bool* I8080::GetVisetedMemory() {
	return Viseted_Memory;
}







void I8080::_XRA(const uint8_t& value) {
	CountTicks += 4;

	AC = 0;
	A = A ^ value;
	Carry = 0;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	IncrementPC();
}

void I8080::_XRA_B() {
	_XRA(B);
}
void I8080::_XRA_C() {
	_XRA(C);
}
void I8080::_XRA_D() {
	_XRA(D);
}
void I8080::_XRA_E() {
	_XRA(E);
}
void I8080::_XRA_H() {
	_XRA(H);
}
void I8080::_XRA_L() {
	_XRA(L);
}
void I8080::_XRA_M() {
	CountTicks += 3;
	_XRA(Memory[GetAdressHL()]);
}
void I8080::_XRA_A() {
	_XRA(A);
}
void I8080::_XRI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_XRA(Memory[PC]);
}

void I8080::_SUB(const uint8_t& value) {
	CountTicks += 4;


	AC = ((A - value) ^ A ^ value) & 16;

	Carry = (A < value);
	A -= value;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);
	IncrementPC();
}


void I8080::_SUB_B() {
	_SUB(B);
}
void I8080::_SUB_C() {
	_SUB(C);
}
void I8080::_SUB_D() {
	_SUB(D);
}
void I8080::_SUB_E() {
	_SUB(E);
}
void I8080::_SUB_H() {
	_SUB(H);
}
void I8080::_SUB_L() {
	_SUB(L);
}
void I8080::_SUB_M() {
	CountTicks += 3;
	_SUB(Memory[GetAdressHL()]);
}
void I8080::_SUB_A() {
	_SUB(A);
}
void I8080::_SUI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_SUB(Memory[PC]);
}

void I8080::_RLC() {
	CountTicks += 4;
	Carry = A >> 7;
	A = ((A << 1) + (A >> 7));
	IncrementPC();
}
void I8080::_RAL() {
	CountTicks += 4;
	unsigned char last_carry = Carry;
	Carry = A >> 7;
	A = ((A << 1) + (last_carry));
	IncrementPC();
}
void I8080::_RRC() {
	CountTicks += 4;
	unsigned char b = (A << 7);
	Carry = (b >> 7);
	A = (A >> 1) + b;
	IncrementPC();
}
void I8080::_RAR() {
	unsigned char last_carry = Carry;
	unsigned char b = (A << 7);
	Carry = (b >> 7);
	A = (A >> 1) + (last_carry << 7);
	IncrementPC();
}

void I8080::_SBB(const uint8_t& value) {
	CountTicks += 4;

	AC = ((A - value - Carry) ^ A ^ value) & 16;

	bool C_old = Carry;
	Carry = (A < value + Carry);
	A -= value + C_old;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);
	IncrementPC();
}


void I8080::_SBB_B() {
	_SBB(B);
}
void I8080::_SBB_C() {
	_SBB(C);
}
void I8080::_SBB_D() {
	_SBB(D);
}
void I8080::_SBB_E() {
	_SBB(E);
}
void I8080::_SBB_H() {
	_SBB(H);
}
void I8080::_SBB_L() {
	_SBB(L);
}
void I8080::_SBB_M() {
	CountTicks += 3;
	_SBB(Memory[GetAdressHL()]);
}
void I8080::_SBB_A() {
	_SBB(A);
}
void I8080::_SBI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_SBB(Memory[PC]);
}

void I8080::_STAX_B() {
	CountTicks += 7;
	Memory[B * 256 + C] = A;
	IncrementPC();
}
void I8080::_STAX_D() {
	CountTicks += 7;
	Memory[D * 256 + E] = A;
	IncrementPC();
}
void I8080::_SHLD_addr16() {
	CountTicks += 16;

	unsigned char indexFirst = Memory[PC + 1];
	unsigned char indexSecond = Memory[PC + 2];

	Memory[indexFirst * 256 + indexSecond] = L;
	Memory[indexFirst * 256 + indexSecond + 1] = H;
	IncrementPC(3);
}
void I8080::_STA_addr16() {
	CountTicks += 13;
	unsigned char indexFirst = Memory[PC + 1];
	unsigned char indexSecond = Memory[PC + 2];

	Memory[indexFirst * 256 + indexSecond] = A;
	IncrementPC(3);
}

void I8080::_RST(const uint8_t& N) {
	CountTicks += 11;

	SP = SP - 2;

	SetSP_nextAdress(PC + 1);
	SetPC(uint16_t(N) * 8);
}


void I8080::_RST_0() {
	_RST(0);
}
void I8080::_RST_1() {
	_RST(1);
}
void I8080::_RST_2() {
	_RST(2);
}
void I8080::_RST_3() {
	_RST(3);
}
void I8080::_RST_4() {
	_RST(4);
}
void I8080::_RST_5() {
	_RST(5);
}
void I8080::_RST_6() {
	_RST(6);
}
void I8080::_RST_7() {
	_RST(7);
}

void I8080::_RET() {
	CountTicks += 10;

	SetVisitedMemoryFromPC(1);
	SetPC(Memory[SP + 1] * 256 + Memory[SP]);
	SP += 2;
}


void I8080::_RNZ() {
	if (Zero == 0) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RNC() {
	if (Carry == 0) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RPO() {
	if (Paruty == 0) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RP() {
	if (Sign == 0) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RZ() {
	if (Zero == 1) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RC() {
	if (Carry == 1) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RPE() {
	if (Paruty == 1) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}
void I8080::_RM() {
	if (Sign == 1) {
		CountTicks += 1;
		_RET();
	}
	else {
		CountTicks += 5;
		IncrementPC();
	}
}

void I8080::_PUSH_B() {
	CountTicks += 11;
	SP--;
	Memory[SP] = B;
	SP--;
	Memory[SP] = C;
	IncrementPC();
}
void I8080::_PUSH_D() {
	CountTicks += 11;
	SP--;
	Memory[SP] = D;
	SP--;
	Memory[SP] = E;
	IncrementPC();
}
void I8080::_PUSH_H() {
	CountTicks += 11;
	SP--;
	Memory[SP] = H;
	SP--;
	Memory[SP] = L;
	IncrementPC();
}
void I8080::_PUSH_PSW() {
	CountTicks += 11;
	SP--;
	Memory[SP] = A;
	SP--;
	Memory[SP] = 0x02 + Carry + Paruty * 4 + AC * 16 + Zero * 64 + Sign * 128;
	IncrementPC();
}

void I8080::_POP_B() {
	CountTicks += 10;
	C = Memory[SP];
	SP++;
	B = Memory[SP];
	SP++;
	IncrementPC();
}
void I8080::_POP_D() {
	CountTicks += 10;
	E = Memory[SP];
	SP++;
	D = Memory[SP];
	SP++;
	IncrementPC();
}
void I8080::_POP_H() {
	CountTicks += 10;
	L = Memory[SP];
	SP++;
	H = Memory[SP];
	SP++;
	IncrementPC();
}
void I8080::_POP_PSW() {
	CountTicks += 10;
	Carry = (Memory[SP] & 0b00000001) == 1;
	Paruty = (Memory[SP] & 0b00000100) == 4;
	AC = (Memory[SP] & 0b00010000) == 16;
	Zero = (Memory[SP] & 0b01000000) == 64;
	Sign = (Memory[SP] & 0b10000000) == 128;
	SP++;
	A = Memory[SP];
	SP++;
	IncrementPC();
}

void I8080::_STC() {
	CountTicks += 4;
	Carry = 1;
	IncrementPC();
}
void I8080::_CMA() {
	CountTicks += 4;
	A = A ^ 255;
	IncrementPC();
}
void I8080::_CMC() {
	CountTicks += 4;
	Carry = !Carry;
	IncrementPC();
}

void I8080::_INPUT() {
	
	if (Memory[PC + 1] == 0x08) {
		if (Flag_Waiting_Input) {
			return;
		}

		if (Flag_GetAnswer) {
			Flag_GetAnswer = false;
			Flag_Waiting_Input = false;

			A = Input;

			CountTicks += 10;
			IncrementPC(2);

			return;
		}


		Flag_Waiting_Input = true;
		return;

	}
	
	A = External_Peripherals[Memory[PC + 1]]->GetOutput();
	CountTicks += 10;
	IncrementPC(2);
}
void I8080::_OUTPUT() {
	CountTicks += 10;
	
	if (Memory[PC + 1] == 0x02) {
		Output.push_back(A);
		if (Output.size() > 1024) {
			Output.erase(Output.begin());
		}
	}
	else {
		External_Peripherals[Memory[PC + 1]]->SetInput(A);
	}
	


	IncrementPC(2);
}

void I8080::_XTHL() {
	CountTicks += 18;

	swap(H, Memory[SP + 1]);
	swap(L, Memory[SP]);
	IncrementPC();
}
void I8080::_XCHG() {
	CountTicks += 4;
	swap(D, H);
	swap(E, L);
	IncrementPC();
}
void I8080::_PCHL() {
	CountTicks += 5;
	SetPC(GetAdressHL());
}
void I8080::_SPHL() {
	CountTicks += 5;
	SP--;
	Memory[SP] = H / 256;
	SP--;
	Memory[SP] = L % 256;

	IncrementPC();
}



void I8080::_NOP() {
	CountTicks += 4;
	IncrementPC();
}

void I8080::_HLT() {
	CountTicks += 7;
	Flag_Stop = true;
}

inline void I8080::_ORA(const uint8_t& value) {
	CountTicks += 4;

	AC = 0;
	A = A | value;
	Carry = 0;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	IncrementPC();
}

void I8080::_ORA_B() {
	_ORA(B);
}
void I8080::_ORA_C() {
	_ORA(C);
}
void I8080::_ORA_D() {
	_ORA(D);
}
void I8080::_ORA_E() {
	_ORA(E);
}
void I8080::_ORA_H() {
	_ORA(H);
}
void I8080::_ORA_L() {
	_ORA(L);
}
void I8080::_ORA_M() {
	CountTicks += 3;
	_ORA(Memory[GetAdressHL()]);
}
void I8080::_ORA_A() {
	_ORA(A);
}
void I8080::_ORI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_ORA(Memory[PC]);
}

inline void I8080::_MVI(uint8_t& valueTo) {
	CountTicks += 7;
	IncrementPC();
	valueTo = Memory[PC];
	IncrementPC();
}

void I8080::_MVI_A_imm8() {
	_MVI(A);
}
void I8080::_MVI_B_imm8() {
	_MVI(B);
}
void I8080::_MVI_C_imm8() {
	_MVI(C);
}
void I8080::_MVI_D_imm8() {
	_MVI(D);
}
void I8080::_MVI_E_imm8() {
	_MVI(E);
}
void I8080::_MVI_H_imm8() {
	_MVI(H);
}
void I8080::_MVI_L_imm8() {
	_MVI(L);
}
void I8080::_MVI_M_imm8() {
	CountTicks += 3;
	_MVI(Memory[GetAdressHL()]);
}

inline void I8080::_MOV(uint8_t& valueTo, const uint8_t& valueFrom) {
	CountTicks += 5;
	valueTo = valueFrom;
	IncrementPC();
}

void I8080::_MOV_A_A() {
	_MOV(A, A);
}
void I8080::_MOV_A_B() {
	_MOV(A, B);
}
void I8080::_MOV_A_C() {
	_MOV(A, C);
}
void I8080::_MOV_A_D() {
	_MOV(A, D);
}
void I8080::_MOV_A_E() {
	_MOV(A, E);
}
void I8080::_MOV_A_H() {
	_MOV(A, H);
}
void I8080::_MOV_A_L() {
	_MOV(A, L);
}
void I8080::_MOV_A_M() {
	CountTicks += 2;
	_MOV(A, Memory[GetAdressHL()]);
}


void I8080::_MOV_B_A() {
	_MOV(B, A);
}
void I8080::_MOV_B_B() {
	_MOV(B, B);
}
void I8080::_MOV_B_C() {
	_MOV(B, C);
}
void I8080::_MOV_B_D() {
	_MOV(B, D);
}
void I8080::_MOV_B_E() {
	_MOV(B, E);
}
void I8080::_MOV_B_H() {
	_MOV(B, H);
}
void I8080::_MOV_B_L() {
	_MOV(B, L);
}
void I8080::_MOV_B_M() {
	CountTicks += 2;
	_MOV(B, Memory[GetAdressHL()]);
}


void I8080::_MOV_C_A() {
	_MOV(C, A);
}
void I8080::_MOV_C_B() {
	_MOV(C, B);
}
void I8080::_MOV_C_C() {
	_MOV(C, C);
}
void I8080::_MOV_C_D() {
	_MOV(C, D);
}
void I8080::_MOV_C_E() {
	_MOV(C, E);
}
void I8080::_MOV_C_H() {
	_MOV(C, H);
}
void I8080::_MOV_C_L() {
	_MOV(C, L);
}
void I8080::_MOV_C_M() {
	CountTicks += 2;
	_MOV(C, Memory[GetAdressHL()]);
}


void I8080::_MOV_D_A() {
	_MOV(D, A);
}
void I8080::_MOV_D_B() {
	_MOV(D, B);
}
void I8080::_MOV_D_C() {
	_MOV(D, C);
}
void I8080::_MOV_D_D() {
	_MOV(D, D);
}
void I8080::_MOV_D_E() {
	_MOV(D, E);
}
void I8080::_MOV_D_H() {
	_MOV(D, H);
}
void I8080::_MOV_D_L() {
	_MOV(D, L);
}
void I8080::_MOV_D_M() {
	CountTicks += 2;
	_MOV(D, Memory[GetAdressHL()]);
}


void I8080::_MOV_E_A() {
	_MOV(E, A);
}
void I8080::_MOV_E_B() {
	_MOV(E, B);
}
void I8080::_MOV_E_C() {
	_MOV(E, C);
}
void I8080::_MOV_E_D() {
	_MOV(E, D);
}
void I8080::_MOV_E_E() {
	_MOV(E, E);
}
void I8080::_MOV_E_H() {
	_MOV(E, H);
}
void I8080::_MOV_E_L() {
	_MOV(E, L);
}
void I8080::_MOV_E_M() {
	CountTicks += 2;
	_MOV(E, Memory[GetAdressHL()]);
}


void I8080::_MOV_H_A() {
	_MOV(H, A);
}
void I8080::_MOV_H_B() {
	_MOV(H, B);
}
void I8080::_MOV_H_C() {
	_MOV(H, C);
}
void I8080::_MOV_H_D() {
	_MOV(H, D);
}
void I8080::_MOV_H_E() {
	_MOV(H, E);
}
void I8080::_MOV_H_H() {
	_MOV(H, H);
}
void I8080::_MOV_H_L() {
	_MOV(H, L);
}
void I8080::_MOV_H_M() {
	CountTicks += 2;
	_MOV(H, Memory[GetAdressHL()]);
}


void I8080::_MOV_L_A() {
	_MOV(L, A);
}
void I8080::_MOV_L_B() {
	_MOV(L, B);
}
void I8080::_MOV_L_C() {
	_MOV(L, C);
}
void I8080::_MOV_L_D() {
	_MOV(L, D);
}
void I8080::_MOV_L_E() {
	_MOV(L, E);
}
void I8080::_MOV_L_H() {
	_MOV(L, H);
}
void I8080::_MOV_L_L() {
	_MOV(L, L);
}
void I8080::_MOV_L_M() {
	CountTicks += 2;
	_MOV(L, Memory[GetAdressHL()]);
}


void I8080::_MOV_M_A() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], A);
}
void I8080::_MOV_M_B() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], B);
}
void I8080::_MOV_M_C() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], C);
}
void I8080::_MOV_M_D() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], D);
}
void I8080::_MOV_M_E() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], E);
}
void I8080::_MOV_M_H() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], H);
}
void I8080::_MOV_M_L() {
	CountTicks += 2;
	_MOV(Memory[GetAdressHL()], L);
}

void I8080::_LXI_B_imm16() {
	CountTicks += 10;
	B = Memory[PC + 1];
	C = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_D_imm16() {
	CountTicks += 10;
	D = Memory[PC + 1];
	E = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_H_imm16() {
	CountTicks += 10;
	H = Memory[PC + 1];
	L = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_SP_imm16() {
	CountTicks += 10;
	unsigned int sp_h = Memory[PC + 1];
	unsigned int sp_l = Memory[PC + 2];
	SP = sp_h * 256 + sp_l;
	IncrementPC(3);
}

void I8080::_LDAX_B() {
	CountTicks += 7;
	A = Memory[B * 256 + C];
	IncrementPC();
}
void I8080::_LDAX_D() {
	CountTicks += 7;
	A = Memory[D * 256 + E];
	IncrementPC();
}
void I8080::_LHLD_addr16() {
	CountTicks += 16;
	L = Memory[Memory[PC + 1] * 256 + Memory[PC + 2]];
	H = Memory[Memory[PC + 1] * 256 + Memory[PC + 2] + 1];
	IncrementPC(3);
}
void I8080::_LDA_addr16() {
	CountTicks += 16;
	A = Memory[Memory[PC + 1] * 256 + Memory[PC + 2]];
	IncrementPC(3);
}

void I8080::_JMP() {
	CountTicks += 10;
	unsigned int h_t = Memory[PC + 1];
	unsigned int l_t = Memory[PC + 2];
	SetVisitedMemoryFromPC(3);
	SetPC(h_t * 256 + l_t);
}

void I8080::_JNZ() {
	if (Zero == 0)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JNC() {
	if (Carry == 0)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JPO() {
	if (Paruty == 0)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JP() {
	if (Sign == 0)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JZ() {
	if (Zero == 1)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JC() {
	if (Carry == 1)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JPE() {
	if (Carry == 1)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}
void I8080::_JM() {
	if (Sign == 1)
		_JMP();
	else {
		CountTicks += 10;
		IncrementPC(3);
	}
}

inline void I8080::_INX(uint8_t& pair_element1, uint8_t& pair_element2) {
	CountTicks += 5;
	unsigned short first = pair_element1 * 256 + pair_element2;
	first++;
	pair_element1 = first / 256;
	pair_element2 = first % 256;
	IncrementPC();
}
void I8080::_INCREMENT(uint8_t& value) {
	CountTicks += 5;

	value++;
	_SetFlagSign(value);
	_SetFlagParuty(value);
	_SetFlagZero(value);

	AC = ((value & 16) == 0);

	IncrementPC();
}

void I8080::_INR_A() {
	_INCREMENT(A);
}
void I8080::_INR_B() {
	_INCREMENT(B);
}
void I8080::_INR_C() {
	_INCREMENT(C);
}
void I8080::_INR_D() {
	_INCREMENT(D);
}
void I8080::_INR_E() {
	_INCREMENT(E);
}
void I8080::_INR_H() {
	_INCREMENT(H);
}
void I8080::_INR_L() {
	_INCREMENT(L);
}
void I8080::_INR_M() {
	CountTicks += 5;
	_INCREMENT(Memory[GetAdressHL()]);
}

void I8080::_INX_B() {
	_INX(B, C);
}
void I8080::_INX_D() {
	_INX(D, E);
}
void I8080::_INX_H() {
	_INX(H, L);
}
void I8080::_INX_SP() {
	unsigned char f = SP / 256, s = SP % 256;
	_INX(f, s);
	SP = f * 256 + s;
}

inline void I8080::_DECREMENT(uint8_t& value) {
	CountTicks += 5;

	value--;
	_SetFlagSign(value);
	_SetFlagParuty(value);
	_SetFlagZero(value);

	AC = ((value & 16) == 16);

	IncrementPC();
}

inline void I8080::_DCX(uint8_t& pair_element1, uint8_t& pair_element2) {
	CountTicks += 5;
	unsigned short first = pair_element1 * 256 + pair_element2;
	first--;
	pair_element1 = first / 256;
	pair_element2 = first % 256;
	IncrementPC();
}



void I8080::_DCR_A() {
	_DECREMENT(A);
}
void I8080::_DCR_B() {
	_DECREMENT(B);
}
void I8080::_DCR_C() {
	_DECREMENT(C);
}
void I8080::_DCR_D() {
	_DECREMENT(D);
}
void I8080::_DCR_E() {
	_DECREMENT(E);
}
void I8080::_DCR_H() {
	_DECREMENT(H);
}
void I8080::_DCR_L() {
	_DECREMENT(L);
}
void I8080::_DCR_M() {
	CountTicks += 5;
	_DECREMENT(Memory[GetAdressHL()]);
}

void I8080::_DCX_B() {
	_DCX(B, C);
}
void I8080::_DCX_D() {
	_DCX(D, E);
}
void I8080::_DCX_H() {
	_DCX(H, L);
}
void I8080::_DCX_SP() {
	unsigned char f = SP / 256, s = SP % 256;
	_DCX(f, s);
	SP = f * 256 + s;
}

void I8080::_DAD(const uint8_t& pair_element1, const uint8_t& pair_element2) {
	// TODO: переделать...
	CountTicks += 10;

	unsigned int value = pair_element1 * 256 + pair_element2;
	unsigned int second = H * 256 + L;

	Carry = ((SIZE_MEMORY - 1) - second < value);

	second += value;

	H = second / 256;
	L = second % 256;

	IncrementPC();
}


void I8080::_DAD_B() {
	_DAD(B, C);
}
void I8080::_DAD_D() {
	_DAD(D, E);
}
void I8080::_DAD_H() {
	_DAD(H, L);
}
void I8080::_DAD_SP() {
	_DAD(SP / 256, SP % 256);
}
void I8080::_COMPARE(const uint8_t& value) {
	CountTicks += 4;

	AC = ~(A ^ (A - value) ^ value) & 16;
	Carry = A < value;
	_SetFlagSign(A - value);
	_SetFlagParuty(A - value);
	_SetFlagZero(A - value);

	IncrementPC();
}

void I8080::_CMP_B() {
	_COMPARE(B);
}
void I8080::_CMP_C() {
	_COMPARE(C);
}
void I8080::_CMP_D() {
	_COMPARE(D);
}
void I8080::_CMP_E() {
	_COMPARE(E);
}
void I8080::_CMP_H() {
	_COMPARE(H);
}
void I8080::_CMP_L() {
	_COMPARE(L);
}
void I8080::_CMP_M() {
	CountTicks += 3;
	_COMPARE(Memory[GetAdressHL()]);
}
void I8080::_CMP_A() {
	_COMPARE(A);
}
void I8080::_CPI_imm8() {
	IncrementPC();
	CountTicks += 3;
	_COMPARE(Memory[PC]);
}

void I8080::_CALL() {
	CountTicks += 17;

	SP = SP - 2;

	SetSP_nextAdress(PC + 3);

	SetVisitedMemoryFromPC(3);
	SetPC(Memory[PC + 1] * 256 + Memory[PC + 2]);
}


void I8080::_CNZ() {
	if (Zero == 0)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CNC() {
	if (Carry == 0)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CPO() {
	if (Paruty == 0)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CP() {
	if (Sign == 0)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CZ() {
	if (Zero == 1)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CC() {
	if (Carry == 1)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CPE() {
	if (Paruty == 1)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}
void I8080::_CM() {
	if (Sign == 1)
		_CALL();
	else {
		CountTicks -= 6;
		IncrementPC(3);
	}
}

void I8080::_ANA(const uint8_t& value) {
	CountTicks += 4;

	AC = ((A | value) & 8) != 0;

	A = A & value;
	Carry = 0;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	IncrementPC();
}

void I8080::_ANA_B() {
	_ANA(B);
}
void I8080::_ANA_C() {
	_ANA(C);
}
void I8080::_ANA_D() {
	_ANA(D);
}
void I8080::_ANA_E() {
	_ANA(E);
}
void I8080::_ANA_H() {
	_ANA(H);
}
void I8080::_ANA_L() {
	_ANA(L);
}
void I8080::_ANA_M() {
	CountTicks += 3;
	_ANA(Memory[GetAdressHL()]);
}
void I8080::_ANA_A() {
	_ANA(A);
}
void I8080::_ANI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_ANA(Memory[PC]);
}

void I8080::_ADD(const uint8_t& value) {
	CountTicks += 4;

	AC = ((A + value) ^ A ^ value) & 16;

	Carry = (255 - A < value);

	A += value;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	IncrementPC();
}


void I8080::_ADD_B() {
	_ADD(B);
}
void I8080::_ADD_C() {
	_ADD(C);
}
void I8080::_ADD_D() {
	_ADD(D);
}
void I8080::_ADD_E() {
	_ADD(E);
}
void I8080::_ADD_H() {
	_ADD(H);
}
void I8080::_ADD_L() {
	_ADD(L);
}
void I8080::_ADD_M() {
	CountTicks += 3;
	_ADD(Memory[GetAdressHL()]);
}
void I8080::_ADD_A() {
	_ADD(A);
}
void I8080::_ADI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_ADD(Memory[PC]);
}


void I8080::_ADC(const uint8_t& value) {
	CountTicks += 4;

	AC = ((A + value + Carry) ^ A ^ value) & 16;
	bool C_old = Carry;
	Carry = (255 - A < value + Carry);
	A += value + C_old;
	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	IncrementPC();
}


void I8080::_ADC_B() {
	_ADC(B);
}
void I8080::_ADC_C() {
	_ADC(C);
}
void I8080::_ADC_D() {
	_ADC(D);
}
void I8080::_ADC_E() {
	_ADC(E);
}
void I8080::_ADC_H() {
	_ADC(H);
}
void I8080::_ADC_L() {
	_ADC(L);
}
void I8080::_ADC_M() {
	CountTicks += 3;
	_ADC(Memory[GetAdressHL()]);
}
void I8080::_ADC_A() {
	_ADC(A);
}
void I8080::_ACI_imm8() {
	CountTicks += 3;
	IncrementPC();
	_ADC(Memory[PC]);
}

inline void I8080::_SetFlagSign(const uint8_t& value) {
	Sign = value & 128;
}
inline void I8080::_SetFlagParuty(const uint8_t& value) {
	int count = 0;
	for (uint8_t i = 0; i < 8; ++i) {
		count += (((value) & (1 << i)) == (1 << i));
	}
	Paruty = (count % 2 == 0);
}
inline void I8080::_SetFlagZero(const uint8_t& value) {
	Zero = (value == 0);
}

inline void I8080::ALU(const uint8_t& opcode) {
	(this->*instructions[opcode])();
}

void I8080::InitInstructions() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "init instructions" << endl;
#endif
	instructions =
	{
	  &I8080::_NOP,     &I8080::_LXI_B_imm16,  &I8080::_STAX_B,      &I8080::_INX_B,   &I8080::_INR_B,   &I8080::_DCR_B,   &I8080::_MVI_B_imm8, &I8080::_RLC,     &I8080::_NOP,     &I8080::_DAD_B,   &I8080::_LDAX_B,      &I8080::_DCX_B,   &I8080::_INR_C,   &I8080::_DCR_C,   &I8080::_MVI_C_imm8, &I8080::_RRC,
	  &I8080::_NOP,     &I8080::_LXI_D_imm16,  &I8080::_STAX_D,      &I8080::_INX_D,   &I8080::_INR_D,   &I8080::_DCR_D,   &I8080::_MVI_D_imm8, &I8080::_RAL,     &I8080::_NOP,     &I8080::_DAD_D,   &I8080::_LDAX_D,      &I8080::_DCX_D,   &I8080::_INR_E,   &I8080::_DCR_E,   &I8080::_MVI_E_imm8, &I8080::_RAR,
	  &I8080::_NOP,     &I8080::_LXI_H_imm16,  &I8080::_SHLD_addr16, &I8080::_INX_H,   &I8080::_INR_H,   &I8080::_DCR_H,   &I8080::_MVI_H_imm8, &I8080::_NOP,     &I8080::_NOP,     &I8080::_DAD_H,   &I8080::_LHLD_addr16, &I8080::_DCX_H,   &I8080::_INR_L,   &I8080::_DCR_L,   &I8080::_MVI_L_imm8, &I8080::_CMA,
	  &I8080::_NOP,     &I8080::_LXI_SP_imm16, &I8080::_STA_addr16,  &I8080::_INX_SP,  &I8080::_INR_M,   &I8080::_DCR_M,   &I8080::_MVI_M_imm8, &I8080::_STC,     &I8080::_NOP,     &I8080::_DAD_SP,  &I8080::_LDA_addr16,  &I8080::_DCX_SP,  &I8080::_INR_A,   &I8080::_DCR_A,   &I8080::_MVI_A_imm8, &I8080::_CMC,
	  &I8080::_MOV_B_B, &I8080::_MOV_B_C,      &I8080::_MOV_B_D,     &I8080::_MOV_B_E, &I8080::_MOV_B_H, &I8080::_MOV_B_L, &I8080::_MOV_B_M,    &I8080::_MOV_B_A, &I8080::_MOV_C_B, &I8080::_MOV_C_C, &I8080::_MOV_C_D,     &I8080::_MOV_C_E, &I8080::_MOV_C_H, &I8080::_MOV_C_L, &I8080::_MOV_C_M,    &I8080::_MOV_C_A,
	  &I8080::_MOV_D_B, &I8080::_MOV_D_C,      &I8080::_MOV_D_D,     &I8080::_MOV_D_E, &I8080::_MOV_D_H, &I8080::_MOV_D_L, &I8080::_MOV_D_M,    &I8080::_MOV_D_A, &I8080::_MOV_E_B, &I8080::_MOV_E_C, &I8080::_MOV_E_D,     &I8080::_MOV_E_E, &I8080::_MOV_E_H, &I8080::_MOV_E_L, &I8080::_MOV_E_M,    &I8080::_MOV_E_A,
	  &I8080::_MOV_H_B, &I8080::_MOV_H_C,      &I8080::_MOV_H_D,     &I8080::_MOV_H_E, &I8080::_MOV_H_H, &I8080::_MOV_H_L, &I8080::_MOV_H_M,    &I8080::_MOV_H_A, &I8080::_MOV_L_B, &I8080::_MOV_L_C, &I8080::_MOV_L_D,     &I8080::_MOV_L_E, &I8080::_MOV_L_H, &I8080::_MOV_L_L, &I8080::_MOV_L_M,    &I8080::_MOV_L_A,
	  &I8080::_MOV_M_B, &I8080::_MOV_M_C,      &I8080::_MOV_M_D,     &I8080::_MOV_M_E, &I8080::_MOV_M_H, &I8080::_MOV_M_L, &I8080::_HLT,        &I8080::_MOV_M_A, &I8080::_MOV_A_B, &I8080::_MOV_A_C, &I8080::_MOV_A_D,     &I8080::_MOV_A_E, &I8080::_MOV_A_H, &I8080::_MOV_A_L, &I8080::_MOV_A_M,    &I8080::_MOV_A_A,
	  &I8080::_ADD_B,   &I8080::_ADD_C,        &I8080::_ADD_D,       &I8080::_ADD_E,   &I8080::_ADD_H,   &I8080::_ADD_L,   &I8080::_ADD_M,      &I8080::_ADD_A,   &I8080::_ADC_B,   &I8080::_ADC_C,   &I8080::_ADC_D,       &I8080::_ADC_E,   &I8080::_ADC_H,   &I8080::_ADC_L,   &I8080::_ADC_M,      &I8080::_ADC_A,
	  &I8080::_SUB_B,   &I8080::_SUB_C,        &I8080::_SUB_D,       &I8080::_SUB_E,   &I8080::_SUB_H,   &I8080::_SUB_L,   &I8080::_SUB_M,      &I8080::_SUB_A,   &I8080::_SBB_B,   &I8080::_SBB_C,   &I8080::_SBB_D,       &I8080::_SBB_E,   &I8080::_SBB_H,   &I8080::_SBB_L,   &I8080::_SBB_M,      &I8080::_SBB_A,
	  &I8080::_ANA_B,   &I8080::_ANA_C,        &I8080::_ANA_D,       &I8080::_ANA_E,   &I8080::_ANA_H,   &I8080::_ANA_L,   &I8080::_ANA_M,      &I8080::_ANA_A,   &I8080::_XRA_B,   &I8080::_XRA_C,   &I8080::_XRA_D,       &I8080::_XRA_E,   &I8080::_XRA_H,   &I8080::_XRA_L,   &I8080::_XRA_M,      &I8080::_XRA_A,
	  &I8080::_ORA_B,   &I8080::_ORA_C,        &I8080::_ORA_D,       &I8080::_ORA_E,   &I8080::_ORA_H,   &I8080::_ORA_L,   &I8080::_ORA_M,      &I8080::_ORA_A,   &I8080::_CMP_B,   &I8080::_CMP_C,   &I8080::_CMP_D,       &I8080::_CMP_E,   &I8080::_CMP_H,   &I8080::_CMP_L,   &I8080::_CMP_M,      &I8080::_CMP_A,
	  &I8080::_RNZ,     &I8080::_POP_B,        &I8080::_JNZ,         &I8080::_JMP,     &I8080::_CNZ,     &I8080::_PUSH_B,  &I8080::_ADI_imm8,   &I8080::_RST_0,   &I8080::_RZ,      &I8080::_RET,     &I8080::_JZ,          &I8080::_NOP,     &I8080::_CZ,      &I8080::_CALL,    &I8080::_ACI_imm8,   &I8080::_RST_1,
	  &I8080::_RNC,     &I8080::_POP_D,        &I8080::_JNC,         &I8080::_OUTPUT,  &I8080::_CNC,     &I8080::_PUSH_D,  &I8080::_SUI_imm8,   &I8080::_RST_2,   &I8080::_RC,      &I8080::_NOP,     &I8080::_JC,          &I8080::_INPUT,   &I8080::_CC,      &I8080::_NOP,     &I8080::_SBI_imm8,   &I8080::_RST_3,
	  &I8080::_RPO,     &I8080::_POP_H,        &I8080::_JPO,         &I8080::_XTHL,    &I8080::_CPO,     &I8080::_PUSH_H,  &I8080::_ANI_imm8,   &I8080::_RST_4,   &I8080::_RPE,     &I8080::_PCHL,    &I8080::_JPE,         &I8080::_XCHG,    &I8080::_CPE,     &I8080::_NOP,     &I8080::_XRI_imm8,   &I8080::_RST_5,
	  &I8080::_RP,      &I8080::_POP_PSW,      &I8080::_JP,          &I8080::_NOP,     &I8080::_CP,      &I8080::_PUSH_PSW,&I8080::_ORI_imm8,   &I8080::_RST_6,   &I8080::_RM,      &I8080::_SPHL,    &I8080::_JM,          &I8080::_NOP,     &I8080::_CM,      &I8080::_NOP,     &I8080::_CPI_imm8,   &I8080::_RST_7
	};
}



vector<uint8_t> I8080::str_instruction_2_array_bytes(const vector<string>& splitted_command, TypeTranslatorError& ErrorType) {
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


	
	const static robin_hood::unordered_node_map<string, TypeInstruction> GetTypeInstruction = {
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
		ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
		return result;
	}
	//std::cout << command << std::endl;

	TypeInstruction type_instruction;

	auto it = GetTypeInstruction.find(command);
	if (it == GetTypeInstruction.end())
	{
		type_instruction = imm8;
	}
	else {
		type_instruction = it->second;
	}

	static const vector <string> mov_mvi_inr_dcr_arithm_access_registers = { "a","b","c","d","e","l","h","m" };
	static const vector <string> inx_dcx_dad_lxi_access_registers = { "b","d","h","sp" };
	static const vector <string> pop_push_access_registers = { "b","d","h","psw" };



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

		int value = FromString2Int(params[0], ErrorType);

		if (ErrorType != TypeTranslatorError::NOTHING) {
			return result;
		}
		if (value > 255) {
			ErrorType = ERROR_OVERFLOW_VALUE_8BIT;
			return result;
		}

		result.emplace_back(instruction_imm8_map.find(command)->second);
		result.emplace_back(value);
		break;
	}
	case imm16: {

		int value = FromString2Int(params[0], ErrorType);
		if (ErrorType != TypeTranslatorError::NOTHING) {
			return result;
		}
		if (value > 65535) {
			ErrorType = ERROR_OVERFLOW_VALUE_16BIT;
			return result;
		}

		int l_imm16 = value % 256;
		int h_imm16 = value / 256;

		result.emplace_back(instruction_imm16_map.find(command)->second);
		result.emplace_back(h_imm16);
		result.emplace_back(l_imm16);

		break;
	}
	case mov: {
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[1]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		if (params[0] == "m" && params[1] == "m") {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}



		result.emplace_back(all_mov_map.find(params[0])->second.find(params[1])->second);
		break;
	}
	case mvi: {
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}


		int value = FromString2Int(params[1], ErrorType);

		if (ErrorType != TypeTranslatorError::NOTHING) {
			return result;
		}
		if (value > 255) {
			ErrorType = ERROR_OVERFLOW_VALUE_8BIT;
			return result;
		}

		result.emplace_back(mvi_imm8_map.find(params[0])->second);
		result.emplace_back(value);

		break;
	}
	case pop: {
		if (FindInVector(pop_push_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(pop_map.find(params[0])->second);
		break;
	}
	case push: {
		if (FindInVector(pop_push_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}


		result.emplace_back(push_map.find(params[0])->second);
		break;
	}
	case arithmetic: {
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		result.emplace_back(arithm_instruction_registers_map.find(command)->second.find(params[0])->second);
		break;
	}
	case inr: {
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}


		result.emplace_back(inr_map.find(params[0])->second);

		break;
	}
	case dcr: {
		if (FindInVector(mov_mvi_inr_dcr_arithm_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_REGISTER;
			return result;
		}

		result.emplace_back(dcr_map.find(params[0])->second);

		break;
	}
	case inx: {
		if (FindInVector(inx_dcx_dad_lxi_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(inx_map.find(params[0])->second);

		break;
	}
	case dcx: {
		if (FindInVector(inx_dcx_dad_lxi_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(dcx_map.find(params[0])->second);
		break;
	}
	case dad: {
		if (FindInVector(inx_dcx_dad_lxi_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(dad_map.find(params[0])->second);
		break;
	}
	case lxi: {
		if (FindInVector(inx_dcx_dad_lxi_access_registers, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		int value = FromString2Int(params[1], ErrorType);
		if (ErrorType != TypeTranslatorError::NOTHING) {
			return result;
		}
		if (value > 65535) {
			ErrorType = ERROR_OVERFLOW_VALUE_16BIT;
			return result;
		}

		int l_imm16 = value % 256;
		int h_imm16 = value / 256;

		result.emplace_back(lxi_imm16_map.find(params[0])->second);
		result.emplace_back(h_imm16);
		result.emplace_back(l_imm16);

		break;
	}
	case stax: {
		vector<string> access_register =
		{ "b","d" };
		if (FindInVector(access_register, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
			return result;
		}

		result.emplace_back(stax_map.find(params[0])->second);
		break;
	}
	case ldax: {
		vector<string> access_register =
		{ "b","d" };
		if (FindInVector(access_register, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_PARAMS;
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
		vector<string> access_values =
		{ "0","1","2","3","4","5","6","7","8","9" };

		if (FindInVector(access_values, params[0]) == false) {
			ErrorType = TypeTranslatorError::ERROR_INCORECT_VALUE;
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




TranslatorOutput I8080::Translate(const vector<string>& array_of_lines) {
	TranslatorOutput result;


	vector<vector<string>> prepared(array_of_lines.size());

	vector<int> adressesForEachLine(array_of_lines.size(), 0);
	vector<int> NeedCheckThatLineIndex(array_of_lines.size(), 0);



	int CounterForNeedCheck = 0;


	for (int i = 0; i < array_of_lines.size(); ++i)
		prepared[i] = tokenize(array_of_lines[i]);



	uint32_t Adress = 0x0000;
	string LastMarker = "";

	auto checkEquals = [](const vector<pair<string, uint16_t>>& arr, const string& name) {
		for (pair<string, uint16_t> obj : arr) {
			if (obj.first == name)
				return true;
		}
		return false;
		};

	auto checkCollsionMarkerAndConst = [](const vector<pair<string, uint16_t>>& markers, const vector<pair<string, uint16_t>>& consts) {
		for (pair<string, uint16_t> m : markers) {
			for (pair<string, uint16_t> c : consts) {
				if (m.first == c.first)
					return true;
			}
		}
		return false;
		};

	auto FindIndexInStringArray = [](const vector<pair<string, uint16_t>>& arr, const string& name) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i].first == name)
				return i;
		}
		return -1;
		};

	auto FindIndexMarkerByAdress = [](const vector<pair<string, uint16_t>>& arr, const uint16_t& Adress) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i].second == Adress)
				return i;
		}
		return -1;
		};


	string last_local_marker = "";
	int countCommandsAfterLastMarker = 0;

	//cout << "Step 1 ====START====\n";
	// Step 1 - размечаем адреса меркеров
	for (int i = 0; i < prepared.size(); ++i)
	{
		if (prepared[i].size() == 0)
			continue;

		//cout << "-----------------\n";
		//cout << "current adress: " << Adress << endl;

		for (int j = 0; j < prepared[i].size(); ++j) {

			string text = prepared[i][j];

			//cout << "[" << text << "]";

			if (IsAllSpecialSymbols(text))
			{
				result.Error = ERROR_WTF;
				result.LineError = i;
				return result;
			}


			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;


			if (flag_have_dot && flag_have_2dot) {

				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					//cout << " it's ADR " ;

					if (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
							result.LineError = i;
							return result;
						}

						if (value > 65535) {
							result.Error = ERROR_OVERFLOW_VALUE_16BIT;
							result.LineError = i;
							return result;
						}
						j++;
						Adress = value;
						adressesForEachLine[i] = Adress;
						//cout << "   with adress: " << value << endl;
					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_ADRESS;
						result.LineError = i;
						return result;
					}

				}
				else if (command == "set") {
					if (prepared[i].size() > j) {

						adressesForEachLine[i] = Adress;

						if (countCommandsAfterLastMarker == 0 && result.Markers.size() != 0) {
							//cout << "im here" << endl;
							if (result.Vars.size() != 0 && result.Vars.back().adress == result.Markers.back().second) {
								//cout << "adding to last\n";
								int count = prepared[i].size() - (j + 1);
								result.Vars.back().count_elements += count;

							}
							else {
								//cout << "create new var\n";
								int count = prepared[i].size() - (j + 1);

								result.Vars.emplace_back(
									result.Markers.back().first,
									result.Markers.back().second,
									(count > 1),
									count);


							}
						}
						j++;
						while (prepared[i].size() > j) {



							uint64_t value = FromString2Int(prepared[i][j], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								// вот тут встретилась константа проверю еЄ в Step 2
								result.Error = TypeTranslatorError::NOTHING;

								if (NeedCheckThatLineIndex[CounterForNeedCheck - 1] != i) {
									NeedCheckThatLineIndex[CounterForNeedCheck] = i;
									CounterForNeedCheck++;
								}

							}
							else if (value > 255) {
								result.Error = ERROR_OVERFLOW_VALUE_8BIT;
								result.LineError = i;
								return result;
							}



							j++;
							//cout << "   with value: " << value << " at adress: " << Adress << endl;


							Adress++;

							if (Adress > 65535) {
								result.Error = ERROR_OVERFLOW_ADRESS;
								result.LineError = i;
								return result;

							}
							//countCommandsAfterLastMarker++;
						}

					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
						result.LineError = i;
						return result;
					}
					continue;
				}
				else if (command == "const") {
					if (prepared[i].size() - j > 1) {

						string name = prepared[i][j + 1];

						if (CheckName4ConstsAndAdresses(name) == false) {
							result.Error = ERROR_WRONG_DEREKTIV_CONST_NAME;
							result.LineError = i;
							return result;
						}

						if (checkEquals(result.Consts, name)) {
							result.Error = ERROR_DUBLICAT_CONST;
							result.LineError = i;
							return result;
						}


						if (prepared[i].size() - j > 2)
						{
							uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
								result.LineError = i;
								return result;
							}

							if (value > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}

							result.Consts.emplace_back(pair<string, uint16_t>{ name, value });

							if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
								result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
								result.LineError = i;
								return result;
							}


							break;

						}
						else {
							result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
							result.LineError = i;
							return result;
						}

					}
					else {

						result.Error = ERROR_DEREKTIV_CONST_WITHOUT_NAME;
						result.LineError = i;
						return result;
					}
				}
				else {

					if (last_local_marker.size() == 0) {
						result.Error = ERROR_CREATE_ANONIM_MARKER;
						result.LineError = i;
						return result;
					}

					//cout << " it's anonim marker ";
					string marker = last_local_marker + "." + text.substr(1, pos_2dot - 1);

					if (CheckName4ConstsAndAdresses(text.substr(1, pos_2dot - 1)) == false) {
						result.Error = ERROR_WRONG_ADRESS_NAME;
						result.LineError = i;
						return result;
					}

					if (checkEquals(result.Markers, marker)) {
						result.Error = ERROR_DUBLICAT_MARKER;
						result.LineError = i;
						return result;
					}
					adressesForEachLine[i] = Adress;
					result.Markers.emplace_back(pair<string, uint16_t>{ marker, Adress });

					NeedCheckThatLineIndex[CounterForNeedCheck] = i;
					CounterForNeedCheck++;

					if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
						result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
						result.LineError = i;
						return result;
					}

					countCommandsAfterLastMarker = 0;
					continue;
				}


			}
			else if (!flag_have_dot && flag_have_2dot) {
				//cout << " - it's marker -";
				string marker = text.substr(0, pos_2dot);


				if (checkEquals(result.Markers, marker)) {
					result.Error = ERROR_DUBLICAT_MARKER;
					result.LineError = i;
					return result;
				}

				NeedCheckThatLineIndex[CounterForNeedCheck] = i;
				CounterForNeedCheck++;


				adressesForEachLine[i] = Adress;

				//cout << "[" << marker << "]" << endl;
				result.Markers.push_back({ marker, Adress });

				if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
					result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
					result.LineError = i;
					return result;
				}



				last_local_marker = marker;
				countCommandsAfterLastMarker = 0;
				continue;
			}
			else if (flag_have_dot && !flag_have_2dot)
			{
				result.Error = ERROR_UNKNOWN_COMMAND;
				result.LineError = i;
				return result;
			}
			else {
				ToLowerAll(text);

				//cout << "its instruction: [" << text << "]" << endl;

				int bytes = GetCountBytes(text);
				int params = GetCountParams(text);

				if (bytes == 0)
				{
					result.Error = ERROR_UNKNOWN_COMMAND;
					result.LineError = i;
					return result;
				}

				if (params != prepared[i].size() - 1)
				{
					result.Error = ERROR_INCORECT_PARAMS;
					result.LineError = i;
					return result;
				}




				adressesForEachLine[i] = Adress;
				Adress += bytes;

				if (Adress > 65536)
				{
					result.Error = ERROR_OVERFLOW_ADRESS;
					result.LineError = i;
					return result;

				}

				if (params > 0) {
					NeedCheckThatLineIndex[CounterForNeedCheck] = i;
					CounterForNeedCheck++;
				}

				// some instruction here
			}

			countCommandsAfterLastMarker++;



			//cout << endl;

			break;
		}


	}
	//NeedCheckThatLineIndex[CounterForNeedCheck] = i;
	//CounterForNeedCheck++;

	int Size_NeedCheckThatLineIndex = CounterForNeedCheck;


	vector<vector<string>> prepared_old = prepared;

	last_local_marker = "";
	//cout << "Step 2 ====START====\n";
	// Step 2 - «амен€ем все маркеры на сооветсвующие числа адресов
	//          и замен€ем все константы на их значени€
	for (int index = 0; index < Size_NeedCheckThatLineIndex; ++index) {

		int i = NeedCheckThatLineIndex[index];

		for (int j = 0; j < prepared[i].size(); j++) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "set")
				{
					j++;
					while (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = TypeTranslatorError::NOTHING;


							int index = FindIndexInStringArray(result.Consts, prepared[i][j]);
							if (index == -1)
							{
								result.Error = ERROR_WRONG_CONST;
								result.LineError = i;
								return result;
							}

							if (result.Consts[index].second > 255) {
								result.Error = ERROR_OVERFLOW_VALUE_8BIT;
								result.LineError = i;
								return result;
							}

							prepared[i][j] = to_string(result.Consts[index].second);
						}
						else if (value > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}



						j++;
					}
					break;
				}
				else if (command == "adr") {
					break;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}

				break;
			}
			else if (!flag_have_dot && flag_have_2dot) {
				string marker = text.substr(0, pos_2dot);
				LastMarker = marker;
				continue;
			}
			else {
				ToLowerAll(text);

				vector<string> instruction_imm8 = { "adi","sui","ani","ori","aci","sbi","xri","cpi","in","out","rst" };
				vector<string> instruction_imm16 = { "shld","sta","lhld","lda","call","cnz","cnc","cpo","cp","cz","cc","cpe","cm","jmp","jnz","jnc","jpo","jp","jz","jc","jpe","jm" };

				if (text == "mvi")
				{
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;
						int index = FindIndexInStringArray(result.Consts, prepared[i][j + 2]);
						if (index == -1)
						{
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						if (result.Consts[index].second > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 2] = to_string(result.Consts[index].second);
					}

				}
				else if (FindInVector(instruction_imm8, text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;
						int index = FindIndexInStringArray(result.Consts, prepared[i][j + 1]);
						if (index == -1)
						{
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						if (result.Consts[index].second > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 1] = to_string(result.Consts[index].second);
					}
				}
				else if (FindInVector(instruction_imm16, text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;

						//cout << "before: [" << prepared[i][j + 1] << "]\n";
						if (prepared[i][j + 1][0] == '.') {
							prepared[i][j + 1] = LastMarker + prepared[i][j + 1];
						}
						//cout << "after:  [" << prepared[i][j + 1] << "]\n";


						int index_const = FindIndexInStringArray(result.Consts, prepared[i][j + 1]);
						int index_adress = FindIndexInStringArray(result.Markers, prepared[i][j + 1]);


						if (index_adress == -1 && index_const == -1)
						{
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}



						if (index_const != -1) {
							if (result.Consts[index_const].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 1] = to_string(result.Consts[index_const].second);
						}
						else if (index_adress != -1) {
							if (result.Markers[index_adress].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 1] = to_string(result.Markers[index_adress].second);
						}


					}
				}
				else if (text == "lxi") {
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;


						//cout << "before: [" << prepared[i][j + 1] << "]\n";
						if (prepared[i][j + 2][0] == '.') {
							prepared[i][j + 2] = LastMarker + prepared[i][j + 1];
						}
						//cout << "after:  [" << prepared[i][j + 1] << "]\n";


						int index_const = FindIndexInStringArray(result.Consts, prepared[i][j + 2]);
						int index_adress = FindIndexInStringArray(result.Markers, prepared[i][j + 2]);


						if (index_adress == -1 && index_const == -1)
						{
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}



						if (index_const != -1) {
							if (result.Consts[index_const].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 2] = to_string(result.Consts[index_const].second);
						}
						else if (index_adress != -1) {
							if (result.Markers[index_adress].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 2] = to_string(result.Markers[index_adress].second);
						}



					}
				}

				break;
			}
		}
	}

	last_local_marker = "";
	countCommandsAfterLastMarker = 0;
	Adress = 0x0000;
	LastMarker = "";

	//cout << "Step 3 ====START====\n";
	// Step 3 - ‘ормируем массив байткодов (result)
	for (int i = 0; i < prepared.size(); ++i) {
		if (prepared[i].size() == 0) { continue; }

		for (int j = 0; j < prepared[i].size(); ++j) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					break;
				}
				else if (command == "set") {
					j++;
					while (prepared[i].size() > j) {
						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						OpcodeAdressed ca;
						ca.adress_l = adressesForEachLine[i] % 256;
						ca.adress_h = adressesForEachLine[i] / 256;
						ca.opcode = value;


						ca.command = ".set: " + prepared[i][j];

						int index = FindIndexMarkerByAdress(result.Markers, adressesForEachLine[i]);
						if (index != -1) {
							ca.marker = result.Markers[index].first;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}


						result.Opcodes.emplace_back(ca);

						j++;
						adressesForEachLine[i]++;
					}
					continue;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}
			}
			else if (!flag_have_dot && flag_have_2dot) {
				continue;
			}
			else {
				//ToLowerAll(text);
				//int bytes = GetCountBytes(text);
				//int params = GetCountParams(text);


				vector<uint8_t> opcodes = str_instruction_2_array_bytes(prepared[i], result.Error);

				if (result.Error != TypeTranslatorError::NOTHING) {
					result.LineError = i;
					return result;
				}

				string command = "";

				for (int k = 0; k < prepared[i].size(); ++k) {
					command += prepared_old[i][k] + " ";
				}

				for (int k = 0; k < opcodes.size(); ++k)
				{
					//cout << std::hex << int(opcodes[k])<< std::dec << endl;
					OpcodeAdressed ca;
					ca.adress_l = (adressesForEachLine[i] + k) % 256;
					ca.adress_h = (adressesForEachLine[i] + k) / 256;
					ca.opcode = opcodes[k];
					if (k == 0)
					{
						ca.command = command;

						int index = FindIndexMarkerByAdress(result.Markers, adressesForEachLine[i]);
						if (index != -1) {
							ca.marker = result.Markers[index].first;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}
					}
					result.Opcodes.emplace_back(ca);

				}

				//Adress += bytes;
			}

			break;
		}


	}


	return result;

}





/*


TranslatorOutput I8080::Translate(const vector<string>& array_of_lines) {
	TranslatorOutput result;


	vector<vector<string>> prepared (array_of_lines.size());

	vector<int> adressesForEachLine (array_of_lines.size(),0);
	vector<int> NeedCheckThatLineIndex(array_of_lines.size(), 0);

	robin_hood::unordered_flat_map<string, uint16_t> Markers;
	robin_hood::unordered_flat_map<string, uint16_t> Consts;


	int CounterForNeedCheck = 0;


	for (int i = 0; i < array_of_lines.size(); ++i)
		prepared[i] = tokenize(array_of_lines[i]);



	uint32_t Adress = 0x0000;
	string LastMarker = "";



	auto FindIndexMarkerByAdress = [](const robin_hood::unordered_flat_map<std::string, uint16_t>& arr, const uint16_t& Adress) {
		for (auto& n : arr) {
			if (n.second == Adress)
				return n.first;
		}
		return std::string("");

		};


	string last_local_marker = "";
	int countCommandsAfterLastMarker = 0;

	//cout << "Step 1 ====START====\n";
	// Step 1 - размечаем адреса меркеров
	for (int i = 0; i < prepared.size(); ++i)
	{
		if (prepared[i].size() == 0)
			continue;

		//cout << "-----------------\n";
		//cout << "current adress: " << Adress << endl;

		for (int j = 0; j < prepared[i].size(); ++j) {

			string text = prepared[i][j];

			//cout << "[" << text << "]";

			if (IsAllSpecialSymbols(text))
			{
				result.Error = ERROR_WTF;
				result.LineError = i;
				return result;
			}


			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;


			if (flag_have_dot && flag_have_2dot) {

				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					//cout << " it's ADR " ;

					if (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
							result.LineError = i;
							return result;
						}

						if (value > 65535) {
							result.Error = ERROR_OVERFLOW_VALUE_16BIT;
							result.LineError = i;
							return result;
						}
						j++;
						Adress = value;
						adressesForEachLine[i] = Adress;
						//cout << "   with adress: " << value << endl;
					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_ADRESS;
						result.LineError = i;
						return result;
					}

				}
				else if (command == "set") {
					if (prepared[i].size() > j) {

						adressesForEachLine[i] = Adress;

						if (countCommandsAfterLastMarker == 0 && result.Markers.size() != 0) {
							//cout << "im here" << endl;
							if (result.Vars.size() != 0 && result.Vars.back().adress == result.Markers.back().second) {
								//cout << "adding to last\n";
								int count = prepared[i].size() - (j + 1);
								result.Vars.back().count_elements += count;

							}
							else {
								//cout << "create new var\n";
								int count = prepared[i].size() - (j + 1);

								result.Vars.push_back({
									result.Markers.back().first,
									result.Markers.back().second,
									(count > 1),
									count });


							}
						}
						j++;
						while (prepared[i].size() > j) {



							uint64_t value = FromString2Int(prepared[i][j], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								// вот тут встретилась константа проверю еЄ в Step 2
								result.Error = TypeTranslatorError::NOTHING;

								if (NeedCheckThatLineIndex[CounterForNeedCheck - 1] != i){
									NeedCheckThatLineIndex[CounterForNeedCheck] = i;
									CounterForNeedCheck++;
								}

							}
							else if (value > 255) {
								result.Error = ERROR_OVERFLOW_VALUE_8BIT;
								result.LineError = i;
								return result;
							}



							j++;
							//cout << "   with value: " << value << " at adress: " << Adress << endl;


							Adress++;

							if (Adress > 65535) {
								result.Error = ERROR_OVERFLOW_ADRESS;
								result.LineError = i;
								return result;

							}
							//countCommandsAfterLastMarker++;
						}

					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
						result.LineError = i;
						return result;
					}
					continue;
				}
				else if (command == "const") {
					if (prepared[i].size() - j > 1) {

						string name = prepared[i][j + 1];

						if (CheckName4ConstsAndAdresses(name) == false) {
							result.Error = ERROR_WRONG_DEREKTIV_CONST_NAME;
							result.LineError = i;
							return result;
						}

						if (Consts.contains(name)) {
							result.Error = ERROR_DUBLICAT_CONST;
							result.LineError = i;
							return result;
						}


						if (prepared[i].size() - j > 2)
						{
							uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
								result.LineError = i;
								return result;
							}

							if (value > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}

							//result.Consts.emplace_back(pair<string, uint16_t>{ name, value });

							Consts[name] = value;

							if (Markers.contains(name)) {
								result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
								result.LineError = i;
								return result;
							}


							break;

						}
						else {
							result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
							result.LineError = i;
							return result;
						}

					}
					else {

						result.Error = ERROR_DEREKTIV_CONST_WITHOUT_NAME;
						result.LineError = i;
						return result;
					}
				}
				else {

					if (last_local_marker.size() == 0) {
						result.Error = ERROR_CREATE_ANONIM_MARKER;
						result.LineError = i;
						return result;
					}

					//cout << " it's anonim marker ";
					string marker = last_local_marker + "." + text.substr(1, pos_2dot - 1);

					if (CheckName4ConstsAndAdresses(text.substr(1, pos_2dot - 1)) == false) {
						result.Error = ERROR_WRONG_ADRESS_NAME;
						result.LineError = i;
						return result;
					}

					if (Markers.contains(marker)) {
						result.Error = ERROR_DUBLICAT_MARKER;
						result.LineError = i;
						return result;
					}
					adressesForEachLine[i] = Adress;

					Markers[marker] = Adress;

					//result.Markers.emplace_back(pair<string, uint16_t>{ marker, Adress });

					NeedCheckThatLineIndex[CounterForNeedCheck] = i;
					CounterForNeedCheck++;

					if (Consts.contains(marker)) {
						result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
						result.LineError = i;
						return result;
					}

					countCommandsAfterLastMarker = 0;
					continue;
				}


			}
			else if (!flag_have_dot && flag_have_2dot) {
				//cout << " - it's marker -";
				string marker = text.substr(0, pos_2dot);


				if (Markers.contains(marker)) {
					result.Error = ERROR_DUBLICAT_MARKER;
					result.LineError = i;
					return result;
				}

				NeedCheckThatLineIndex[CounterForNeedCheck] = i;
				CounterForNeedCheck++;


				adressesForEachLine[i] = Adress;

				//cout << "[" << marker << "]" << endl;
				//result.Markers.push_back({ marker, Adress });

				Markers[marker] = Adress;

				if (Consts.contains(marker)) {
					result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
					result.LineError = i;
					return result;
				}



				last_local_marker = marker;
				countCommandsAfterLastMarker = 0;
				continue;
			}
			else if (flag_have_dot && !flag_have_2dot)
			{
				result.Error = ERROR_UNKNOWN_COMMAND;
				result.LineError = i;
				return result;
			}
			else {
				ToLowerAll(text);

				//cout << "its instruction: [" << text << "]" << endl;

				int bytes = GetCountBytes(text);
				int params = GetCountParams(text);

				if (bytes == 0)
				{
					result.Error = ERROR_UNKNOWN_COMMAND;
					result.LineError = i;
					return result;
				}

				if (params != prepared[i].size() - 1)
				{
					result.Error = ERROR_INCORECT_PARAMS;
					result.LineError = i;
					return result;
				}




				adressesForEachLine[i] = Adress;
				Adress += bytes;

				if (Adress > 65536)
				{
					result.Error = ERROR_OVERFLOW_ADRESS;
					result.LineError = i;
					return result;

				}

				if (params > 0) {
					NeedCheckThatLineIndex[CounterForNeedCheck] = i;
					CounterForNeedCheck++;
				}

				// some instruction here
			}
			countCommandsAfterLastMarker++;



			//cout << endl;

			break;
		}


	}
	//NeedCheckThatLineIndex[CounterForNeedCheck] = i;
	//CounterForNeedCheck++;

	int Size_NeedCheckThatLineIndex = CounterForNeedCheck;


	//cout << "All to check: " << CounterForNeedCheck << endl;


	//for (int i = 0; i < CounterForNeedCheck; i++)
	//{
	//	cout << "[";
	//	for (int j = 0; j < prepared[NeedCheckThatLineIndex[i]].size(); j++)
	//	{
	//		cout << prepared[NeedCheckThatLineIndex[i]][j] << " ";
	//	}
	//	cout << "]\n";
	//}




	vector<vector<string>> prepared_old = prepared;

	last_local_marker = "";
	//cout << "Step 2 ====START====\n";
	// Step 2 - «амен€ем все маркеры на сооветсвующие числа адресов
	//          и замен€ем все константы на их значени€
	for (int index = 0; index < Size_NeedCheckThatLineIndex; ++index) {

		int i = NeedCheckThatLineIndex[index];

		for (int j = 0; j < prepared[i].size(); j++) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "set")
				{
					j++;
					while (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = TypeTranslatorError::NOTHING;




if (Consts.find(prepared[i][j]) == Consts.end())
{
	result.Error = ERROR_WRONG_CONST;
	result.LineError = i;
	return result;
}

if (Consts[prepared[i][j]] > 255) {
	result.Error = ERROR_OVERFLOW_VALUE_8BIT;
	result.LineError = i;
	return result;
}

prepared[i][j] = to_string(Consts[prepared[i][j]]);
						}
						else if (value > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}



						j++;
					}
					break;
				}
				else if (command == "adr") {
					break;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}

				break;
			}
			else if (!flag_have_dot && flag_have_2dot) {
				string marker = text.substr(0, pos_2dot);
				LastMarker = marker;
				continue;
			}
			else {
				ToLowerAll(text);

				const static robin_hood::unordered_flat_set<std::string> instruction_imm8{ "adi","sui","ani","ori","aci","sbi","xri","cpi","in","out","rst" };
				const static robin_hood::unordered_flat_set<std::string> instruction_imm16{ "shld","sta","lhld","lda","call","cnz","cnc","cpo","cp","cz","cc","cpe","cm","jmp","jnz","jnc","jpo","jp","jz","jc","jpe","jm" };


				if (text == "mvi")
				{
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;


						if (Consts.contains(prepared[i][j + 2]) == false) {
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						uint16_t value = Consts[prepared[i][j + 2]];

						if (value > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 2] = to_string(value);
					}

				}
				else if (instruction_imm8.contains(text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;


						if (Consts.contains(prepared[i][j + 1]) == false) {
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						uint16_t value = Consts[prepared[i][j + 1]];

						if (value > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 1] = to_string(value);
					}
				}
				else if (instruction_imm16.contains(text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;

						//cout << "before: [" << prepared[i][j + 1] << "]\n";
						if (prepared[i][j + 1][0] == '.') {
							prepared[i][j + 1] = LastMarker + prepared[i][j + 1];
						}
						//cout << "after:  [" << prepared[i][j + 1] << "]\n";


						uint16_t value = 0;

						if (Consts.contains(prepared[i][j + 1]))
							value = Consts[prepared[i][j + 1]];
						else if (Markers.contains(prepared[i][j + 1]))
							value = Markers[prepared[i][j + 1]];
						else {
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}

						if (value > 65535) {
							result.Error = ERROR_OVERFLOW_VALUE_16BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 1] = to_string(value);


					}
				}
				else if (text == "lxi") {
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;


						uint16_t value = 0;

						if (Consts.contains(prepared[i][j + 2]))
							value = Consts[prepared[i][j + 2]];
						else if (Markers.contains(prepared[i][j + 2]))
							value = Markers[prepared[i][j + 2]];
						else {
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}

						if (value > 65535) {
							result.Error = ERROR_OVERFLOW_VALUE_16BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 2] = to_string(value);



					}
				}

				break;
				}
		}
	}

	last_local_marker = "";
	countCommandsAfterLastMarker = 0;
	Adress = 0x0000;
	LastMarker = "";
	//cout << "Step 3 ====START====\n";
	// Step 3 - ‘ормируем массив байткодов (result)
	for (int i = 0; i < prepared.size(); ++i) {
		if (prepared[i].size() == 0) { continue; }

		for (int j = 0; j < prepared[i].size(); ++j) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					break;
				}
				else if (command == "set") {
					j++;
					while (prepared[i].size() > j) {
						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						OpcodeAdressed ca;
						ca.adress_l = adressesForEachLine[i] % 256;
						ca.adress_h = adressesForEachLine[i] / 256;
						ca.opcode = value;


						ca.command = ".set: " + prepared[i][j];

						string nameMarker = FindIndexMarkerByAdress(Markers, adressesForEachLine[i]);

						if (nameMarker.empty() == false) {
							ca.marker = nameMarker;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}


						result.Opcodes.emplace_back(ca);

						j++;
						adressesForEachLine[i]++;
					}
					continue;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}
			}
			else if (!flag_have_dot && flag_have_2dot) {
				continue;
			}
			else {
				//ToLowerAll(text);
				//int bytes = GetCountBytes(text);
				//int params = GetCountParams(text);


				vector<uint8_t> opcodes = str_instruction_2_array_bytes(prepared[i], result.Error);

				if (result.Error != TypeTranslatorError::NOTHING) {
					result.LineError = i;
					return result;
				}

				string command = "";

				for (int k = 0; k < prepared[i].size(); ++k) {
					command += prepared_old[i][k] + " ";
				}

				for (int k = 0; k < opcodes.size(); ++k)
				{
					//cout << std::hex << int(opcodes[k])<< std::dec << endl;
					OpcodeAdressed ca;
					ca.adress_l = (adressesForEachLine[i] + k) % 256;
					ca.adress_h = (adressesForEachLine[i] + k) / 256;
					ca.opcode = opcodes[k];
					if (k == 0)
					{
						ca.command = command;

						string nameMarker = FindIndexMarkerByAdress(Markers, adressesForEachLine[i]);
						if (nameMarker.empty() == false) {
							ca.marker = nameMarker;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}
					}
					result.Opcodes.emplace_back(ca);

				}

				//Adress += bytes;
			}

			break;
		}


	}



	for (auto& n : Markers) {
		result.Markers.push_back({ n.first, n.second });
	}

	for (auto& n : Consts) {
		result.Consts.push_back({ n.first, n.second });
	}



	return result;

}



*/




/*
TranslatorOutput I8080::Translate(const vector<string>& array_of_lines) {
	TranslatorOutput result;


	vector<vector<string>> prepared;

	for (int i = 0; i < array_of_lines.size(); ++i)
		prepared.emplace_back(tokenize(array_of_lines[i]));



	uint32_t Adress = 0x0000;
	string LastMarker = "";

	auto checkEquals = [](const vector<pair<string, uint16_t>>& arr, const string& name) {
		for (pair<string, uint16_t> obj : arr) {
			if (obj.first == name)
				return true;
		}
		return false;
	};

	auto checkCollsionMarkerAndConst = [](const vector<pair<string, uint16_t>>& markers, const vector<pair<string, uint16_t>>& consts) {
		for (pair<string, uint16_t> m : markers) {
			for (pair<string, uint16_t> c : consts) {
				if (m.first == c.first)
					return true;
			}
		}
		return false;
		};

	auto FindIndexInStringArray = [](const vector<pair<string, uint16_t>>& arr, const string& name) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i].first == name)
				return i;
		}
		return -1;
		};

	auto FindIndexMarkerByAdress = [](const vector<pair<string, uint16_t>>& arr, const uint16_t& Adress) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i].second == Adress)
				return i;
		}
		return -1;
		};


	string last_local_marker = "";
	int countCommandsAfterLastMarker = 0;

	//cout << "Step 1 ====START====\n";
	// Step 1 - размечаем адреса меркеров
	for (int i = 0; i < prepared.size(); ++i)
	{
		if (prepared[i].size() == 0)
			continue;

		//cout << "-----------------\n";
		//cout << "current adress: " << Adress << endl;

		for (int j = 0; j < prepared[i].size(); ++j) {

			string text = prepared[i][j];

			//cout << "[" << text << "]";

			if (IsAllSpecialSymbols(text))
			{
				result.Error = ERROR_WTF;
				result.LineError = i;
				return result;
			}


			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;


			if (flag_have_dot && flag_have_2dot) {

				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					//cout << " it's ADR " ;

					if (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
							result.LineError = i;
							return result;
						}

						if (value > 65535) {
							result.Error = ERROR_OVERFLOW_VALUE_16BIT;
							result.LineError = i;
							return result;
						}
						j++;
						Adress = value;
						//cout << "   with adress: " << value << endl;
					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_ADRESS;
						result.LineError = i;
						return result;
					}

				}
				else if (command == "set") {
					if (prepared[i].size() > j) {

						if (countCommandsAfterLastMarker == 0 && result.Markers.size() != 0) {
							//cout << "im here" << endl;

							if (result.Vars.size() != 0 && result.Vars.back().adress == result.Markers.back().second) {
								//cout << "adding to last\n";
								int count = prepared[i].size() - (j + 1);
								result.Vars.back().count_elements += count;

							}
							else {
								//cout << "create new var\n";
								int count = prepared[i].size() - (j + 1);

								result.Vars.push_back({
									result.Markers.back().first,
									result.Markers.back().second,
									(count > 1),
									count });
							}
						}
						j++;
						while (prepared[i].size() > j) {



							uint64_t value = FromString2Int(prepared[i][j], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								// вот тут встретилась константа проверю еЄ в Step 2
								result.Error = TypeTranslatorError::NOTHING;
							}
							else if (value > 255) {
								result.Error = ERROR_OVERFLOW_VALUE_8BIT;
								result.LineError = i;
								return result;
							}



							j++;
							//cout << "   with value: " << value << " at adress: " << Adress << endl;
							Adress++;

							if (Adress > 65535) {
								result.Error = ERROR_OVERFLOW_ADRESS;
								result.LineError = i;
								return result;

							}
							//countCommandsAfterLastMarker++;
						}

					}
					else {
						result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
						result.LineError = i;
						return result;
					}
					continue;
				}
				else if (command == "const") {
					if (prepared[i].size() - j > 1) {

						string name = prepared[i][j + 1];

						if (CheckNameConst(name) == false) {
							result.Error = ERROR_WRONG_DEREKTIV_CONST_NAME;
							result.LineError = i;
							return result;
						}

						if (checkEquals(result.Consts, name)) {
							result.Error = ERROR_DUBLICAT_CONST;
							result.LineError = i;
							return result;
						}


						if (prepared[i].size() - j > 2)
						{
							uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

							if (result.Error != TypeTranslatorError::NOTHING) {
								result.Error = ERROR_UNKNOWN_VALUE_DEREKTIV;
								result.LineError = i;
								return result;
							}

							if (value > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							
							result.Consts.emplace_back(pair<string, uint16_t>{ name, value });

							if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
								result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
								result.LineError = i;
								return result;
							}


							break;

						}
						else {
							result.Error = ERROR_DEREKTIV_WITHOUT_VALUE;
							result.LineError = i;
							return result;
						}

					}
					else {

						result.Error = ERROR_DEREKTIV_CONST_WITHOUT_NAME;
						result.LineError = i;
						return result;
					}
				}
				else {

					if (last_local_marker.size() == 0) {
						result.Error = ERROR_CREATE_ANONIM_MARKER;
						result.LineError = i;
						return result;
					}

					//cout << " it's anonim marker ";
					string marker = last_local_marker + "." + text.substr(1, pos_2dot - 1);

					if (CheckNameAdress(text.substr(1, pos_2dot - 1)) == false) {
						result.Error = ERROR_WRONG_ADRESS_NAME;
						result.LineError = i;
						return result;
					}

					if (checkEquals(result.Markers, marker)) {
						result.Error = ERROR_DUBLICAT_MARKER;
						result.LineError = i;
						return result;
					}

					result.Markers.emplace_back(pair<string, uint16_t>{ marker, Adress });


					if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
						result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
						result.LineError = i;
						return result;
					}

					countCommandsAfterLastMarker = 0;
					continue;
				}


			}
			else if (!flag_have_dot && flag_have_2dot) {
				//cout << " - it's marker -";
				string marker = text.substr(0, pos_2dot);


				if (checkEquals(result.Markers, marker)) {
					result.Error = ERROR_DUBLICAT_MARKER;
					result.LineError = i;
					return result;
				}

				//cout << "[" << marker << "]" << endl;
				result.Markers.push_back({ marker, Adress });

				if (checkCollsionMarkerAndConst(result.Markers, result.Consts)) {
					result.Error = ERROR_COLLISION_BETWEEN_NAMES_MARKER_AND_CONST;
					result.LineError = i;
					return result;
				}



				last_local_marker = marker;
				countCommandsAfterLastMarker = 0;
				continue;
			}
			else if (flag_have_dot && !flag_have_2dot)
			{
				result.Error = ERROR_UNKNOWN_COMMAND;
				result.LineError = i;
				return result;
			}
			else {
				ToLowerAll(text);

				//cout << "its instruction: [" << text << "]" << endl;

				int bytes = GetCountBytes(text);
				int params = GetCountParams(text);

				if (bytes == 0)
				{
					result.Error = ERROR_UNKNOWN_COMMAND;
					result.LineError = i;
					return result;
				}
				//cout << params << "   " << prepared[i].size()-1 << endl;
				if (params != prepared[i].size() - 1)
				{
					result.Error = ERROR_INCORECT_PARAMS;
					result.LineError = i;
					return result;
				}



				Adress += bytes;

				if (Adress > 65536)
				{
					result.Error = ERROR_OVERFLOW_ADRESS;
					result.LineError = i;
					return result;

				}

				// some instruction here
			}
			countCommandsAfterLastMarker++;



			//cout << endl;

			break;
		}


	}


	vector<vector<string>> prepared_old = prepared;

	last_local_marker = "";
	//cout << "Step 2 ====START====\n";
	// Step 2 - «амен€ем все маркеры на сооветсвующие числа адресов
	//          и замен€ем все константы на их значени€ 
	for (int i = 0; i < prepared.size(); ++i) {
		if (prepared[i].size() == 0) { continue; }

		for (int j = 0; j < prepared[i].size(); j++) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "set")
				{
					j++;
					while (prepared[i].size() > j) {

						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						if (result.Error != TypeTranslatorError::NOTHING) {
							result.Error = TypeTranslatorError::NOTHING;


							int index = FindIndexInStringArray(result.Consts, prepared[i][j]);
							if (index == -1)
							{
								result.Error = ERROR_WRONG_CONST;
								result.LineError = i;
								return result;
							}

							if (result.Consts[index].second > 255) {
								result.Error = ERROR_OVERFLOW_VALUE_8BIT;
								result.LineError = i;
								return result;
							}

							prepared[i][j] = to_string(result.Consts[index].second);
						}
						else if (value > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}



						j++;
					}
					break;
				}
				else if (command == "adr") {
					break;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}

				break;
			}
			else if (!flag_have_dot && flag_have_2dot) {
				string marker = text.substr(0, pos_2dot);
				LastMarker = marker;
				continue;
			}
			else {
				ToLowerAll(text);

				vector<string> instruction_imm8 = { "adi","sui","ani","ori","aci","sbi","xri","cpi","in","out","rst" };
				vector<string> instruction_imm16 = { "shld","sta","lhld","lda","call","cnz","cnc","cpo","cp","cz","cc","cpe","cm","jmp","jnz","jnc","jpo","jp","jz","jc","jpe","jm" };

				if (text == "mvi")
				{
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;
						int index = FindIndexInStringArray(result.Consts, prepared[i][j + 2]);
						if (index == -1)
						{
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						if (result.Consts[index].second > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 2] = to_string(result.Consts[index].second);
					}

				}
				else if (FindInVector(instruction_imm8, text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;
						int index = FindIndexInStringArray(result.Consts, prepared[i][j + 1]);
						if (index == -1)
						{
							result.Error = ERROR_WRONG_CONST;
							result.LineError = i;
							return result;
						}

						if (result.Consts[index].second > 255) {
							result.Error = ERROR_OVERFLOW_VALUE_8BIT;
							result.LineError = i;
							return result;
						}

						prepared[i][j + 1] = to_string(result.Consts[index].second);
					}
				}
				else if (FindInVector(instruction_imm16, text)) {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;

						//cout << "before: [" << prepared[i][j + 1] << "]\n";
						if (prepared[i][j + 1][0] == '.') {
							prepared[i][j + 1] = LastMarker + prepared[i][j + 1];
						}
						//cout << "after:  [" << prepared[i][j + 1] << "]\n";


						int index_const = FindIndexInStringArray(result.Consts, prepared[i][j + 1]);
						int index_adress = FindIndexInStringArray(result.Markers, prepared[i][j + 1]);


						if (index_adress == -1 && index_const == -1)
						{
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}



						if (index_const != -1) {
							if (result.Consts[index_const].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 1] = to_string(result.Consts[index_const].second);
						}
						else if (index_adress != -1) {
							if (result.Markers[index_adress].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 1] = to_string(result.Markers[index_adress].second);
						}


					}
				}
				else if (text == "lxi") {
					uint64_t value = FromString2Int(prepared[i][j + 2], result.Error);

					if (result.Error != TypeTranslatorError::NOTHING) {
						result.Error = TypeTranslatorError::NOTHING;


						//cout << "before: [" << prepared[i][j + 1] << "]\n";
						if (prepared[i][j + 2][0] == '.') {
							prepared[i][j + 2] = LastMarker + prepared[i][j + 1];
						}
						//cout << "after:  [" << prepared[i][j + 1] << "]\n";


						int index_const = FindIndexInStringArray(result.Consts, prepared[i][j + 2]);
						int index_adress = FindIndexInStringArray(result.Markers, prepared[i][j + 2]);


						if (index_adress == -1 && index_const == -1)
						{
							result.Error = ERROR_WRONG_CONST_OR_MARKER;
							result.LineError = i;
							return result;
						}



						if (index_const != -1) {
							if (result.Consts[index_const].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 2] = to_string(result.Consts[index_const].second);
						}
						else if (index_adress != -1) {
							if (result.Markers[index_adress].second > 65535) {
								result.Error = ERROR_OVERFLOW_VALUE_16BIT;
								result.LineError = i;
								return result;
							}
							prepared[i][j + 2] = to_string(result.Markers[index_adress].second);
						}



					}
				}

				break;
			}
		}
	}

	last_local_marker = "";
	countCommandsAfterLastMarker = 0;
	Adress = 0x0000;
	LastMarker = "";
	//cout << "Step 3 ====START====\n";
	// Step 3 - ‘ормируем массив байткодов (result)
	for (int i = 0; i < prepared.size(); ++i) {
		if (prepared[i].size() == 0) { continue; }

		for (int j = 0; j < prepared[i].size(); ++j) {
			string text = prepared[i][j];

			size_t pos_dot = text.find_first_of(".");
			size_t pos_2dot = text.find_first_of(":");
			bool flag_have_dot = pos_dot != string::npos;
			bool flag_have_2dot = pos_2dot != string::npos;

			if (flag_have_dot && flag_have_2dot) {
				string command = text.substr(pos_dot + 1, (pos_2dot - pos_dot) - 1);
				ToLowerAll(command);

				if (command == "adr") {
					uint64_t value = FromString2Int(prepared[i][j + 1], result.Error);
					j++;
					Adress = value;
				}
				else if (command == "set") {
					j++;
					while (prepared[i].size() > j) {
						uint64_t value = FromString2Int(prepared[i][j], result.Error);

						OpcodeAdressed ca;
						ca.adress_l = Adress % 256;
						ca.adress_h = Adress / 256;
						ca.opcode = value;


						ca.command = ".set: " + prepared[i][j];

						int index = FindIndexMarkerByAdress(result.Markers, Adress);
						if (index != -1) {
							ca.marker = result.Markers[index].first;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}


						result.Opcodes.emplace_back(ca);

						j++;
						Adress++;
					}
					continue;
				}
				else if (command == "const") {
					break;
				}
				else {
					continue;
				}
			}
			else if (!flag_have_dot && flag_have_2dot) {
				continue;
			}
			else {
				ToLowerAll(text);
				int bytes = GetCountBytes(text);
				//int params = GetCountParams(text);


				vector<uint8_t> opcodes = str_instruction_2_array_bytes(prepared[i], result.Error);

				if (result.Error != TypeTranslatorError::NOTHING) {
					result.LineError = i;
					return result;
				}

				string command = "";

				for (int k = 0; k < prepared_old[i].size(); ++k)
				{
					command += prepared_old[i][k] + " ";
				}

				for (int k = 0; k < opcodes.size(); ++k)
				{
					//cout << std::hex << int(opcodes[k])<< std::dec << endl;
					OpcodeAdressed ca;
					ca.adress_l = (Adress + k) % 256;
					ca.adress_h = (Adress + k) / 256;
					ca.opcode = opcodes[k];
					if (k == 0)
					{
						ca.command = command;

						int index = FindIndexMarkerByAdress(result.Markers, Adress);
						if (index != -1) {
							ca.marker = result.Markers[index].first;
							ca.adress_marker_l = ca.adress_l;
							ca.adress_marker_h = ca.adress_h;
						}
					}
					result.Opcodes.emplace_back(ca);

				}

				Adress += bytes;
			}

			break;
		}


	}


	return result;

}
*/
