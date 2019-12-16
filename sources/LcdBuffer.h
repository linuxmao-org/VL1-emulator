#pragma once
#include "VL1Defs.h"
#include "VL1String.h"


class CCalculator;


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


typedef struct
{
	int mode;
	int function;
	int cursor;
	unsigned char dot;
	bool bK;
	bool bM;
	bool bNeg;
	char line1[kLcdLine1Size];
	char line2[kLcdLine2Size];
	bool bReInit;
	int clock;
}
tLcdState;


typedef struct
{
	unsigned char dot;
	char line1[kLcdLine1Size];
	char line2[kLcdLine2Size];
}
tLcdScreenData;


class CLcdBuffer
{
public:
	CLcdBuffer();
	~CLcdBuffer();

	void Setup(CCalculator *calculator, tLcdScreenData *screenData);

	void SetMode(float value);
	void Input(int key, int pos=8, bool bScroll=true);
	void ScrollRight(int note);
	void Clear();

	void Show(bool bNothing=false);
	bool ShowFloat(double value, bool bError=false);
	bool ShowString(CVL1String& str, char op, bool bError=false, bool bM=false, bool bK=false);
	void ShowNote(int note);

	void Tick();
	void SetTempo(float tempo);

	void GetState(tLcdState& state) { state = m_state; }
	void SetState(tLcdState& state) { m_state = state; }

private:
	bool SetChar(int ch, int octave, bool bSharp, int n=8, bool bScroll=true);
	bool Scroll();
	void SetFunction(int function);
	void SetOperator(char op);

	tLcdState m_state;
	tLcdScreenData *m_screenData;

	CCalculator *m_calculator;
};