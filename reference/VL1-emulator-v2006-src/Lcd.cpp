#include "Lcd.h"
#include "VL1.h"
#include "GlobalData.h"

#include <stdio.h>
#include <math.h>


#define kLcdX  243
#define kLcdY  32
#define kCol1  1
#define kRow1  2
#define kRow2  11
#define kDeltaChar  14


enum 
{
	kDotId = 188,
	kDotX = 10,
	kDotY = 16,

	kSharp1Id = 189,
	kSharp1X = kLcdX+40,
	kSharp1Y = kLcdY+kRow1,
	
	kSharp2Id = 190,
	kSharp2X = kLcdX+82,
	kSharp2Y = kLcdY+kRow1,
	
	kSharp3Id = 191,
	kSharp3X = kLcdX+122,
	kSharp3Y = kLcdY+kRow1,
	
	kAddId = 192,
	kAddX = kLcdX+110,
	kAddY = kLcdY+kRow1,
	
	kSubId = 193,
	kSubX = kLcdX+100,
	kSubY = kLcdY+kRow1,
	
	kMulId = 194,
	kMulX = kLcdX+89,
	kMulY = kLcdY+kRow1,
	
	kDivId = 195,
	kDivX = kLcdX+69,
	kDivY = kLcdY+kRow1,
	
	kMId = 196,
	kMX = kLcdX+47,
	kMY = kLcdY+kRow1,
	
	kKId = 197,
	kKX = kLcdX+58,
	kKY = kLcdY+kRow1,

	kEId = 198,
	kEX = kLcdX+5,
	kEY = kLcdY+kRow1,

	kCharsId = 187,
	kChar1X = kLcdX+kCol1,
	kChar1Y = kLcdY+kRow2,
	kChar2X = kChar1X+kDeltaChar,
	kChar2Y = kLcdY+kRow2,
	kChar3X = kChar2X+kDeltaChar,
	kChar3Y = kLcdY+kRow2,
	kChar4X = kChar3X+kDeltaChar,
	kChar4Y = kLcdY+kRow2,
	kChar5X = kChar4X+kDeltaChar,
	kChar5Y = kLcdY+kRow2,
	kChar6X = kChar5X+kDeltaChar,
	kChar6Y = kLcdY+kRow2,
	kChar7X = kChar6X+kDeltaChar,
	kChar7Y = kLcdY+kRow2,
	kChar8X = kChar7X+kDeltaChar,
	kChar8Y = kLcdY+kRow2,
	kChar9X = kChar8X+kDeltaChar,
	kChar9Y = kLcdY+kRow2,
};


#if MOTIF
// resource for MOTIF (format XPM)
#include "dot.xpm"
#include "sharp1.xpm"
#include "sharp2.xpm"
#include "sharp3.xpm"
#include "add.xpm"
#include "sub.xpm"
#include "mul.xpm"
#include "div.xpm"
#include "m.xpm"
#include "k.xpm"
#include "e.xpm"

CResTable xpmResources = 
{
	{ kChars, chars },
	{ kSharp1, sharp1 },
	{ kSharp2, sharp2 },
	{ kSharp3, sharp3 },
	{ kDot, dot },
	{ kAdd, add },
	{ kSub, sub },
	{ kDiv, div },
	{ kMul, mul },
	{ kK, k },
	{ kM, m },
	{ kE, e },
	{ 0, 0}
};
#endif


const char DigitToChar[10] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};


CLcd::CLcd()
{
	Initialize();
}


CLcd::CLcd(CControlListener *pListener, VSTGUI::CFrame *pFrame)
{
	Initialize();
	Open(pListener,pFrame);
}


CLcd::~CLcd()
{
	Close();
}


void CLcd::Initialize()
{
	m_bOpen = FALSE;
	m_pE = NULL;
	m_pM = NULL;
	m_pK = NULL;
	m_pMul = NULL;
	m_pDiv = NULL;
	m_pAdd = NULL;
	m_pSub = NULL;
	memset(m_pSharp,0,kLcdMaxSharp*sizeof(m_pSharp[0]));
	memset(m_pChars,0,kLcdMaxChar*sizeof(m_pChars[0]));
	memset(m_pDot,0,kLcdMaxDot*sizeof(m_pDot[0]));
}


