#ifndef I8086_H
#define I8086_H

#include "Emulator/Processors/Processor.h"
#include <cstdint>
#include <array>

class I8086 : public Processor
{
public:
	I8086();
	~I8086();

    void RemoveAllBreakPoints() override;                    // TODO:
    void EraseMemory() override;                             // TODO:
    void Reset() override;                                   // TODO:
    void LoadMemory(const std::vector<uint8_t>& data, const bool& isBinary) override;     // TODO:
    void NextStep() override;                                // TODO:

    Momento* SaveState() override;
    void     RestoreState(Momento* momento) override;

private:

};

#endif