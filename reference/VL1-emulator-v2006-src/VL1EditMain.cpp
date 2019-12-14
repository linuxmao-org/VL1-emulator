#ifndef __VL1EDIT_H__
#include "VL1Edit.h"
#endif

#define DEBUG 0

bool oome = false;

#if MAC
#pragma export on
#endif

//------------------------------------------------------------------------
// Prototype of the export function main
//------------------------------------------------------------------------
#if BEOS
#define main main_plugin
extern "C" __declspec(dllexport) AEffect *main_plugin (audioMasterCallback audioMaster);

#elif MACX
#define main main_macho
extern "C" AEffect *main_macho (audioMasterCallback audioMaster);

#else
AEffect *main (audioMasterCallback audioMaster);
#endif

//------------------------------------------------------------------------
AEffect *main (audioMasterCallback audioMaster)
{
	// Get VST Version
	if (!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
	{
		#if DEBUG
		DebugStr("\pVstPlugIn: old vst version");
		#endif
		return 0;  // old version
	}

	// Create the AudioEffect
	CVL1Edit *pEffect = new CVL1Edit(audioMaster);
	if (!pEffect)
		return 0;
	
	// Check if no problem in constructor of VL1Edit
	if (oome)
	{
		delete pEffect;
		return 0;
	}
	return pEffect->getAeffect();
}


#if MAC
#pragma export off
#endif

//------------------------------------------------------------------------
#if WIN32
#include <windows.h>
void* hInstance;
BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	hInstance = hInst;
	return 1;
}
#endif
