#ifndef CURRENT_STATE_PROCESSOR_H
#define CURRENT_STATE_PROCESSOR_H

#include <cstdint>


struct CurrentState {
	uint8_t
		* A = nullptr, // main registers
		* B = nullptr,
		* C = nullptr,
		* D = nullptr,
		* E = nullptr,
		* H = nullptr,
		* L = nullptr;

	uint16_t* PC = nullptr, // programm counter
		    * SP = nullptr; // index register

	bool* Sign = nullptr, // flags
		* Zero = nullptr,
		* Parity = nullptr,
		* Carry = nullptr,
		* AuxiliaryCarry = nullptr;

	uint64_t* CountTicks = nullptr;
	uint64_t* CountInstruction = nullptr;

};
struct CurrentStateNotPointer {
	uint8_t
		A = 0, // main registers
		B = 0,
		C = 0,
		D = 0,
		E = 0,
		H = 0,
		L = 0;
	bool Sign = false, // flags
		Zero = false,
		Parity = false,
		Carry = false,
		AuxiliaryCarry = false;

	CurrentStateNotPointer() {

	}

	CurrentStateNotPointer(CurrentState cs) {
		Init(cs);
	}

	void Init(CurrentState cs) {
		if (cs.A != nullptr)
		{
			A = *cs.A;
			B = *cs.B;
			C = *cs.C;
			D = *cs.D;
			E = *cs.E;
			H = *cs.H;
			L = *cs.L;
			Sign = *cs.Sign;
			Carry = *cs.Carry;
			Parity = *cs.Parity;
			Zero = *cs.Zero;
			AuxiliaryCarry = *cs.AuxiliaryCarry;
		}
		else {
			A = 0;
			B = 0;
			C = 0;
			D = 0;
			E = 0;
			H = 0;
			L = 0;
			Sign = 0;
			Carry = 0;
			Parity = 0;
			Zero = 0;
			AuxiliaryCarry = 0;
		}
	}


};




#endif // !CURRENT_STATE_PROCESSOR_H