BOOL CLcd::AddChar(int id, int idBmp, int x, int y, int nBmp, CMovieBitmap **ppControl, CControlListener *pListener, VSTGUI::CFrame *pFrame)
{
	if ((!ppControl) || (!pListener) || (!pFrame)) return FALSE;
	CBitmap *hBmp = new CBitmap(idBmp);
	if (!hBmp) return FALSE;
	int h = hBmp->getHeight()/nBmp;
	*ppControl = new CMovieBitmap(CRect(x,y,x+hBmp->getWidth(),y+h),pListener,id,nBmp,h,hBmp,CPoint(0,0));
	if (*ppControl) pFrame->addView(*ppControl);
	hBmp->forget();
	return *ppControl!=NULL;
}


long CLcd::Open(CControlListener *pListener, VSTGUI::CFrame *pFrame)
{
	AddChar(kChar1,kCharsId,kChar1X,kChar1Y,16,&m_pChars[0],pListener,pFrame);
	AddChar(kChar2,kCharsId,kChar2X,kChar2Y,16,&m_pChars[1],pListener,pFrame);
	AddChar(kChar3,kCharsId,kChar3X,kChar3Y,16,&m_pChars[2],pListener,pFrame);
	AddChar(kChar4,kCharsId,kChar4X,kChar4Y,16,&m_pChars[3],pListener,pFrame);
	AddChar(kChar5,kCharsId,kChar5X,kChar5Y,16,&m_pChars[4],pListener,pFrame);
	AddChar(kChar6,kCharsId,kChar6X,kChar6Y,16,&m_pChars[5],pListener,pFrame);
	AddChar(kChar7,kCharsId,kChar7X,kChar7Y,16,&m_pChars[6],pListener,pFrame);
	AddChar(kChar8,kCharsId,kChar8X,kChar8Y,16,&m_pChars[7],pListener,pFrame);
	AddChar(kChar9,kCharsId,kChar9X,kChar9Y,16,&m_pChars[8],pListener,pFrame);
	AddChar(kDot1,kDotId,kChar2X+kDotX,kChar2Y+kDotY,2,&m_pDot[0],pListener,pFrame);
	AddChar(kDot2,kDotId,kChar3X+kDotX,kChar3Y+kDotY,2,&m_pDot[1],pListener,pFrame);
	AddChar(kDot3,kDotId,kChar4X+kDotX,kChar4Y+kDotY,2,&m_pDot[2],pListener,pFrame);
	AddChar(kDot4,kDotId,kChar5X+kDotX,kChar5Y+kDotY,2,&m_pDot[3],pListener,pFrame);
	AddChar(kDot5,kDotId,kChar6X+kDotX,kChar6Y+kDotY,2,&m_pDot[4],pListener,pFrame);
	AddChar(kDot6,kDotId,kChar7X+kDotX,kChar7Y+kDotY,2,&m_pDot[5],pListener,pFrame);
	AddChar(kDot7,kDotId,kChar8X+kDotX,kChar8Y+kDotY,2,&m_pDot[6],pListener,pFrame);
	AddChar(kDot8,kDotId,kChar9X+kDotX,kChar9Y+kDotY,2,&m_pDot[7],pListener,pFrame);
	AddChar(kAdd,kAddId,kAddX,kAddY,2,&m_pAdd,pListener,pFrame);
	AddChar(kSub,kSubId,kSubX,kSubY,2,&m_pSub,pListener,pFrame);
	AddChar(kMul,kMulId,kMulX,kMulY,2,&m_pMul,pListener,pFrame);
	AddChar(kDiv,kDivId,kDivX,kDivY,2,&m_pDiv,pListener,pFrame);
	AddChar(kSharp1,kSharp1Id,kSharp1X,kSharp1Y,2,&m_pSharp[0],pListener,pFrame);
	AddChar(kSharp2,kSharp2Id,kSharp2X,kSharp2Y,2,&m_pSharp[1],pListener,pFrame);
	AddChar(kSharp3,kSharp3Id,kSharp3X,kSharp3Y,2,&m_pSharp[2],pListener,pFrame);
	AddChar(kM,kMId,kMX,kMY,2,&m_pM,pListener,pFrame);
	AddChar(kK,kKId,kKX,kKY,2,&m_pK,pListener,pFrame);
	AddChar(kErr,kEId,kEX,kEY,2,&m_pE,pListener,pFrame);
	m_bOpen = TRUE;
	return true;
}


