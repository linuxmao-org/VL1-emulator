#include "VL1Edit.h"
#include "VL1Editor.h"
#include <string.h>

extern bool oome;


CVL1Edit::CVL1Edit(audioMasterCallback audioMaster) :
	CVL1(audioMaster)
{
	editor = new VL1Editor(this);
	if (!editor)
	{
		oome = true;
	}
}


CVL1Edit::~CVL1Edit()
{
	// the editor gets deleted by the AudioEffect base class
}


void CVL1Edit::setParameter(long index, float value)
{
	CVL1::setParameter(index,value);
	setParameterEditor(index,value);
}


bool CVL1Edit::getEffectName(char *pText)
{
	strcpy(pText,"VL-Tone"); // Max 32 chars.
	return true;
}


bool CVL1Edit::getProductString(char *pText)
{
	strcpy(pText,"VL-Tone"); // Max 64 chars.
	return true;
}


bool CVL1Edit::getVendorString(char *pText)
{
	strcpy(pText,"PolyValens"); // Max 64 chars.
	return true;
}
