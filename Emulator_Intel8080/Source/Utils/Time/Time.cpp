#include "Time.h"


uint64_t GetCurrentTimestamp() {
    std::time_t result = std::time(nullptr);

    return result;
}