void CLcd::Close()
{
	Initialize();
}


float CLcd::MapChar(char ch)
{
	switch (ch)
	{
		case '0': return 1.0f/16.0f;
		case '1': return 2.0f/16.0f;
		case '2': return 3.0f/16.0f;
		case '3': return 4.0f/16.0f;
		case '4': return 5.0f/16.0f;
		case '5': return 6.0f/16.0f;
		case '6': return 7.0f/16.0f;
		case '7': return 8.0f/16.0f;
		case '8': return 9.1f/16.0f;
		case '9': return 10.2f/16.0f;
		case '[': return 11.3f/16.0f;
		case ']': return 12.4f/16.0f;
		case '_': return 13.4f/16.0f;
		case '-': return 14.5f/16.0f;
		case '~': return 15.5f/16.0f;
		case '#': return 1.0f/2.0f;
		case '+': return 1.0f/2.0f;
		case 's': return 1.0f/2.0f;
		case 'x': return 1.0f/2.0f;
		case ':': return 1.0f/2.0f;
		case 'k': return 1.0f/2.0f;
		case 'm': return 1.0f/2.0f;
		case 'e': return 1.0f/2.0f;
	}

	return 0.0f;
}


BOOL CLcd::SetControlValue(CMovieBitmap *pControl, float value)
{
	if (!m_bOpen || !pControl) return FALSE;
	pControl->setValue(value);
	pControl->setDirty(true);
	return TRUE;
}


