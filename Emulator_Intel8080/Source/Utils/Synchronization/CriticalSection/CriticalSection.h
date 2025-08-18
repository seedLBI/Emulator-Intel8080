#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <windows.h>

class CriticalSection
{
public:
    CriticalSection();
    ~CriticalSection();

    void Enter();
    void Leave();

private:
    CRITICAL_SECTION cs_ID;
};


#endif CRITICAL_SECTION_H