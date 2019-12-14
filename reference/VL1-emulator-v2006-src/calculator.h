#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


#include "Utils.h"
#include "VL1String.h"


enum
{
	kEnterNumber1,
	kEnterOperator,
	kEnterNumber2,
	kPercentMode,
	kMaxIndex = 9,
	kMaxNumberLength = 8,
};


typedef struct
{
	CVL1String str1;
	CVL1String str2;
	CVL1String strK;
	CVL1String strM;
	CVL1String strPerc;
	char Operator;
	char operatorK;
	char operatorPerc;
	int mode;
	BOOL bK;
	BOOL bError;
	BOOL bPendingClear;
	BOOL bPendingStripTrailingZeroes;
}
tCalculatorState;


class CCalculator
{
public:
	CCalculator();
	~CCalculator() {}

	void Clear(BOOL bClearK, BOOL bRefuseOnError);
	void ClearK();
	void ClearM();
	CVL1String& Input(int key);

	CVL1String& GetNumber(int i) { return i==1? m_state.str1 : m_state.str2; }
	char GetOperator() { return m_state.bK? m_state.operatorK : m_state.Operator; }
	BOOL GetError() { return m_state.bError; }
	
	BOOL GetM() { return !m_state.strM.IsEmpty() && !m_state.strM.IsZero(); }
	CVL1String& GetMAsString() { return m_state.strM; }
	void SetM(CVL1String& str) { m_state.strM = str; }

	BOOL GetK() { return m_state.bK; }

	BOOL AddToM(CVL1String& str);
	BOOL SubtractFromM(CVL1String& str);

	int Test();

	void GetState(tCalculatorState& state) { state = m_state; }
	void SetState(tCalculatorState& state) { m_state = state; }

private:
	tCalculatorState m_state;

	BOOL IsOperator(char ch);
	BOOL IsNumber(char ch);
	BOOL Check(double& n);
	CVL1String& AddChar(char ch);
	CVL1String& Calculate(BOOL bClearK=TRUE);
	CVL1String& CalculatePercentage(BOOL bClearK=FALSE);
	BOOL Sqrt(CVL1String& str);
};


#endif // __CALCULATOR_H__
