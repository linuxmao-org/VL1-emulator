#ifndef __VL1EDIT_H__
#define __VL1EDIT_H__


#include "VL1.h"


#define kVersion  1000


class CVL1Edit : public CVL1
{
public:
	CVL1Edit(audioMasterCallback audioMaster);
	~CVL1Edit();

	virtual void setParameter(long index, float value);
	inline virtual void setParameterEditor(long index, float value) 
		{ if (editor) ((AEffGUIEditor*)editor)->setParameter(index,value); }

	virtual bool getEffectName(char *pText);
	virtual bool getProductString(char *pText);
	virtual bool getVendorString(char *pText);
	virtual long getVendorVersion() { return kVersion; }
};

#endif // __VL1EDIT_H__
