#include "LcdBuffer.h"
#include "Clock.h"
#include "Calculator.h"
#include "SharedData.h"
#include <stdio.h>
#include <math.h>


const char DigitToChar[10] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};


CLcdBuffer::CLcdBuffer()
	: m_pShared(nullptr)
{
	m_state.mode = kLcdOffMode;
	m_state.clock = 0;
	Clear();
	m_state.bReInit = true;
}


CLcdBuffer::~CLcdBuffer()
{
}


void CLcdBuffer::Setup(CSharedData *pShared)
{
	m_pShared = pShared;
}


void CLcdBuffer::Clear()
{
	memset(m_state.line1,0,kLcdLine1Size*sizeof(char));
	memset(m_state.line2,0,kLcdLine2Size*sizeof(char));
	m_state.cursor = kLcdMaxCursor;
	m_state.dot = 0;
	m_state.bNeg = false;
	m_state.function = kLcdNone;
	m_state.bReInit = false;
}


void CLcdBuffer::Input(int key, int pos, bool bScroll)
{
	if (m_state.mode==kLcdOffMode) return;

	switch (key)
	{
		case kKeyPlusMin: // G4 or "+/-" (octave switch in "middle" position)
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',-1,false,pos,bScroll);
			else if (m_state.mode==kLcdCalMode)
			{
				if (m_state.cursor<kLcdMaxCursor)
				{
					m_state.bNeg = !m_state.bNeg;
					SetChar(m_state.bNeg?'-':0,0,false,m_state.cursor,false);
				}
			}
			break;
		case kKeyPlusMinS: // G#4
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',-1,true,pos,bScroll);
			break;
		case kKeyDot: // A4 or "."
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',-1,false,pos,bScroll);
			else if ((m_state.mode==kLcdCalMode) && (m_state.dot==0)) m_state.dot = 0x01;
			break;
		case kKeyDotS: // A#4
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',-1,true,pos,bScroll);
			break;
		case kKey0: // B4 or 0
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('7',-1,false,pos,bScroll);
			else
			{
				if (m_state.cursor<kLcdMaxCursor) SetChar('0',0,false,pos,bScroll);
			}
			break;
		case kKey1: // C5 or 1
			SetChar('1',0,false,pos,bScroll);
			break;
		case kKey1S: // C#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',0,true,pos,bScroll);
			break;
		case kKey2: // D5 or 2
			SetChar('2',0,false,pos,bScroll);
			break;
		case kKey2S: // D#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',0,true,pos,bScroll);
			break;
		case kKey3: // E5 or 3
			SetChar('3',0,false,pos,bScroll);
			//ShowFloat(sqrt(2.0),true);
			break;
		case kKey4: // F5 or 4
			SetChar('4',0,false,pos,bScroll);
			//ShowFloat(876543);
			break;
		case kKey4S: // F#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',0,true,pos,bScroll);
			//ShowFloat(876543.21);
			break;
		case kKey5: // G5 or 5
			SetChar('5',0,false,pos,bScroll);
			break;
		case kKey5S: // G#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',0,true,pos,bScroll);
			break;
		case kKey6: // A5 or 6
			SetChar('6',0,false,pos,bScroll);
			break;
		case kKey6S: // A#5
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',0,true,pos,bScroll);
			break;
		case kKey7: // B5 or 7
			SetChar('7',0,false,pos,bScroll);
			break;
		case kKey8: // C6 or 8
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',1,false,pos,bScroll);
			else SetChar('8',1,false,pos,bScroll);
			break;
		case kKey8S: // C#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('1',1,true,pos,bScroll);
			break;
		case kKey9: // D6 or 9
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',1,false,pos,bScroll);
			else SetChar('9',1,false,pos,bScroll);
			break;
		case kKey9S: // D#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('2',1,true,pos,bScroll);
			break;
		case kKeyDiv: // E6 or ":"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('3',1,false,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdDiv);
			break;
		case kKeyMul: // F6 or "x"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',1,false,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdMul);
			break;
		case kKeyMulS: // F#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('4',1,true,pos,bScroll);
			break;
		case kKeySub: // G6 or "-"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',1,false,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdSub);
			break;
		case kKeySubS: // G#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('5',1,true,pos,bScroll);
			break;
		case kKeyAdd: // A6 or "+"
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',1,false,pos,bScroll);
			else if (m_state.mode==kLcdCalMode) SetFunction(kLcdAdd);
			break;
		case kKeyAddS: // A#6
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('6',1,true,pos,bScroll);
			break;
		case kKeyEqual: // B6 or "="
			if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode)) SetChar('7',1,false,pos,bScroll);
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
	m_state.bReInit = true;

	if (m_state.mode==kLcdPlayMode || m_state.mode==kLcdRecMode)
	{
		SetTempo(m_pShared->clock->GetTempo());
	}
	else if (m_state.mode==kLcdCalMode)
	{
		m_state.bK = false;
		m_state.bM = m_pShared->calculator->GetM();
		m_state.line1[2] = m_state.bM? 'm' : 0;
		m_state.line2[8] = '0';
	}
	else // m_state.mode==kLcdOffMode
	{
		Show(true);
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
		m_state.bK = false;
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


bool CLcdBuffer::SetChar(int ch, int octave, bool bSharp, int n, bool bScroll)
{
	if ((n>=kLcdLine2Size) || (n<0)) return false;

	if (m_state.bReInit) Clear();
	if (bScroll)
	{
		if (!Scroll()) return false;
	}

	m_state.line2[n] = ch;

	if ((m_state.mode==kLcdPlayMode) || (m_state.mode==kLcdRecMode))
	{
		if (n-1>=0) m_state.line2[n-1] = octave==1? '~' : octave==-1? '_' : 0;
		if (bSharp) m_state.line1[n+1] = bSharp? '#' : 0;
	}

	return true;
}


bool CLcdBuffer::Scroll()
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
		else return false;
	}
	else return false;

	for (int i=0; i<kLcdLine2Size; i++)
	{
		if (i+delta<kLcdLine2Size)
		{
			m_state.line2[i] = m_state.line2[i+delta];
		}
		else break;
	}
	m_state.line2[kLcdLine2Size-1] = 0;

	return true;
}


void CLcdBuffer::Show(bool bNothing)
{
	if (bNothing)
	{
		Clear();
	}

	unsigned char dot = m_state.dot;
	if (m_state.mode==kLcdCalMode && !dot && !bNothing) dot = 0x01;

	tLcdScreenData *screenData = m_pShared->screenData;
	if (screenData)
	{
		screenData->dot = dot;
		memcpy(screenData->line1, m_state.line1, kLcdLine1Size);
		memcpy(screenData->line2, m_state.line2, kLcdLine2Size);
	}
}


bool CLcdBuffer::ShowFloat(double value, bool bError)
{
	Clear();

	char str[80];
	int iValue = (int) value;
	double fValue = value - iValue;
	bool bInteger = fabs(fValue)<0.00000005? true : false;

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

	return true;
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


bool CLcdBuffer::ShowString(CVL1String& str, char op, bool bError, bool bM, bool bK)
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

	return true;
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
		m_state.bReInit = true;
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
		Input(NoteToKey[note-55],2,false); // 55 is +/- key (G0)
	}
}
