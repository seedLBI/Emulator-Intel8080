#ifndef I8080_MOMENTO_H
#define I8080_MOMENTO_H

#include "Emulator/History/Momento.h"
#include <memory>
#include <cstdint>
#include <vector>


class I8080_Momento : public Momento
{
public:
    I8080_Momento(const uint8_t& opcode, const uint8_t& data_first_byte, const uint8_t& data_second_byte,
                  const uint8_t& A, const uint8_t& B, const uint8_t& C, const uint8_t& D, const uint8_t& E,
                  const uint8_t& H, const uint8_t& L, const uint16_t& PC, const uint16_t& SP,
                  const bool& Sign, const bool& Zero, const bool& Parity, const bool& Carry, const bool& AuxiliaryCarry, const bool& InterruptEnabled,
                  const bool& Flag_Stop, const bool& Flag_Waiting_Input, const bool& Flag_GetAnswer, const uint8_t& Input,
                  const uint64_t& CountTicks,
                  const std::vector<std::pair<uint16_t, uint8_t>>& changedMemory,
                  const std::shared_ptr<Momento>& MomentoPort);

	~I8080_Momento();

    uint8_t Get_opcode() const;
    uint8_t Get_data_first_byte() const;
    uint8_t Get_data_second_byte() const;
    uint8_t Get_A() const;
    uint8_t Get_B() const;
    uint8_t Get_C() const;
    uint8_t Get_D() const;
    uint8_t Get_E() const;
    uint8_t Get_H() const;
    uint8_t Get_L() const;

    uint16_t Get_PC() const;
    uint16_t Get_SP() const;

    uint64_t Get_CountTicks() const;

    bool Get_Sign() const;
    bool Get_Zero() const;
    bool Get_Parity() const;
    bool Get_Carry() const;
    bool Get_AuxiliaryCarry() const;
    bool Get_InterruptEnabled() const;

    bool Get_Flag_Stop() const;
    bool Get_Flag_Waiting_Input() const;
    bool Get_Flag_GetAnswer() const;
    uint8_t Get_Input() const;

    std::vector<std::pair<uint16_t, uint8_t>> Get_changedMemory() const;
    void Set_changedMemory(const std::vector<std::pair<uint16_t, uint8_t>>& newVector);

    std::shared_ptr<Momento> get_MomentoPort();
    void Set_MomentoPort(const std::shared_ptr<Momento>& newMomento);

private:
    uint8_t opcode;
    uint8_t data_first_byte, data_second_byte;
    uint8_t A, B, C, D, E, H, L;
    uint16_t PC, SP;
    uint64_t CountTicks;
    bool Sign, Zero, Parity, Carry, AuxiliaryCarry, InterruptEnabled;
    bool Flag_Stop;
    bool Flag_Waiting_Input;
    bool Flag_GetAnswer;
    uint8_t Input;
    std::vector<std::pair<uint16_t, uint8_t>> changedMemory;

    std::shared_ptr<Momento> MomentoPort;
};





#endif // !I8080_MOMENTO_H
