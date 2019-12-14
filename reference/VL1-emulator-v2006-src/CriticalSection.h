#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__


#include <Windows.h>


class CCriticalSection
{
public:
	inline CCriticalSection() 
		{ InitializeCriticalSection(&m_cs); }

	inline ~CCriticalSection() 
		{ DeleteCriticalSection(&m_cs); }

	inline void Lock() 
		{ EnterCriticalSection(&m_cs); }

	inline void Unlock() 
		{ LeaveCriticalSection(&m_cs); }

private:
	CRITICAL_SECTION m_cs;
};


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


class CCriticalSectionLock
{
public:
	inline CCriticalSectionLock() : m_pCs(NULL) {}

	inline CCriticalSectionLock(CCriticalSection *pCs) 
		{ m_pCs = pCs; if (m_pCs) m_pCs->Lock(); }

	inline ~CCriticalSectionLock() 
		{ if (m_pCs) m_pCs->Unlock(); }

private:
	CCriticalSection *m_pCs;
};


#endif // __CRITICAL_SECTION_H__
