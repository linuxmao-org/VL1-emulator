#ifndef __VL1EDIT_H__
#define __VL1EDIT_H__


#include "VL1.hpp"


#define kVersion  1000


class VL1Edit : public CVL1
{
public:
	VL1Edit(audioMasterCallback audioMaster);
	~VL1Edit();

	virtual void setParameter(long index, float value);

	virtual bool getEffectName(char *pText);
	virtual bool getProductString(char *pText);
	virtual bool getVendorString(char *pText);
	virtual long getVendorVersion() { return kVersion; }
};

#endif // __VL1EDIT_H__
