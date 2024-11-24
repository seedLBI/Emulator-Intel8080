#include "I8080.h"

I8080::I8080() : Processor(u8"Intel 8080") {
	Init_External_Peripherals();
	InitInstructions();
	InitInstructionsWithHistory();
}

void I8080::Init_External_Peripherals() {
#ifdef WITH_DEBUG_OUTPUT
	cout << "init ports processor:" << endl;
#endif

	External_Peripherals.resize(255);

	for (int i = 0x00; i < 0xff; i++)
		External_Peripherals[i] = new I8080_Port(i);

	External_Peripherals[ 0x02 ] = new I8080_ConsoleOutput();
	External_Peripherals[ 0x05 ] = new I8080_PixelScreen();
	External_Peripherals[ 0x06 ] = new I8080_PixelScreenTwoBuffers();
	External_Peripherals[ 0x07 ] = new I8080_SymbolScreen();
	External_Peripherals[ 0x08 ] = new I8080_Port(0x08);
	External_Peripherals[ 0x09 ] = new I8080_GeneratorRandomValues();
	External_Peripherals[ 0x10 ] = new I8080_AsyncKeyboard();
	External_Peripherals[ 0x16 ] = new I8080_Timer();

}

void I8080::RestoreState(const std::shared_ptr<Momento>& momento) {

	I8080_Momento* i8080_momento = dynamic_cast<I8080_Momento*>(momento.get());

	A				   = i8080_momento->Get_A();
	B				   = i8080_momento->Get_B();
	C				   = i8080_momento->Get_C();
	D				   = i8080_momento->Get_D();
	E				   = i8080_momento->Get_E();
	H				   = i8080_momento->Get_H();
	L				   = i8080_momento->Get_L();
	PC				   = i8080_momento->Get_PC();
	SP				   = i8080_momento->Get_SP();
	Sign			   = i8080_momento->Get_Sign();
	Zero			   = i8080_momento->Get_Zero();
	Paruty			   = i8080_momento->Get_Parity();
	Carry			   = i8080_momento->Get_Carry();
	AuxiliaryCarry	   = i8080_momento->Get_AuxiliaryCarry();
	InterruptEnabled   = i8080_momento->Get_InterruptEnabled();
	SetFlagStop(		 i8080_momento->Get_Flag_Stop());
	Flag_Waiting_Input = i8080_momento->Get_Flag_Waiting_Input();
	Flag_GetAnswer	   = i8080_momento->Get_Flag_GetAnswer();
	Input			   = i8080_momento->Get_Input();
	CountTicks		   = i8080_momento->Get_CountTicks();

	auto data = i8080_momento->Get_changedMemory();
	for (uint8_t i = 0; i < data.size(); i++)
		Memory[data[i].first] = data[i].second;

	

	if (i8080_momento->get_MomentoPort() != nullptr){

		if (i8080_momento->get_MomentoPort()->GetPortNumber() != -1)
		{
			External_Peripherals[i8080_momento->get_MomentoPort()->GetPortNumber()]->RestoreState(i8080_momento->get_MomentoPort());
		}


	}

}


std::shared_ptr<Momento> I8080::SaveState() {

	ptr_To_Last_Momento = std::shared_ptr<Momento>(new I8080_Momento(
		Memory[PC],
		Memory[uint16_t(PC + 1)], Memory[uint16_t(PC + 2)],
		A, B, C, D, E, H, L,
		PC, SP,
		Sign, Zero, Paruty, Carry, AuxiliaryCarry, InterruptEnabled,
		GetFlagStop(), Flag_Waiting_Input, Flag_GetAnswer, Input,
		CountTicks, {}, {}));

	return ptr_To_Last_Momento;
}


inline void I8080::SetSP_nextAdress(const uint16_t& next_adress) {
	Memory[SP]				 = (next_adress & 0x00ff);	  // next.low
	Memory[uint16_t(SP + 1)] = (next_adress & 0xff00) >> 8; // next.high
}

inline void I8080::SetPC(const uint16_t& adress) {
	Viseted_Memory[adress] = true;
	PC = adress;
}

inline void I8080::SetVisitedMemoryFromPC(const int& count) {
	for (int i = PC; i < (PC + count); ++i) {
		Viseted_Memory[i] = true;
	}
}

inline void I8080::IncrementPC(const uint8_t& count) {
	for (int i = PC; i < (PC + count); ++i)
		Viseted_Memory[i] = true;
	PC += count;
}

inline int I8080::GetAdressHL() { return (H << 8) | L; }


void I8080::EraseMemory() {
	for (unsigned int i = 0; i < SIZE_MEMORY; i++) {
		Memory[i] = 0x00;
		Viseted_Memory[i] = false;
	}
	changedMemory.clear();
}

