#include "CriticalSection.h"

void CriticalSection::Enter() {
    EnterCriticalSection(&cs_ID);
}
void CriticalSection::Leave() {
    LeaveCriticalSection(&cs_ID);
}

CriticalSection::CriticalSection() {
    InitializeCriticalSection(&cs_ID);
}

CriticalSection::~CriticalSection() {
    DeleteCriticalSection(&cs_ID);
}