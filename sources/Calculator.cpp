#include "Calculator.h"
#include "VL1Defs.h"
#include <math.h>


CCalculator::CCalculator()
{
	Clear(true,false);
}


void CCalculator::Clear(bool bClearK, bool bRefuseOnError)
{
	if ((bRefuseOnError) && (m_state.bError)) return;
	else
	{
		m_state.str1.Clear();
		m_state.str1.Zero();
		m_state.str2.Clear();
		m_state.strPerc.Clear();
		m_state.Operator = '\0';
		m_state.mode = kEnterNumber1;
		m_state.bError = false;
		m_state.bPendingClear = false;
		m_state.bPendingStripTrailingZeroes = false;
		if (bClearK) ClearK();
	}
}


bool CCalculator::Check(double& n)
{
	if (fabs(n)>99999999.0)
	{
		n /= 100000000.0;
		m_state.bError = true;
	}
	return m_state.bError;
}


void CCalculator::ClearK()
{
	m_state.strK.Clear();
	m_state.bK = false;
	m_state.operatorK = '\0';
}


void CCalculator::ClearM()
{
	m_state.strM.Clear();
	//m_state.bM = false;
}


bool CCalculator::AddToM(CVL1String& str)
{
	double n1 = m_state.strM.GetAsDouble();
	double n2 = str.GetAsDouble();
	n1 += n2;
	if (!Check(n1))
	{
		m_state.strM.SetFromDouble(n1);
		return true;
	}
	else return false;
}


bool CCalculator::SubtractFromM(CVL1String& str)
{
	double n1 = m_state.strM.GetAsDouble();
	double n2 = str.GetAsDouble();
	n1 -= n2;
	if (!Check(n1))
	{
		m_state.strM.SetFromDouble(n1);
		return true;
	}
	else return false;
}


CVL1String& CCalculator::Calculate(bool bClearK)
{
	if (m_state.str1.IsEmpty())
	{
		m_state.str1.Zero();
		return m_state.str1;
	}

	double n1;
	if ((m_state.bK) && (!m_state.str2.IsEmpty())) n1 = m_state.str2.GetAsDouble();
	else n1 = m_state.str1.GetAsDouble();

	double n2;
	if (m_state.bK) n2 = m_state.strK.GetAsDouble();
	else
	{
		if (m_state.str2.IsEmpty())
		{
			if ((m_state.Operator=='-') || (m_state.Operator=='+')) n2 = 0;
			else n2 = m_state.str1.GetAsDouble();
		}
		else n2 = m_state.str2.GetAsDouble();
	}

	char op = m_state.bK? m_state.operatorK : m_state.Operator;

	switch (op)
	{
		case '+':
			n1 += n2;
			break;

		case '-':
			n1 -= n2;
			break;

		case '/':
			if (n2!=0.0) n1 /= n2;
			else
			{
				n1 = 0.0;
				m_state.bError = true;
			}
			break;

		case '*':
			n1 *= n2;
			break;
	}

	Check(n1);

	m_state.str1.SetFromDouble(n1,!m_state.bError);

	if (bClearK) m_state.bK = false;

	if (m_state.bK) m_state.str2.SetFromDouble(n1);
	else
	{
		m_state.str2.Clear();
		ClearK();
		m_state.Operator = '\0';
	}

	m_state.mode = kEnterNumber1;

	return m_state.str1;
}


CVL1String& CCalculator::CalculatePercentage(bool bClearK)
{
	if (m_state.str1.IsEmpty())
	{
		m_state.str1.Zero();
		return m_state.str1;
	}

	double n1;
	if ((m_state.bK) && (!m_state.str2.IsEmpty())) n1 = m_state.str2.GetAsDouble();
	else n1 = m_state.str1.GetAsDouble();

	double n2;
	if (m_state.bK) n2 = m_state.strK.GetAsDouble();
	else
	{
		if (m_state.str2.IsEmpty())
		{
			if ((m_state.Operator=='-') || (m_state.Operator=='+')) n2 = 0;
			else n2 = m_state.str1.GetAsDouble();
		}
		else n2 = m_state.str2.GetAsDouble();
	}

	char op = m_state.bK? m_state.operatorK : m_state.Operator;

	switch (op)
	{
		case '+':
			n1 /= (1.0 - (n2/100.0)); // Mark-up percentage
			break;

		case '-':
			n1 = 100.0*(n1-n2)/(n2); // Delta percentage
			break;

		case '/':
			if (n2!=0.0) n1 /= 0.01*n2;
			else
			{
				n1 = 0.0;
				m_state.bError = true;
			}
			break;

		case '*':
			n1 *= 0.01*n2;
			break;
	}

	Check(n1);

	m_state.str1.SetFromDouble(n1);

	if (bClearK) m_state.bK = false;

	if (m_state.bK) m_state.str2.SetFromDouble(n1);
	else
	{
		m_state.str2.Clear();
		ClearK();
		m_state.Operator = '\0';
	}

	m_state.mode = kEnterNumber1;

	return m_state.str1;
}


