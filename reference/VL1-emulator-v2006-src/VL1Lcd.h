#ifndef __VL1_LCD__
#define __VL1_LCD__


// include VSTGUI
#ifndef __vstgui__
#include "vstgui.h"
#endif


#include "Utils.h"


class VL1Lcd
{
public:
	VL1Lcd();
	~VL1Lcd();

private:
	CMovieBitmap *m_pSharp1;
	CMovieBitmap *m_pSharp2;
	CMovieBitmap *m_pSharp3;
	CMovieBitmap *m_pM;
	CMovieBitmap *m_pK;
	CMovieBitmap *m_pMul;
	CMovieBitmap *m_pDiv;
	CMovieBitmap *m_pAdd;
	CMovieBitmap *m_pSub;
	CMovieBitmap *m_pChar1;
	CMovieBitmap *m_pChar2;
	CMovieBitmap *m_pChar3;
	CMovieBitmap *m_pChar4;
	CMovieBitmap *m_pChar5;
	CMovieBitmap *m_pChar7;
	CMovieBitmap *m_pChar8;
	CMovieBitmap *m_pChar9;
};

#endif // __VL1_LCD__
