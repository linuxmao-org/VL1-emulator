#ifndef __LCD__
#define __LCD__


// include VSTGUI
#ifndef __vstgui__
#include "vstgui.h"
#endif


#include "Utils.h"
#include "VL1String.h"
#include "CriticalSection.h"


enum
{
	kLcdPlayMode,
	kLcdRecMode,
	kLcdCalMode,
	kLcdOffMode,

	kLcdLine1Size = 10,
	kLcdLine2Size = 9,
	//kLcdMaxLine = 2,
	kLcdMaxChar = 9,
	kLcdMaxSharp = 3,
	kLcdMaxDot = 8,
	kLcdMaxCursor = kLcdLine2Size-1,

	kLcdNone = 0,
	kLcdAdd = 1,
	kLcdSub = 2,
	kLcdMul = 3,
	kLcdDiv = 4,
};


class CLcd
{
public:
	CLcd();
	CLcd(CControlListener *pListener, VSTGUI::CFrame *pFrame);
	~CLcd();

	void Initialize();
	long Open(CControlListener *pListener, VSTGUI::CFrame *pFrame);
	void Close();

	void Show(char *pLine1, int lineSize1, char *pLine2, int lineSize2, unsigned char dot, BOOL bNothing=FALSE);

private:
	BOOL AddChar(int id, int idBmp, int x, int y, int nBmp, CMovieBitmap **ppControl, CControlListener *pListener, VSTGUI::CFrame *pFrame);
	float MapChar(char ch);
	BOOL SetControlValue(CMovieBitmap *pControl, float value);

	int m_mode;
	int m_function;
	int m_cursor;
	unsigned char m_dot;

	CMovieBitmap *m_pSharp[kLcdMaxSharp];
	CMovieBitmap *m_pE;
	CMovieBitmap *m_pM;
	CMovieBitmap *m_pK;
	CMovieBitmap *m_pMul;
	CMovieBitmap *m_pDiv;
	CMovieBitmap *m_pAdd;
	CMovieBitmap *m_pSub;
	CMovieBitmap *m_pChars[kLcdMaxChar];
	CMovieBitmap *m_pDot[kLcdMaxDot];

	BOOL m_bOpen;
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


typedef struct
{
	int mode;
	int function;
	int cursor;
	unsigned char dot;
	BOOL bK;
	BOOL bM;
	BOOL bNeg;
	char line1[kLcdLine1Size];
	char line2[kLcdLine2Size];
	BOOL bReInit;
	int clock;
}
tLcdState;


class CLcdBuffer
{
public:
	CLcdBuffer();
	~CLcdBuffer();

	long Open();
	void Close();

	void SetMode(float value);
	void Input(int key, int pos=8, BOOL bScroll=TRUE);
	void ScrollRight(int note);
	void Clear();

	void Show(BOOL bNothing=FALSE);
	BOOL ShowFloat(double value, BOOL bError=FALSE);
	BOOL ShowString(CVL1String& str, char op, BOOL bError=FALSE, BOOL bM=FALSE, BOOL bK=FALSE);
	void ShowNote(int note);

	void Tick();
	void SetTempo(float tempo);

	void OpenDisplay(CControlListener *pListener, VSTGUI::CFrame *pFrame);
	void CloseDisplay();

	void GetState(tLcdState& state) { state = m_state; }
	void SetState(tLcdState& state) { m_state = state; }

private:
	CCriticalSection m_cs;
	CLcd *m_pLcd;

	BOOL SetChar(int ch, int octave, BOOL bSharp, int n=8, BOOL bScroll=TRUE);
	BOOL Scroll();
	void SetFunction(int function);
	void SetOperator(char op);

	tLcdState m_state;
};


extern CLcdBuffer gLCD;


#endif // __LCD__