void CLcd::Show(char *pLine1, int lineSize1, char *pLine2, int lineSize2, unsigned char dot, BOOL bNothing)
{
	for (int i=0; i<lineSize2; i++)
	{
		SetControlValue(m_pChars[i],MapChar(pLine2[i]));
	}

	SetControlValue(m_pSharp[0],MapChar(pLine1[1]));
	SetControlValue(m_pSharp[1],MapChar(pLine1[5]));
	SetControlValue(m_pSharp[2],MapChar(pLine1[9]));

	SetControlValue(m_pE,MapChar(pLine1[0]));
	SetControlValue(m_pM,MapChar(pLine1[2]));
	SetControlValue(m_pK,MapChar(pLine1[3]));
	SetControlValue(m_pDiv,MapChar(pLine1[4]));
	SetControlValue(m_pMul,MapChar(pLine1[6]));
	SetControlValue(m_pSub,MapChar(pLine1[7]));
	SetControlValue(m_pAdd,MapChar(pLine1[8]));

	unsigned char mask = 0x80;
	for (i=0; i<8; i++)
	{
		SetControlValue(m_pDot[i],dot&mask?1.0f:0.0f);
		mask >>= 1;
	}
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


CLcdBuffer::CLcdBuffer() :
	m_pLcd(NULL)
{
	m_state.mode = kLcdOffMode;
	m_state.clock = 0;
	Clear();
	m_state.bReInit = TRUE;
}


CLcdBuffer::~CLcdBuffer()
{
}


void CLcdBuffer::OpenDisplay(CControlListener *pListener, VSTGUI::CFrame *pFrame)
{ 
	CCriticalSectionLock(m_cs);
	m_pLcd = new CLcd(pListener,pFrame);
	Show();
}


void CLcdBuffer::CloseDisplay()
{ 
	CCriticalSectionLock(m_cs);
	if (m_pLcd) delete m_pLcd; 
	m_pLcd = NULL; 
}


void CLcdBuffer::Clear()
{
	memset(m_state.line1,0,kLcdLine1Size*sizeof(char));
	memset(m_state.line2,0,kLcdLine2Size*sizeof(char));
	m_state.cursor = kLcdMaxCursor;
	m_state.dot = 0;
	m_state.bNeg = FALSE;
	m_state.function = kLcdNone;
	m_state.bReInit = FALSE;
}


void CLcdBuffer::Input(int key, int pos, BOOL bScroll)
{
	if (m_state.mode==kLcdOffMode) return;

	switch (key)
	{
		case kKeyPlusMin: // G4 or "+/-" (octave switch in "middle" position)
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',-1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) 
			{
				if (m_state.cursor<kLcdMaxCursor)
				{
					m_state.bNeg = !m_state.bNeg;
					SetChar(m_state.bNeg?'-':0,0,FALSE,m_state.cursor,FALSE);
				}
			}
			break;
		case kKeyPlusMinS: // G#4
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',-1,TRUE,pos,bScroll);
			break;
		case kKeyDot: // A4 or "."
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',-1,FALSE,pos,bScroll);
			else if ((m_state.mode==kLcdCalMode) && (m_state.dot==0)) m_state.dot = 0x01;
			break;
		case kKeyDotS: // A#4
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',-1,TRUE,pos,bScroll);
			break;
		case kKey0: // B4 or 0
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('7',-1,FALSE,pos,bScroll);
			else
			{
				if (m_state.cursor<kLcdMaxCursor) SetChar('0',0,FALSE,pos,bScroll);
			}
			break;
		case kKey1: // C5 or 1
			SetChar('1',0,FALSE,pos,bScroll);
			break;
		case kKey1S: // C#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',0,TRUE,pos,bScroll);
			break;
		case kKey2: // D5 or 2
			SetChar('2',0,FALSE,pos,bScroll);
			break;
		case kKey2S: // D#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',0,TRUE,pos,bScroll);
			break;
		case kKey3: // E5 or 3
			SetChar('3',0,FALSE,pos,bScroll);
			//ShowFloat(sqrt(2.0),TRUE);
			break;
		case kKey4: // F5 or 4
			SetChar('4',0,FALSE,pos,bScroll);
			//ShowFloat(876543);
			break;
		case kKey4S: // F#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',0,TRUE,pos,bScroll);
			//ShowFloat(876543.21);
			break;
		case kKey5: // G5 or 5
			SetChar('5',0,FALSE,pos,bScroll);
			break;
		case kKey5S: // G#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',0,TRUE,pos,bScroll);
			break;
		case kKey6: // A5 or 6
			SetChar('6',0,FALSE,pos,bScroll);
			break;
		case kKey6S: // A#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',0,TRUE,pos,bScroll);
			break;
		case kKey7: // B5 or 7
			SetChar('7',0,FALSE,pos,bScroll);
			break;
		case kKey8: // C6 or 8
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',1,FALSE,pos,bScroll);
			else SetChar('8',1,FALSE,pos,bScroll);
			break;
		case kKey8S: // C#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',1,TRUE,pos,bScroll);
			break;
		case kKey9: // D6 or 9
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',1,FALSE,pos,bScroll);
			else SetChar('9',1,FALSE,pos,bScroll);
			break;
		case kKey9S: // D#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',1,TRUE,pos,bScroll);
			break;
		case kKeyDiv: // E6 or ":"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('3',1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdDiv);
			break;
		case kKeyMul: // F6 or "x"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdMul);
			break;
		case kKeyMulS: // F#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',1,TRUE,pos,bScroll);
			break;
		case kKeySub: // G6 or "-"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdSub);
			break;
		case kKeySubS: // G#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',1,TRUE,pos,bScroll);
			break;
		case kKeyAdd: // A6 or "+"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdAdd);
			break;
		case kKeyAddS: // A#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',1,TRUE,pos,bScroll);
			break;
		case kKeyEqual: // B6 or "="
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('7',1,FALSE,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdNone);
			break;
		case kKeyReset:
			break;
		case kKeyDel:
			break;
		case kKeyTempoUp:
			break;
		case kKeyTempoDown:
			break;
		case kKeyRhythm:
			break;
		case kKeyMLC:
			break;
		case kKeyMusic:
			break;
		case kKeyAutoPlay:
			break;
		case kKeyOneKeyPlayDotDot:
			break;
		case kKeyOneKeyPlayDot:
			break;
	}

	Show();
}


void CLcdBuffer::SetMode(float value)
{
	switch (GetInterval(value,3.0f))
	{
		case 0:
			m_state.mode = kLcdPlayMode;
			break;

		case 1:
			m_state.mode = kLcdRecMode;
			break;

		case 2:
			m_state.mode = kLcdCalMode;
			break;

		case 3:
			m_state.mode = kLcdOffMode;
			break;
	}

	Clear();
	m_state.bReInit = TRUE;

	if (m_state.mode==kLcdPlayMode || m_state.mode==kLcdRecMode)
	{
		SetTempo(gClock.GetTempo());
	}
	else if (m_state.mode==kLcdCalMode)
	{
		m_state.bK = FALSE;
		m_state.bM = gCalculator.GetM();
		m_state.line1[2] = m_state.bM? 'm' : 0;
		m_state.line2[8] = '0';
	}
	else // m_state.mode==kLcdOffMode
	{
		Show(TRUE);
		return;
	}

	Show();
}


void CLcdBuffer::SetFunction(int function)
{
	if ((m_state.function!=kLcdNone) && (m_state.function==function)) m_state.bK = !m_state.bK;
	else
	{
		m_state.function = function;
		m_state.bK = FALSE;
		m_state.line1[8] = 0;
		m_state.line1[7] = 0;
		m_state.line1[6] = 0;
		m_state.line1[4] = 0;
	}

	switch (m_state.function)
	{
		case kLcdAdd:
			m_state.line1[8] = '+';
			break;

		case kLcdSub:
			m_state.line1[7] = 's';
			break;

		case kLcdMul:
			m_state.line1[6] = 'x';
			break;

		case kLcdDiv:
			m_state.line1[4] = ':';
			break;
	}

	m_state.line1[3] = m_state.bK? 'k' : 0;
	m_state.line1[2] = m_state.bM? 'm' : 0;
}


BOOL CLcdBuffer::SetChar(int ch, int octave, BOOL bSharp, int n, BOOL bScroll)
{
	if ((n>=kLcdLine2Size) || (n<0)) return FALSE;

	if (m_state.bReInit) Clear();
	if (bScroll)
	{
		if (!Scroll()) return FALSE;
	}

	m_state.line2[n] = ch;

	if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode))
	{
		if (n-1>=0) m_state.line2[n-1] = octave==1? '~' : octave==-1? '_' : 0;
		if (bSharp) m_state.line1[n+1] = bSharp? '#' : 0;
	}

	return TRUE;
}