bool CCalculator::Sqrt(CVL1String& str)
{
	if (str.IsEmpty())
	{
		str.Zero();
		return false;
	}

	double n = str.GetAsDouble();

	if (n<0) m_state.bError = true;
	n = sqrt(fabs(n));

	str.SetFromDouble(n);

	return !m_state.bError;
}


CVL1String& CCalculator::AddChar(char ch)
{
	//if (m_state.bError) return m_state.str1;

	if (IsNumber(ch))
	{
		if (m_state.mode==kPercentMode)
		{
			m_state.mode = kEnterNumber1;
		}
		if (m_state.mode==kEnterNumber1)
		{
			if (m_state.bPendingClear) Clear(false,true);
			if (m_state.str1.IsEmpty()) m_state.str1.Zero();
			if (m_state.str1.LengthWithoutDot()<=kMaxNumberLength) m_state.str1.Add(ch);
			return m_state.str1;
		}
		if (m_state.mode==kEnterOperator)
		{
			m_state.str2.Clear();
			m_state.mode = kEnterNumber2;
		}
		if (m_state.mode==kEnterNumber2)
		{
			if (m_state.str2.IsEmpty()) m_state.str2.Zero();
			if (m_state.str2.LengthWithoutDot()<=kMaxNumberLength) m_state.str2.Add(ch);
			return m_state.str2;
		}
	}
	else if (IsOperator(ch))
	{
		switch (m_state.mode)
		{
			case kPercentMode:
				m_state.mode = kEnterOperator;
				if ((m_state.operatorPerc=='*') && ((ch=='+') || (ch=='-')))
				{
					m_state.str2 = m_state.strPerc;
					if (ch=='-') m_state.str1.InvertSign();
					m_state.Operator = '+';
					return Calculate();
				}
				else if ((m_state.operatorPerc=='+') && (ch=='-'))
				{
					m_state.str2 = m_state.strPerc;
					m_state.Operator = ch;
					return Calculate();
				}
				break;

			case kEnterNumber1:
				m_state.bK = false;
				m_state.mode = kEnterOperator;
				break;

			case kEnterNumber2:
				Calculate();
				m_state.mode = kEnterOperator;
				break;

			case kEnterOperator:
				if (ch==m_state.Operator)
				{
					m_state.bK = !m_state.bK;
					if (m_state.bK)
					{
						m_state.strK = m_state.str1;
						m_state.operatorK = m_state.Operator;
					}
					else
					{
						m_state.str2 = m_state.strK;
						//m_state.strK.Clear();
					}
				}
				else
				{
					m_state.bK = false;
					//m_state.strK.Clear();
				}
				break;
		}

		m_state.Operator = ch;

		if (m_state.mode==kEnterNumber2) return m_state.str2;
		else
		{
			if (m_state.bPendingStripTrailingZeroes)
			{
				// Needed sometimes after clearing an error using "C".
				// Example:
				// 123456 x 741852 = E 915.86080
				// Press "C" to clear the error -> 915.86080
				// Press -, +, x, / to remove the trailing zero -> 915.8608
				m_state.bPendingStripTrailingZeroes = false;
				m_state.str1.StripTrailingZeroes();
			}

			return m_state.str1;
		}
	}

	return m_state.str1;
}


bool CCalculator::IsOperator(char ch)
{
	switch (ch)
	{
		case '/':
		case '*':
		case '-':
		case '+':
			return true;
	}
	return false;
}


bool CCalculator::IsNumber(char ch)
{
	switch (ch)
	{
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
	}
	return false;
}


