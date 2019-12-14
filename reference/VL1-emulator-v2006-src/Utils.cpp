#include "Utils.h"
#include <stdio.h>


#if WINDOWS
#include <windows.h>
int TRACE(const char *lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	char szBuffer[512];

	nBuf = _vsnprintf(szBuffer, 512, lpszFormat, args);

	// was there an error? was the expanded string too long?
	if (nBuf>=0)
	{
		OutputDebugString(szBuffer);
	}

	va_end(args);

	return nBuf;
}
#endif // WINDOWS


#if MOTIF
int TRACE(const char *lpszFormat, ...)
{
	return sprintf(stderr,lpszFormat);
}
#endif


#if MAC
int TRACE(const char *lpszFormat, ...)
{
	return sprintf(stderr,lpszFormat);
}
#endif


#if BEOS
int TRACE(const char *lpszFormat, ...)
{
	return sprintf(stderr,lpszFormat);
}
#endif


#if SGI
int TRACE(const char *lpszFormat, ...)
{
	return sprintf(stderr,lpszFormat);
}
#endif
