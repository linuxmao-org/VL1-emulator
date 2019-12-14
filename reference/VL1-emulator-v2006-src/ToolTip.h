#ifndef __TOOLTIP__
#define __TOOLTIP__


// include VSTGUI
#ifndef __vstgui__
#include "vstgui.h"
#endif


#include "Utils.h"
//#include "VL1String.h"
#include "CriticalSection.h"


typedef struct
{
	//int x;
	//int y;
	//int id;
	int bmp[4]; //index: kVL1Play=0, kVL1Rec=1, kVL1Cal=2, kVL1Off=3
	CMovieBitmap *pToolTip;
	CControl *pBuddyCtrl;
}
tToolTipItem;


class CToolTip
{
public:
	CToolTip();
	CToolTip(CControlListener *pListener, VSTGUI::CFrame *pFrame);
	~CToolTip();

	void Initialize();
	long Open(CControlListener *pListener, VSTGUI::CFrame *pFrame);
	void Close();

	void Show(char *pLine1, int lineSize1, char *pLine2, int lineSize2, unsigned char dot, BOOL bNothing=FALSE);

private:
	BOOL Add(int id, int idBmp, int x, int y, int nBmp, CMovieBitmap **ppControl, CControlListener *pListener, VSTGUI::CFrame *pFrame, int *pModes);
	float MapChar(char ch);
	BOOL SetControlValue(CMovieBitmap *pControl, float value);

	tToolTipItem m_tooltip[kToolTipItems];

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


#endif // __TOOLTIP__