void I8080::LoadMemory(const std::vector<OpcodeAdressed>& array) {
	EraseMemory();

	project_DATA.clear();

	for (unsigned int i = 0; i < array.size(); i++)
		Memory[array[i].adress_h * 256 + array[i].adress_l] = array[i].opcode;

	SetModeProject(ModeProject::USER);
}
void I8080::LoadMemoryFromBinary(const std::vector<uint8_t>& array) {
	EraseMemory();

	project_DATA = array;

	for (unsigned int i = 0; i < array.size(); i++)
		Memory[i] = array[i];

	PC = 0x0000;

	SetModeProject(ModeProject::BIN);

}
void I8080::LoadMemoryFromCOM(const std::vector<uint8_t>& array) {
	EraseMemory();

	project_DATA = array;


	for (unsigned int i = 0; i < array.size(); i++) {
		if (i + 0x0100 > 0xffff)
			break;
		Memory[i + 0x0100] = array[i];
	}

	// inject "out 0" at 0x0000 (signal to stop the test)
	Memory[0x0000] = 0xD3;
	Memory[0x0001] = 0x00;

	// inject "out 1" at 0x0005 (signal to output some characters)
	Memory[0x0005] = 0xD3;
	Memory[0x0006] = 0x01;
	Memory[0x0007] = 0xC9;

	PC = 0x0100;

	SetModeProject(ModeProject::COM);
}

void I8080::ReloadProjectData() {
	if (_ModeProject == ModeProject::COM){
		EraseMemory();

		for (unsigned int i = 0; i < project_DATA.size(); i++) {
			if (i + 0x0100 > 0xffff)
				break;
			Memory[i + 0x0100] = project_DATA[i];
		}

		// inject "out 0" at 0x0000 (signal to stop the test)
		Memory[0x0000] = 0xD3;
		Memory[0x0001] = 0x00;

		// inject "out 1" at 0x0005 (signal to output some characters)
		Memory[0x0005] = 0xD3;
		Memory[0x0006] = 0x01;
		Memory[0x0007] = 0xC9;

		PC = 0x0100;
	}
	else if (_ModeProject == ModeProject::BIN) {
		EraseMemory();

		for (unsigned int i = 0; i < project_DATA.size(); i++)
			Memory[i] = project_DATA[i];

		PC = 0;
	}
}

void I8080::SetModeProject(const ModeProject& mode) {
	if (mode != _ModeProject){

		if (mode == ModeProject::COM) {
			instructions[0xD3] = &I8080::_OUTPUT_COM;
			instructionsWithHistory[0xD3] = &I8080::_OUTPUT_COM;
		}
		else {
			instructions[0xD3] = &I8080::_OUTPUT;
			instructionsWithHistory[0xD3] = &I8080::Hi_OUTPUT;
		}

		_ModeProject = mode;
	}
}

ModeProject I8080::GetModeProject() {
	return _ModeProject;
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
	cs.AuxiliaryCarry = &AuxiliaryCarry;
}

void I8080::NextStep() {
	CountInstruction++;
	ALU(Memory[PC]);
}
void I8080::NextStepWithHistorySaving() {
	ptr_portMomento = std::shared_ptr<Momento>();
	changedMemory.clear();
	CountInstruction++;
	ALU_WithHistorySaving(Memory[PC]);
}



void I8080::Reset() {

	ReloadProjectData();

	if (_ModeProject == ModeProject::COM)
		SetPC(0x0100);
	else
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
	AuxiliaryCarry = false;
	InterruptEnabled = false;

	SetFlagStop(false);
	Flag_Waiting_Input = false;
	Flag_GetAnswer = false;

	CountTicks = 0;
	CountInstruction = 0;

	changedMemory.clear();

	for (int i = 0; i < External_Peripherals.size(); i++)
		External_Peripherals[i]->Reset();

}

bool  I8080::IsWaitingPortInput() {
	return Flag_Waiting_Input;
}
void  I8080::InputAnswer2Port(const uint8_t& Answer) {
	Flag_GetAnswer = true;
	Flag_Waiting_Input = false;

	Input = Answer;
}
bool* I8080::GetBreakpointsInMemory() {
	return BreakPoints;
}
void  I8080::ToggleBreakPointPosition(const uint16_t& Position) {
	BreakPoints[Position] = !BreakPoints[Position];
}


void I8080::SetBreakPointPosition(const uint16_t& Position, const bool& state) {
	BreakPoints[Position] = state;
}
void I8080::RemoveAllBreakPoints() {
	for (int i = 0; i < SIZE_MEMORY; i++)
		BreakPoints[i] = false;
}
bool I8080::OnBreakPoint() {
	return BreakPoints[PC];
}

uint16_t I8080::GetProgrammCounter() {
	return PC;
}

