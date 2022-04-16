#include <windows.h>

class CriticalSection
{
private:
    /* data */
    CRITICAL_SECTION mCriticalSection;

public:
    CriticalSection(/* args */);
    ~CriticalSection();

    void Lock();
    void Unlock();

};

CriticalSection::CriticalSection(/* args */)
{
    InitializeCriticalSectionEx(&mCriticalSection, 0,0);
}

CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&mCriticalSection);
}

void CriticalSection::Lock()
{
    EnterCriticalSection(&mCriticalSection);
}

void CriticalSection::Unlock()
{
    LeaveCriticalSection(&mCriticalSection);
}

class CriticalSectionLock
{

    /* data */
    CriticalSection* mCriticalSection;

public:
    CriticalSectionLock(CriticalSection& criticalSection);
    ~CriticalSectionLock();
};

CriticalSectionLock::CriticalSectionLock(CriticalSection& criticalSection)
{
    mCriticalSection = &criticalSection;
    mCriticalSection->Lock();
}

CriticalSectionLock::~CriticalSectionLock()
{
    mCriticalSection->Unlock();
}