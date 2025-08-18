#include "I8080.Momento.h"




uint8_t I8080_Momento::Get_opcode() const {
    return opcode;
}
uint8_t I8080_Momento::Get_data_first_byte() const {
    return data_first_byte;
}
uint8_t I8080_Momento::Get_data_second_byte() const {
    return data_second_byte;
}
uint8_t I8080_Momento::Get_A() const {
    return A;
}
uint8_t I8080_Momento::Get_B() const {
    return B;
}
uint8_t I8080_Momento::Get_C() const {
    return C;
}
uint8_t I8080_Momento::Get_D() const {
    return D;
}
uint8_t I8080_Momento::Get_E() const {
    return E;
}
uint8_t I8080_Momento::Get_H() const {
    return H;
}
uint8_t I8080_Momento::Get_L() const {
    return L;
}
uint16_t I8080_Momento::Get_PC() const {
    return PC;
}
uint16_t I8080_Momento::Get_SP() const {
    return SP;
}
uint64_t I8080_Momento::Get_CountTicks() const {
    return CountTicks;
}
bool I8080_Momento::Get_Sign() const {
    return Sign;
}
bool I8080_Momento::Get_Zero() const {
    return Zero;
}
bool I8080_Momento::Get_Parity() const {
    return Parity;
}
bool I8080_Momento::Get_Carry() const {
    return Carry;
}
bool I8080_Momento::Get_AuxiliaryCarry() const {
    return AuxiliaryCarry;
}
bool I8080_Momento::Get_InterruptEnabled() const {
    return InterruptEnabled;
}
bool I8080_Momento::Get_Flag_Stop() const {
    return Flag_Stop;
}
bool I8080_Momento::Get_Flag_Waiting_Input() const {
    return Flag_Waiting_Input;
}
bool I8080_Momento::Get_Flag_GetAnswer() const {
    return Flag_GetAnswer;
}
uint8_t I8080_Momento::Get_Input() const {
    return Input;
}

std::vector<std::pair<uint16_t, uint8_t>> I8080_Momento::Get_changedMemory() const {
    return changedMemory;
}
void I8080_Momento::Set_changedMemory(const std::vector<std::pair<uint16_t, uint8_t>>& newVector) {
    this->changedMemory = newVector;
}

std::shared_ptr<Momento> I8080_Momento::get_MomentoPort() {
    return MomentoPort;
}

void I8080_Momento::Set_MomentoPort(const std::shared_ptr<Momento>& newMomento) {
    MomentoPort = newMomento;
}

I8080_Momento::I8080_Momento(
    const uint8_t& opcode,
    const uint8_t& data_first_byte,
    const uint8_t& data_second_byte,
    const uint8_t& A,
    const uint8_t& B,
    const uint8_t& C,
    const uint8_t& D,
    const uint8_t& E,
    const uint8_t& H,
    const uint8_t& L,
    const uint16_t& PC,
    const uint16_t& SP,
    const bool& Sign,
    const bool& Zero,
    const bool& Parity,
    const bool& Carry,
    const bool& AuxiliaryCarry,
    const bool& InterruptEnabled,
    const bool& Flag_Stop,
    const bool& Flag_Waiting_Input,
    const bool& Flag_GetAnswer,
    const uint8_t& Input,
    const uint64_t& CountTicks,
    const std::vector<std::pair<uint16_t, uint8_t>>& changedMemory,
    const std::shared_ptr<Momento>& MomentoPort) : Momento(-1),
    opcode(opcode),
    data_first_byte(data_first_byte),
    data_second_byte(data_second_byte),
    A(A),
    B(B),
    C(C),
    D(D),
    E(E),
    H(H),
    L(L),
    PC(PC),
    SP(SP),
    Sign(Sign),
    Zero(Zero),
    Parity(Parity),
    Carry(Carry),
    AuxiliaryCarry(AuxiliaryCarry),
    InterruptEnabled(InterruptEnabled),
    Flag_Stop(Flag_Stop),
    Flag_Waiting_Input(Flag_Waiting_Input),
    Flag_GetAnswer(Flag_GetAnswer),
    Input(Input),
    CountTicks(CountTicks),
    changedMemory(changedMemory),
    MomentoPort(MomentoPort)
{

}

I8080_Momento::~I8080_Momento(){

}