BOOL CLcdBuffer::Scroll()
{
	int delta = 0;

	if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode))
	{
		m_state.line1[1] = m_state.line1[5];
		m_state.line1[5] = m_state.line1[9];
		m_state.line1[9] = 0;
		delta = 3;
	}
	else if (m_state.mode==kLcdCalMode)
	{
		if (m_state.cursor>0) 
		{
			m_state.cursor--;
			delta = 1;
			if (m_state.dot!=0x80) m_state.dot <<= 1;
		}
		else return FALSE;
	}
	else return FALSE;

	for (int i=0; i<kLcdLine2Size; i++)
	{
		if (i+delta<kLcdLine2Size)
		{
			m_state.line2[i] = m_state.line2[i+delta];
		}
		else break;
	}
	m_state.line2[kLcdLine2Size-1] = 0;

	return TRUE;
}


void CLcdBuffer::Show(BOOL bNothing)
{
	CCriticalSectionLock(m_cs);

	if (bNothing)
	{
		Clear();
	}

	unsigned char dot = m_state.dot;
	if (m_state.mode==kLcdCalMode && !dot && !bNothing) dot = 0x01;

	if (m_pLcd) m_pLcd->Show(m_state.line1, kLcdLine1Size, m_state.line2, kLcdLine2Size, dot, bNothing);
}