CVL1String& CCalculator::Input(int key)
//
// TODO (21/12/2004): develop a proper state machine.
//
{
	if ((m_state.bError) && (key!=kKeyReset) && (key!=kKeyDel)) return m_state.str1;

	switch (key)
	{
		case kKeyPlusMin: // "+/-"
			if ((m_state.mode==kEnterNumber1) || (m_state.mode==kEnterOperator))
			{
				m_state.str1.InvertSign();
				return m_state.str1;
			}
			else if (m_state.mode==kEnterNumber2)
			{
				m_state.str2.InvertSign();
				return m_state.str2;
			}
			return m_state.str1;

		case kKeyDot: // "."
			return AddChar('.');

		case kKey0: // 0
			return AddChar('0');

		case kKey1: // 1
			return AddChar('1');

		case kKey2: // 2
			return AddChar('2');

		case kKey3: // 3
			return AddChar('3');

		case kKey4: // 4
			return AddChar('4');

		case kKey5: // 5
			return AddChar('5');

		case kKey6: // 6
			return AddChar('6');

		case kKey7: // 7
			return AddChar('7');

		case kKey8: // 8
			return AddChar('8');

		case kKey9: // 9
			return AddChar('9');

		case kKeyDiv: // ":"
			return AddChar('/');

		case kKeyMul: // "x"
			return AddChar('*');

		case kKeySub: // "-"
			return AddChar('-');

		case kKeyAdd: // "+"
			return AddChar('+');

		case kKeyEqual: // "="
			m_state.bPendingClear = true;
			return Calculate(false);

		case kKeyReset: // AC
			Clear(true,false);
			m_state.str1.Zero();
			break;

		case kKeyDel: // C
			if (m_state.bError)
			{
				m_state.bError = false;
				m_state.bPendingStripTrailingZeroes = true;
			}
			else if (m_state.mode==kEnterNumber1)
			{
				m_state.str1.Clear();
				m_state.str1.Zero();
				return m_state.str1;
			}
			else if (m_state.mode==kEnterNumber2)
			{
				m_state.str2.Clear();
				m_state.str2.Zero();
				return m_state.str2;
			}
			break;

		case kKeyTempoUp: // sqrt
			switch (m_state.mode)
			{
				case kEnterNumber1:
					m_state.bPendingClear = true;
					Sqrt(m_state.str1);
					break;

				case kEnterOperator:
					if (m_state.str2.IsEmpty())
					{
						m_state.str2 = m_state.str1;
						Sqrt(m_state.str2);
						return m_state.str2;
					}
					break;

				case kEnterNumber2:
					Sqrt(m_state.str2);
					return m_state.str2;
			}
			break;

		case kKeyTempoDown: // %
			if (m_state.mode==kEnterOperator) m_state.str2 = m_state.str1;
			if (m_state.mode!=kEnterNumber1)
			{
				m_state.strPerc = m_state.str1;
				m_state.operatorPerc = m_state.Operator;
				m_state.bPendingClear = true;
				CalculatePercentage();
				m_state.mode = kPercentMode;
			}
			break;

		case kKeyMLC: // MC
			ClearM();
			break;

		case kKeyMusic: // MR
			if (m_state.strM.IsEmpty()) m_state.strM.Zero();
			switch (m_state.mode)
			{
				case kEnterNumber1:
					m_state.bPendingClear = true;
					m_state.str1 = m_state.strM;
					break;

				case kEnterOperator:
				case kEnterNumber2:
					m_state.str2 = m_state.strM;
					return m_state.str2;
			}
			return m_state.str1;
			break;

		case kKeyAutoPlay: // M-
			m_state.bPendingClear = true;
			Calculate();
			if (!m_state.bError)
			{
				if (!SubtractFromM(m_state.str1)) m_state.str1.Zero();
			}
			break;

		case kKeyOneKeyPlayDotDot: // M+
			m_state.bPendingClear = true;
			Calculate();
			if (!m_state.bError)
			{
				if (!AddToM(m_state.str1)) m_state.str1.Zero();
			}
			break;
	}

	return m_state.str1;
}


int CCalculator::Test()
{
	int errors = 0;
	CVL1String str;

	str = Input(kKeyReset); // Display: 0.
	if (str.GetAsDouble()!=0.0) errors++;

	Input(kKey5);
	Input(kKey3);
	Input(kKeyAdd);
	Input(kKey1);
	Input(kKey2);
	Input(kKey3);
	Input(kKeySub);
	Input(kKey6);
	Input(kKey3);
	Input(kKeyEqual); // Display: 113.
	if (str.GetAsDouble()!=113) errors++;

	Input(kKey2);
	Input(kKey3);
	Input(kKeySub);
	Input(kKey5);
	Input(kKey6);
	Input(kKeyMul);
	Input(kKey9);
	Input(kKey6);
	Input(kKey3);
	Input(kKeyEqual); // Display: -31779.
	if (str.GetAsDouble()!=-31779) errors++;

	Input(kKey5);
	Input(kKey6);
	Input(kKeyMul);
	Input(kKey3);
	Input(kKeySub);
	Input(kKey8);
	Input(kKey9);
	Input(kKeyDiv);
	Input(kKey5);
	Input(kKeyDot);
	Input(kKey2);
	Input(kKeyAdd);
	Input(kKey6);
	Input(kKey3);
	Input(kKeyEqual); // Display: 78.192307
	if (str.GetAsDouble()!=78.192307) errors++;

	/*Input(kKey);
	Input(kKey);
	Input(kKey);
	Input(kKey);
	Input(kKey);
	Input(kKey);
	Input(kKey);*/

	return errors;
}