void I8080::SetProgrammCounter(const uint16_t& index) {
	SetPC(index);
	SetFlagStop(false);
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

void I8080::_DAA() {
	CountTicks += 4;

	bool c = Carry;

	uint8_t lsb = A & 0b00001111;
	uint8_t msb = A >> 4;

	uint8_t adjustment = 0;

	if (lsb > 9 || AuxiliaryCarry) {
		adjustment += 0x06;
	}

	if (msb > 9 || Carry || (msb >= 9 && lsb > 9)) {
		adjustment += 0x60;
		c = true;
	}


	AuxiliaryCarry = ((A & 0b00001111) + (adjustment & 0b00001111)) > 0b00001111;
	Carry = (255 - A < adjustment);
	

	A += adjustment;

	_SetFlagSign(A);
	_SetFlagParuty(A);
	_SetFlagZero(A);

	Carry = c;

	IncrementPC();
}

void I8080::_EI() {
	CountTicks += 4;
	InterruptEnabled = true;
	IncrementPC();
}
void I8080::_DI() {
	CountTicks += 4;
	InterruptEnabled = false;
	IncrementPC();
}

void I8080::_XRA(const uint8_t& value) {
	CountTicks += 4;

	A = A ^ value;

	AuxiliaryCarry = 0;
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

	AuxiliaryCarry = (int16_t(A & 0b00001111) - int16_t(value & 0b00001111)) >= 0;
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
	uint8_t last_carry = Carry;
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

	bool C_old = Carry;

	AuxiliaryCarry = (int16_t(A&0b00001111) - int16_t(value&0b00001111) - Carry) >= 0;
	Carry = (uint16_t(A) < uint16_t(value) + uint16_t(Carry));

	A -= value;
	A -= C_old;

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

	unsigned int l = Memory[PC + 1];
	unsigned int h = Memory[PC + 2];

	Memory[h * 256 + l] = L;
	Memory[h * 256 + l + 1] = H;

	IncrementPC(3);
}
void I8080::_STA_addr16() {
	CountTicks += 13;
	unsigned int l = Memory[PC + 1];
	unsigned int h = Memory[PC + 2];

	Memory[h * 256 + l] = A;

	IncrementPC(3);
}

inline void I8080::_RST(const uint8_t& N) {
	CountTicks += 11;

	SP = SP - 2;

	SetSP_nextAdress(PC + 1);
	SetVisitedMemoryFromPC(1);

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

	uint8_t Flags = GetRegisterFlags();
	SP--;
	Memory[SP] = A;
	SP--;
	Memory[SP] = Flags;



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

	uint8_t Flags = Memory[SP];

	Sign = (Flags >> 7) & 1;
	Zero = (Flags >> 6) & 1;
	AuxiliaryCarry = (Flags >> 4) & 1;
	Paruty = (Flags >> 2) & 1;
	Carry = (Flags >> 0) & 1;

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
	External_Peripherals[Memory[PC + 1]]->SetInput(A);
	IncrementPC(2);
}
void I8080::_OUTPUT_COM() {
	CountTicks += 10;

	if (Memory[PC + 1] == 0) {
		SetFlagStop(true);
	}
	else if (Memory[PC + 1] == 1) {
		uint8_t operation = C;

		if (operation == 2) {
			External_Peripherals[0x02]->SetInput(E);
		}
		else if (operation == 9) {
			uint16_t addr = (D << 8) | E;
			do {
				External_Peripherals[0x02]->SetInput(Memory[addr++]);
			} while (Memory[addr] != '$');
		}
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

	SP = H * 256 + L;

	IncrementPC();
}


void I8080::_NOP() {
	CountTicks += 4;
	IncrementPC();
}

void I8080::_HLT() {
	CountTicks += 7;
	SetFlagStop(true);
}

inline void I8080::_ORA(const uint8_t& value) {
	CountTicks += 4;


	A = A | value;

	AuxiliaryCarry = 0;
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
	C = Memory[PC + 1];
	B = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_D_imm16() {
	CountTicks += 10;
	E = Memory[PC + 1];
	D = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_H_imm16() {
	CountTicks += 10;
	L = Memory[PC + 1];
	H = Memory[PC + 2];
	IncrementPC(3);
}

void I8080::_LXI_SP_imm16() {
	CountTicks += 10;
	unsigned int sp_l = Memory[PC + 1];
	unsigned int sp_h = Memory[PC + 2];
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
	L = Memory[Memory[PC + 2] * 256 + Memory[PC + 1]];
	H = Memory[Memory[PC + 2] * 256 + Memory[PC + 1] + 1];
	IncrementPC(3);
}
void I8080::_LDA_addr16() {
	CountTicks += 16;
	A = Memory[Memory[PC + 2] * 256 + Memory[PC + 1]];
	IncrementPC(3);
}

void I8080::_JMP() {
	CountTicks += 10;
	unsigned int l_t = Memory[PC + 1];
	unsigned int h_t = Memory[PC + 2];
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
	if (Paruty == 1)
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
inline void I8080::_INCREMENT(uint8_t& value) {
	CountTicks += 5;

	value++;
	_SetFlagSign(value);
	_SetFlagParuty(value);
	_SetFlagZero(value);

	AuxiliaryCarry = ((value & 0b00001111) == 0);


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

	AuxiliaryCarry = ((value & 0b00001111) != 0b00001111);

	IncrementPC();
}

inline void I8080::_DCX(uint8_t& pair_element1, uint8_t& pair_element2) {
	CountTicks += 5;
	uint32_t first = pair_element1 * 256 + pair_element2;
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
	uint8_t f = SP / 256, s = SP % 256;
	_DCX(f, s);
	SP = f * 256 + s;
}

inline void I8080::_DAD(const uint8_t& pair_element1, const uint8_t& pair_element2) {
	CountTicks += 10;

	uint32_t value = (uint16_t)pair_element1 * 256 + (uint16_t)pair_element2;
	uint32_t HL =(uint16_t)H * 256 + (uint16_t)L;

	Carry = ((HL + value) >> 16) & 1;

	HL += value;

	H = HL / 256;
	L = HL % 256;

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
inline void I8080::_COMPARE(const uint8_t& value) {
	CountTicks += 4;
	
	AuxiliaryCarry = ((A & 0b00001111) - (value & 0b00001111)) >= 0;
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

inline void I8080::_CALL() {
	CountTicks += 17;

	SP = SP - 2;

	SetSP_nextAdress(PC + 3);

	SetVisitedMemoryFromPC(3);
	SetPC(Memory[PC + 1] + Memory[PC + 2] * 256);
}

void I8080::_CNZ() {
	if (Zero == 0)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}

void I8080::_CNC() {
	if (Carry == 0)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CPO() {
	if (Paruty == 0)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CP() {
	if (Sign == 0)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CZ() {
	if (Zero == 1)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CC() {
	if (Carry == 1)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CPE() {
	if (Paruty == 1)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::_CM() {
	if (Sign == 1)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}

inline void I8080::_ANA(const uint8_t& value) {
	CountTicks += 4;

	Carry = 0;
	AuxiliaryCarry = ((A | value) & 0b00001000) != 0;

	A = A & value;

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

inline void I8080::_ADD(const uint8_t& value) {
	CountTicks += 4;

	AuxiliaryCarry = (A&0b00001111) + (value&0b00001111) > 0b00001111;
	Carry = (uint16_t(A) + uint16_t(value) > 0x00ff);

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

	bool C_old = Carry;
	AuxiliaryCarry = ((A & 0b00001111) + (value & 0b00001111) + Carry) > 0b00001111;
	Carry = uint16_t(A) + uint16_t(value) + Carry > 0x00FF;

	A += value;
	A += C_old;

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

uint8_t I8080::GetRegisterFlags() {
	uint8_t FlagRegister = 0;
	FlagRegister |= Sign << 7;
	FlagRegister |= Zero << 6;
	FlagRegister |= AuxiliaryCarry << 4;
	FlagRegister |= Paruty << 2;
	FlagRegister |= 1 << 1;
	FlagRegister |= Carry << 0;

	return FlagRegister;
}


inline void I8080::HiSetSP_nextAdress(const uint16_t& next_adress) {
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {SP,Memory[SP]},{uint16_t(SP + 1),Memory[uint16_t(SP + 1)]} });

	Memory[SP] = (next_adress & 0x00ff);	  // next.low
	Memory[uint16_t(SP + 1)] = (next_adress & 0xff00) >> 8; // next.high
}

inline void I8080::Hi_CALL() {
	CountTicks += 17;

	SP = SP - 2;

	HiSetSP_nextAdress(PC + 3);

	SetVisitedMemoryFromPC(3);
	SetPC(Memory[PC + 1] + Memory[PC + 2] * 256);
}
void I8080::Hi_STAX_B() {
	CountTicks += 7;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {B * 256 + C,Memory[B * 256 + C]} });
	Memory[B * 256 + C] = A;
	IncrementPC();
}
void I8080::Hi_STAX_D() {
	CountTicks += 7;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({{ D * 256 + E,Memory[D * 256 + E] }});
	Memory[D * 256 + E] = A;
	IncrementPC();
}
void I8080::Hi_SHLD_addr16() {
	CountTicks += 16;

	unsigned int l = Memory[PC + 1];
	unsigned int h = Memory[PC + 2];

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {h * 256 + l,Memory[h * 256 + l]},  {h * 256 + l + 1,Memory[h * 256 + l + 1]} });

	Memory[h * 256 + l] = L;
	Memory[h * 256 + l + 1] = H;

	IncrementPC(3);
}
void I8080::Hi_STA_addr16() {
	CountTicks += 13;
	unsigned int l = Memory[PC + 1];
	unsigned int h = Memory[PC + 2];

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {h * 256 + l,Memory[h * 256 + l]} });

	Memory[h * 256 + l] = A;


	IncrementPC(3);
}

void I8080::Hi_CNZ() {
	if (Zero == 0)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CNC() {
	if (Carry == 0)
		_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CPO() {
	if (Paruty == 0)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CP() {
	if (Sign == 0)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CZ() {
	if (Zero == 1)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CC() {
	if (Carry == 1)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CPE() {
	if (Paruty == 1)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}
void I8080::Hi_CM() {
	if (Sign == 1)
		Hi_CALL();
	else {
		CountTicks += 11;
		IncrementPC(3);
	}
}


inline void I8080::Hi_RST(const uint8_t& N) {
	CountTicks += 11;

	SP = SP - 2;

	HiSetSP_nextAdress(PC + 1);
	SetVisitedMemoryFromPC(1);

	SetPC(uint16_t(N) * 8);

}


void I8080::Hi_RST_0() {
	Hi_RST(0);
}
void I8080::Hi_RST_1() {
	Hi_RST(1);
}
void I8080::Hi_RST_2() {
	Hi_RST(2);
}
void I8080::Hi_RST_3() {
	Hi_RST(3);
}
void I8080::Hi_RST_4() {
	Hi_RST(4);
}
void I8080::Hi_RST_5() {
	Hi_RST(5);
}
void I8080::Hi_RST_6() {
	Hi_RST(6);
}
void I8080::Hi_RST_7() {
	Hi_RST(7);
}



void I8080::Hi_PUSH_B() {
	CountTicks += 11;

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {uint16_t(SP - 1),B},{uint16_t(SP - 2),C} });

	SP--;
	Memory[SP] = B;
	SP--;
	Memory[SP] = C;
	IncrementPC();
}
void I8080::Hi_PUSH_D() {
	CountTicks += 11;

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {uint16_t(SP - 1),D},{uint16_t(SP - 2),E} });

	SP--;
	Memory[SP] = D;
	SP--;
	Memory[SP] = E;
	IncrementPC();
}
void I8080::Hi_PUSH_H() {
	CountTicks += 11;

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {uint16_t(SP - 1),H},{uint16_t(SP - 2),L} });

	SP--;
	Memory[SP] = H;
	SP--;
	Memory[SP] = L;
	IncrementPC();
}
void I8080::Hi_PUSH_PSW() {
	CountTicks += 11;

	uint8_t Flags = GetRegisterFlags();

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {uint16_t(SP - 1),A},{uint16_t(SP - 2),Flags} });

	SP--;
	Memory[SP] = A;
	SP--;
	Memory[SP] = Flags;



	IncrementPC();
}


void I8080::Hi_MOV_M_A() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], A);

}
void I8080::Hi_MOV_M_B() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], B);
}
void I8080::Hi_MOV_M_C() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], C);
}
void I8080::Hi_MOV_M_D() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], D);
}
void I8080::Hi_MOV_M_E() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], E);
}
void I8080::Hi_MOV_M_H() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], H);
}
void I8080::Hi_MOV_M_L() {
	CountTicks += 2;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MOV(Memory[GetAdressHL()], L);
}