BOOL CLcdBuffer::ShowFloat(double value, BOOL bError)
{
	Clear();

	char str[80];
	int iValue = (int) value;
	double fValue = value - iValue;
	BOOL bInteger = fabs(fValue)<0.00000005? TRUE : FALSE;

	int d = sprintf(str,"%d",iValue);
	// Use width specifier to simulate bad precision.
	if (!bInteger) d = sprintf(str,"%*.*f",kLcdLine2Size,kLcdLine2Size-d,value) - 1;

	int dot = -1;
	int j = kLcdLine2Size - d;
	j += bInteger? 0 : 1;
	if (j<0) j = 0;
	for (int i=0; i<d; i++)
	{
		if (str[i]!='.') m_state.line2[j++] = str[i];
		else dot = i;
		if (j>=kLcdLine2Size) break;
	}

	m_state.dot = dot==-1? 0x01 : 1<<(8-dot);

	m_state.line1[0] = bError? 'e' : 0;

	return TRUE;
}


void CLcdBuffer::SetOperator(char op)
{
	m_state.line1[8] = 0;
	m_state.line1[7] = 0;
	m_state.line1[6] = 0;
	m_state.line1[4] = 0;

	switch (op)
	{
		case '+':
			m_state.line1[8] = '+';
			break;

		case '-':
			m_state.line1[7] = 's';
			break;

		case '*':
			m_state.line1[6] = 'x';
			break;

		case '/':
			m_state.line1[4] = ':';
			break;
	}
}


BOOL CLcdBuffer::ShowString(CVL1String& str, char op, BOOL bError, BOOL bM, BOOL bK)
{
	Clear();

	CVL1String s = str;
	if (s.Length()>0)
	{
		int dot = s.StripDot();
		int len = s.Length();
		m_state.dot = dot>0? 0x01<<(len-dot) : 0x01; 
		int offset = kLcdLine2Size - len;
		strcpy(&m_state.line2[offset],s.Get());
	}

	SetOperator(op);
	m_state.line1[0] = bError? 'e' : 0;
	m_state.line1[2] = bM? 'm' : 0;
	m_state.line1[3] = bK? 'k' : 0;

	Show();

	return TRUE;
}


#define kMaxTick  32

void CLcdBuffer::Tick()
{
	m_state.clock++;
	if (m_state.clock>=kMaxTick) m_state.clock = 0;

	if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode))
	{
		if (m_state.clock>=(kMaxTick>>1)) m_state.line2[0] = '-';
		else m_state.line2[0] = 0;
//		Show();
	}
}


void CLcdBuffer::SetTempo(float tempo)
{
	if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode))
	{
		Clear();
		m_state.line2[3] = '[';
		if (tempo<0) m_state.line2[4] = '-';
		m_state.line2[5] = DigitToChar[abs((int)tempo)];
		m_state.line2[6] = ']';
		Show();
		m_state.bReInit = TRUE;
	}
}

#define kNoteToKeyMax  29
const int NoteToKey[kNoteToKeyMax] = 
{
	kKeyPlusMin,  // 0
	kKeyPlusMinS,  // 1
	kKeyDot,  // 2
	kKeyDotS,  // 3
	kKey0,  // 4
	kKey1,  // 5
	kKey1S,  // 6
	kKey2,  // 7
	kKey2S,  // 8
	kKey3,  // 9
	kKey4,  // 10
	kKey4S,  // 11
	kKey5,  // 12
	kKey5S,  // 13
	kKey6,  // 14
	kKey6S,  // 15
	kKey7,  // 16
	kKey8,  // 17
	kKey8S,  // 18
	kKey9,  // 19
	kKey9S,  // 20
	kKeyDiv,  // 21
	kKeyMul,  // 22
	kKeyMulS,  // 23
	kKeySub,  // 24
	kKeySubS,  // 25
	kKeyAdd,  // 26
	kKeyAddS,  // 27
	kKeyEqual,  // 28
};


void CLcdBuffer::ShowNote(int note)
{ 
	Input(NoteToKey[note-55]); // 55 is +/- key (G0)
}


void CLcdBuffer::ScrollRight(int note)
{
	m_state.line1[9] = m_state.line1[5];
	m_state.line1[5] = m_state.line1[1];
	m_state.line1[1] = 0;

	for (int i=kLcdLine2Size-1; i>3; i-=3)
	{
		m_state.line2[i] = m_state.line2[i-3];
	}

	if (!note)
	{
		m_state.line2[1] = 0;
		m_state.line2[2] = 0;
		Show();
	}
	else
	{
		Input(NoteToKey[note-55],2,FALSE); // 55 is +/- key (G0)
	}
}
