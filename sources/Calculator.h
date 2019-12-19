/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

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
	bool bK;
	bool bError;
	bool bPendingClear;
	bool bPendingStripTrailingZeroes;
}
tCalculatorState;


class CCalculator
{
public:
	CCalculator();
	~CCalculator() {}

	void Clear(bool bClearK, bool bRefuseOnError);
	void ClearK();
	void ClearM();
	CVL1String& Input(int key);

	CVL1String& GetNumber(int i) { return i==1? m_state.str1 : m_state.str2; }
	char GetOperator() { return m_state.bK? m_state.operatorK : m_state.Operator; }
	bool GetError() { return m_state.bError; }

	bool GetM() { return !m_state.strM.IsEmpty() && !m_state.strM.IsZero(); }
	CVL1String& GetMAsString() { return m_state.strM; }
	void SetM(CVL1String& str) { m_state.strM = str; }

	bool GetK() { return m_state.bK; }

	bool AddToM(CVL1String& str);
	bool SubtractFromM(CVL1String& str);

	int Test();

	void GetState(tCalculatorState& state) { state = m_state; }
	void SetState(tCalculatorState& state) { m_state = state; }

private:
	tCalculatorState m_state;

	bool IsOperator(char ch);
	bool IsNumber(char ch);
	bool Check(double& n);
	CVL1String& AddChar(char ch);
	CVL1String& Calculate(bool bClearK=true);
	CVL1String& CalculatePercentage(bool bClearK=false);
	bool Sqrt(CVL1String& str);
};


#endif // __CALCULATOR_H__