void I8080::Hi_MVI_M_imm8() {
	CountTicks += 3;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_MVI(Memory[GetAdressHL()]);
}

void I8080::Hi_XTHL() {
	CountTicks += 18;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {uint16_t(SP),Memory[SP]},{uint16_t(SP + 1),Memory[SP + 1]} });

	swap(H, Memory[SP + 1]);
	swap(L, Memory[SP]);


	IncrementPC();
}

void I8080::Hi_INR_M() {
	CountTicks += 5;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_INCREMENT(Memory[GetAdressHL()]);
}
void I8080::Hi_DCR_M() {
	CountTicks += 5;
	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_changedMemory({ {GetAdressHL(),Memory[GetAdressHL()]} });
	_DECREMENT(Memory[GetAdressHL()]);
}

void I8080::Hi_INPUT() {

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

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_MomentoPort(External_Peripherals[Memory[PC + 1]]->SaveState());

	A = External_Peripherals[Memory[PC + 1]]->GetOutput();
	CountTicks += 10;
	IncrementPC(2);
}
void I8080::Hi_OUTPUT() {
	CountTicks += 10;

	dynamic_cast<I8080_Momento*>(ptr_To_Last_Momento.get())->Set_MomentoPort(External_Peripherals[Memory[PC + 1]]->SaveState());

	External_Peripherals[Memory[PC + 1]]->SetInput(A);
	IncrementPC(2);
}



