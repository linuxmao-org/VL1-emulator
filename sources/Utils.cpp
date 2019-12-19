/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "Utils.h"
#include <stdio.h>
#include <stdarg.h>


#ifndef NDEBUG
#ifdef _WIN32
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
#else
int TRACE(const char *lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf = vfprintf(stderr, lpszFormat, args);

	va_end(args);

	return nBuf;
}
#endif
#endif


void ReplaceCommaWithDot(char *str)
{
	for (char c; (c = *str); ++str)
	{
		if (c == ',')
			*str = '.';
	}
}
