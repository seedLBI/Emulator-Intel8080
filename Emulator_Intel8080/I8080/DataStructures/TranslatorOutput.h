#ifndef TRANSLATOR_OUTPUT_H
#define TRANSLATOR_OUTPUT_H

#include "TypeTranslatorError.h"
#include "OpcodeAdressed.h"
#include "VarsDebug.h"
#include <vector>

struct TranslatorOutput {
    std::vector<OpcodeAdressed>                   Opcodes;
    std::vector<std::pair<std::string, uint16_t>> Markers;
    std::vector<VarsDebug>                        Vars;
    std::vector<std::pair<std::string, uint16_t>> Consts;
    int LineError = 0;
    TypeTranslatorError Error = TypeTranslatorError::NOTHING;

    void Clear() {
        Opcodes.clear();
        Markers.clear();
        Vars.clear();
        Consts.clear();
        LineError = 0;
        Error = TypeTranslatorError::NOTHING;
    }
};


#endif // !TRANSLATOR_OUTPUT_H