inline void I8080::ALU(const uint8_t& opcode) {
	(this->*instructions[opcode])();
}

inline void I8080::ALU_WithHistorySaving(const uint8_t& opcode) {
	(this->*instructionsWithHistory[opcode])();
}

void I8080::InitInstructions() {


#ifdef WITH_DEBUG_OUTPUT
	cout << "init instructions" << endl;
#endif
	instructions =
	{
	  &I8080::_NOP,     &I8080::_LXI_B_imm16,  &I8080::_STAX_B,      &I8080::_INX_B,   &I8080::_INR_B,   &I8080::_DCR_B,   &I8080::_MVI_B_imm8, &I8080::_RLC,     &I8080::_NOP,     &I8080::_DAD_B,   &I8080::_LDAX_B,      &I8080::_DCX_B,   &I8080::_INR_C,   &I8080::_DCR_C,   &I8080::_MVI_C_imm8, &I8080::_RRC,
	  &I8080::_NOP,     &I8080::_LXI_D_imm16,  &I8080::_STAX_D,      &I8080::_INX_D,   &I8080::_INR_D,   &I8080::_DCR_D,   &I8080::_MVI_D_imm8, &I8080::_RAL,     &I8080::_NOP,     &I8080::_DAD_D,   &I8080::_LDAX_D,      &I8080::_DCX_D,   &I8080::_INR_E,   &I8080::_DCR_E,   &I8080::_MVI_E_imm8, &I8080::_RAR,
	  &I8080::_NOP,     &I8080::_LXI_H_imm16,  &I8080::_SHLD_addr16, &I8080::_INX_H,   &I8080::_INR_H,   &I8080::_DCR_H,   &I8080::_MVI_H_imm8, &I8080::_DAA,     &I8080::_NOP,     &I8080::_DAD_H,   &I8080::_LHLD_addr16, &I8080::_DCX_H,   &I8080::_INR_L,   &I8080::_DCR_L,   &I8080::_MVI_L_imm8, &I8080::_CMA,
	  &I8080::_NOP,     &I8080::_LXI_SP_imm16, &I8080::_STA_addr16,  &I8080::_INX_SP,  &I8080::_INR_M,   &I8080::_DCR_M,   &I8080::_MVI_M_imm8, &I8080::_STC,     &I8080::_NOP,     &I8080::_DAD_SP,  &I8080::_LDA_addr16,  &I8080::_DCX_SP,  &I8080::_INR_A,   &I8080::_DCR_A,   &I8080::_MVI_A_imm8, &I8080::_CMC,
	  &I8080::_MOV_B_B, &I8080::_MOV_B_C,      &I8080::_MOV_B_D,     &I8080::_MOV_B_E, &I8080::_MOV_B_H, &I8080::_MOV_B_L, &I8080::_MOV_B_M,    &I8080::_MOV_B_A, &I8080::_MOV_C_B, &I8080::_MOV_C_C, &I8080::_MOV_C_D,     &I8080::_MOV_C_E, &I8080::_MOV_C_H, &I8080::_MOV_C_L, &I8080::_MOV_C_M,    &I8080::_MOV_C_A,
	  &I8080::_MOV_D_B, &I8080::_MOV_D_C,      &I8080::_MOV_D_D,     &I8080::_MOV_D_E, &I8080::_MOV_D_H, &I8080::_MOV_D_L, &I8080::_MOV_D_M,    &I8080::_MOV_D_A, &I8080::_MOV_E_B, &I8080::_MOV_E_C, &I8080::_MOV_E_D,     &I8080::_MOV_E_E, &I8080::_MOV_E_H, &I8080::_MOV_E_L, &I8080::_MOV_E_M,    &I8080::_MOV_E_A,
	  &I8080::_MOV_H_B, &I8080::_MOV_H_C,      &I8080::_MOV_H_D,     &I8080::_MOV_H_E, &I8080::_MOV_H_H, &I8080::_MOV_H_L, &I8080::_MOV_H_M,    &I8080::_MOV_H_A, &I8080::_MOV_L_B, &I8080::_MOV_L_C, &I8080::_MOV_L_D,     &I8080::_MOV_L_E, &I8080::_MOV_L_H, &I8080::_MOV_L_L, &I8080::_MOV_L_M,    &I8080::_MOV_L_A,
	  &I8080::_MOV_M_B, &I8080::_MOV_M_C,      &I8080::_MOV_M_D,     &I8080::_MOV_M_E, &I8080::_MOV_M_H, &I8080::_MOV_M_L, &I8080::_HLT,        &I8080::_MOV_M_A, &I8080::_MOV_A_B, &I8080::_MOV_A_C, &I8080::_MOV_A_D,     &I8080::_MOV_A_E, &I8080::_MOV_A_H, &I8080::_MOV_A_L, &I8080::_MOV_A_M,    &I8080::_MOV_A_A,
	  &I8080::_ADD_B,   &I8080::_ADD_C,        &I8080::_ADD_D,       &I8080::_ADD_E,   &I8080::_ADD_H,   &I8080::_ADD_L,   &I8080::_ADD_M,      &I8080::_ADD_A,   &I8080::_ADC_B,   &I8080::_ADC_C,   &I8080::_ADC_D,       &I8080::_ADC_E,   &I8080::_ADC_H,   &I8080::_ADC_L,   &I8080::_ADC_M,      &I8080::_ADC_A,
	  &I8080::_SUB_B,   &I8080::_SUB_C,        &I8080::_SUB_D,       &I8080::_SUB_E,   &I8080::_SUB_H,   &I8080::_SUB_L,   &I8080::_SUB_M,      &I8080::_SUB_A,   &I8080::_SBB_B,   &I8080::_SBB_C,   &I8080::_SBB_D,       &I8080::_SBB_E,   &I8080::_SBB_H,   &I8080::_SBB_L,   &I8080::_SBB_M,      &I8080::_SBB_A,
	  &I8080::_ANA_B,   &I8080::_ANA_C,        &I8080::_ANA_D,       &I8080::_ANA_E,   &I8080::_ANA_H,   &I8080::_ANA_L,   &I8080::_ANA_M,      &I8080::_ANA_A,   &I8080::_XRA_B,   &I8080::_XRA_C,   &I8080::_XRA_D,       &I8080::_XRA_E,   &I8080::_XRA_H,   &I8080::_XRA_L,   &I8080::_XRA_M,      &I8080::_XRA_A,
	  &I8080::_ORA_B,   &I8080::_ORA_C,        &I8080::_ORA_D,       &I8080::_ORA_E,   &I8080::_ORA_H,   &I8080::_ORA_L,   &I8080::_ORA_M,      &I8080::_ORA_A,   &I8080::_CMP_B,   &I8080::_CMP_C,   &I8080::_CMP_D,       &I8080::_CMP_E,   &I8080::_CMP_H,   &I8080::_CMP_L,   &I8080::_CMP_M,      &I8080::_CMP_A,
	  &I8080::_RNZ,     &I8080::_POP_B,        &I8080::_JNZ,         &I8080::_JMP,     &I8080::_CNZ,     &I8080::_PUSH_B,  &I8080::_ADI_imm8,   &I8080::_RST_0,   &I8080::_RZ,      &I8080::_RET,     &I8080::_JZ,          &I8080::_JMP,     &I8080::_CZ,      &I8080::_CALL,    &I8080::_ACI_imm8,   &I8080::_RST_1,
	  &I8080::_RNC,     &I8080::_POP_D,        &I8080::_JNC,         &I8080::_OUTPUT,  &I8080::_CNC,     &I8080::_PUSH_D,  &I8080::_SUI_imm8,   &I8080::_RST_2,   &I8080::_RC,      &I8080::_RET,     &I8080::_JC,          &I8080::_INPUT,   &I8080::_CC,      &I8080::_CALL,    &I8080::_SBI_imm8,   &I8080::_RST_3,
	  &I8080::_RPO,     &I8080::_POP_H,        &I8080::_JPO,         &I8080::_XTHL,    &I8080::_CPO,     &I8080::_PUSH_H,  &I8080::_ANI_imm8,   &I8080::_RST_4,   &I8080::_RPE,     &I8080::_PCHL,    &I8080::_JPE,         &I8080::_XCHG,    &I8080::_CPE,     &I8080::_CALL,    &I8080::_XRI_imm8,   &I8080::_RST_5,
	  &I8080::_RP,      &I8080::_POP_PSW,      &I8080::_JP,          &I8080::_DI,      &I8080::_CP,      &I8080::_PUSH_PSW,&I8080::_ORI_imm8,   &I8080::_RST_6,   &I8080::_RM,      &I8080::_SPHL,    &I8080::_JM,          &I8080::_EI,      &I8080::_CM,      &I8080::_CALL,    &I8080::_CPI_imm8,   &I8080::_RST_7
	};
}


void I8080::InitInstructionsWithHistory() {


#ifdef WITH_DEBUG_OUTPUT
	cout << "init instructions with history" << endl;
#endif
	
	instructionsWithHistory =
	{
	  &I8080::_NOP,      &I8080::_LXI_B_imm16,  &I8080::Hi_STAX_B,     &I8080::_INX_B,    &I8080::_INR_B,    &I8080::_DCR_B,     &I8080::_MVI_B_imm8,  &I8080::_RLC,      &I8080::_NOP,     &I8080::_DAD_B,   &I8080::_LDAX_B,      &I8080::_DCX_B,   &I8080::_INR_C,   &I8080::_DCR_C,   &I8080::_MVI_C_imm8, &I8080::_RRC,
	  &I8080::_NOP,      &I8080::_LXI_D_imm16,  &I8080::Hi_STAX_D,     &I8080::_INX_D,    &I8080::_INR_D,    &I8080::_DCR_D,     &I8080::_MVI_D_imm8,  &I8080::_RAL,      &I8080::_NOP,     &I8080::_DAD_D,   &I8080::_LDAX_D,      &I8080::_DCX_D,   &I8080::_INR_E,   &I8080::_DCR_E,   &I8080::_MVI_E_imm8, &I8080::_RAR,
	  &I8080::_NOP,      &I8080::_LXI_H_imm16,  &I8080::Hi_SHLD_addr16,&I8080::_INX_H,    &I8080::_INR_H,    &I8080::_DCR_H,     &I8080::_MVI_H_imm8,  &I8080::_DAA,      &I8080::_NOP,     &I8080::_DAD_H,   &I8080::_LHLD_addr16, &I8080::_DCX_H,   &I8080::_INR_L,   &I8080::_DCR_L,   &I8080::_MVI_L_imm8, &I8080::_CMA,
	  &I8080::_NOP,      &I8080::_LXI_SP_imm16, &I8080::Hi_STA_addr16, &I8080::_INX_SP,   &I8080::Hi_INR_M,  &I8080::Hi_DCR_M,   &I8080::Hi_MVI_M_imm8,&I8080::_STC,      &I8080::_NOP,     &I8080::_DAD_SP,  &I8080::_LDA_addr16,  &I8080::_DCX_SP,  &I8080::_INR_A,   &I8080::_DCR_A,   &I8080::_MVI_A_imm8, &I8080::_CMC,
	  &I8080::_MOV_B_B,  &I8080::_MOV_B_C,      &I8080::_MOV_B_D,      &I8080::_MOV_B_E,  &I8080::_MOV_B_H,  &I8080::_MOV_B_L,   &I8080::_MOV_B_M,     &I8080::_MOV_B_A,  &I8080::_MOV_C_B, &I8080::_MOV_C_C, &I8080::_MOV_C_D,     &I8080::_MOV_C_E, &I8080::_MOV_C_H, &I8080::_MOV_C_L, &I8080::_MOV_C_M,    &I8080::_MOV_C_A,
	  &I8080::_MOV_D_B,  &I8080::_MOV_D_C,      &I8080::_MOV_D_D,      &I8080::_MOV_D_E,  &I8080::_MOV_D_H,  &I8080::_MOV_D_L,   &I8080::_MOV_D_M,     &I8080::_MOV_D_A,  &I8080::_MOV_E_B, &I8080::_MOV_E_C, &I8080::_MOV_E_D,     &I8080::_MOV_E_E, &I8080::_MOV_E_H, &I8080::_MOV_E_L, &I8080::_MOV_E_M,    &I8080::_MOV_E_A,
	  &I8080::_MOV_H_B,  &I8080::_MOV_H_C,      &I8080::_MOV_H_D,      &I8080::_MOV_H_E,  &I8080::_MOV_H_H,  &I8080::_MOV_H_L,   &I8080::_MOV_H_M,     &I8080::_MOV_H_A,  &I8080::_MOV_L_B, &I8080::_MOV_L_C, &I8080::_MOV_L_D,     &I8080::_MOV_L_E, &I8080::_MOV_L_H, &I8080::_MOV_L_L, &I8080::_MOV_L_M,    &I8080::_MOV_L_A,
	  &I8080::Hi_MOV_M_B,&I8080::Hi_MOV_M_C,    &I8080::Hi_MOV_M_D,    &I8080::Hi_MOV_M_E,&I8080::Hi_MOV_M_H,&I8080::Hi_MOV_M_L, &I8080::_HLT,         &I8080::Hi_MOV_M_A,&I8080::_MOV_A_B, &I8080::_MOV_A_C, &I8080::_MOV_A_D,     &I8080::_MOV_A_E, &I8080::_MOV_A_H, &I8080::_MOV_A_L, &I8080::_MOV_A_M,    &I8080::_MOV_A_A,
	  &I8080::_ADD_B,    &I8080::_ADD_C,        &I8080::_ADD_D,        &I8080::_ADD_E,    &I8080::_ADD_H,    &I8080::_ADD_L,     &I8080::_ADD_M,       &I8080::_ADD_A,    &I8080::_ADC_B,   &I8080::_ADC_C,   &I8080::_ADC_D,       &I8080::_ADC_E,   &I8080::_ADC_H,   &I8080::_ADC_L,   &I8080::_ADC_M,      &I8080::_ADC_A,
	  &I8080::_SUB_B,    &I8080::_SUB_C,        &I8080::_SUB_D,        &I8080::_SUB_E,    &I8080::_SUB_H,    &I8080::_SUB_L,     &I8080::_SUB_M,       &I8080::_SUB_A,    &I8080::_SBB_B,   &I8080::_SBB_C,   &I8080::_SBB_D,       &I8080::_SBB_E,   &I8080::_SBB_H,   &I8080::_SBB_L,   &I8080::_SBB_M,      &I8080::_SBB_A,
	  &I8080::_ANA_B,    &I8080::_ANA_C,        &I8080::_ANA_D,        &I8080::_ANA_E,    &I8080::_ANA_H,    &I8080::_ANA_L,     &I8080::_ANA_M,       &I8080::_ANA_A,    &I8080::_XRA_B,   &I8080::_XRA_C,   &I8080::_XRA_D,       &I8080::_XRA_E,   &I8080::_XRA_H,   &I8080::_XRA_L,   &I8080::_XRA_M,      &I8080::_XRA_A,
	  &I8080::_ORA_B,    &I8080::_ORA_C,        &I8080::_ORA_D,        &I8080::_ORA_E,    &I8080::_ORA_H,    &I8080::_ORA_L,     &I8080::_ORA_M,       &I8080::_ORA_A,    &I8080::_CMP_B,   &I8080::_CMP_C,   &I8080::_CMP_D,       &I8080::_CMP_E,   &I8080::_CMP_H,   &I8080::_CMP_L,   &I8080::_CMP_M,      &I8080::_CMP_A,
	  &I8080::_RNZ,      &I8080::_POP_B,        &I8080::_JNZ,          &I8080::_JMP,      &I8080::Hi_CNZ,    &I8080::Hi_PUSH_B,  &I8080::_ADI_imm8,    &I8080::Hi_RST_0,  &I8080::_RZ,      &I8080::_RET,     &I8080::_JZ,          &I8080::_JMP,     &I8080::Hi_CZ,    &I8080::Hi_CALL,  &I8080::_ACI_imm8,   &I8080::Hi_RST_1,
	  &I8080::_RNC,      &I8080::_POP_D,        &I8080::_JNC,          &I8080::Hi_OUTPUT, &I8080::Hi_CNC,    &I8080::Hi_PUSH_D,  &I8080::_SUI_imm8,    &I8080::Hi_RST_2,  &I8080::_RC,      &I8080::_RET,     &I8080::_JC,          &I8080::Hi_INPUT, &I8080::Hi_CC,    &I8080::Hi_CALL,  &I8080::_SBI_imm8,   &I8080::Hi_RST_3,
	  &I8080::_RPO,      &I8080::_POP_H,        &I8080::_JPO,          &I8080::Hi_XTHL,   &I8080::Hi_CPO,    &I8080::Hi_PUSH_H,  &I8080::_ANI_imm8,    &I8080::Hi_RST_4,  &I8080::_RPE,     &I8080::_PCHL,    &I8080::_JPE,         &I8080::_XCHG,    &I8080::Hi_CPE,   &I8080::Hi_CALL,  &I8080::_XRI_imm8,   &I8080::Hi_RST_5,
	  &I8080::_RP,       &I8080::_POP_PSW,      &I8080::_JP,           &I8080::_DI,       &I8080::Hi_CP,     &I8080::Hi_PUSH_PSW,&I8080::_ORI_imm8,    &I8080::Hi_RST_6,  &I8080::_RM,      &I8080::_SPHL,    &I8080::_JM,          &I8080::_EI,      &I8080::Hi_CM,    &I8080::Hi_CALL,  &I8080::_CPI_imm8,   &I8080::Hi_RST_7
	};
}


