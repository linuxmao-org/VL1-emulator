#ifndef __VL1_STRING_H__
#define __VL1_STRING_H__


#include "Utils.h"
#include <stdlib.h>
#include <string.h>


enum
{
	kVL1StringMaxLength = 80,
};


class CVL1String
{
public:
	CVL1String();
	CVL1String(char *pStr);
	~CVL1String() {}

	inline int Length() { return strlen(m_str); }
	int LengthWithoutDot()
	{
		int len = strlen(m_str);
		if (strchr(m_str,'.')) len--;
		return len;
	}
	void Clear();
	bool IsEmpty() { return Length()==0; }
	int Zero();
	bool IsZero() { return GetAsDouble()==0.0; }

	int Add(char ch);
	int InsertAt(char ch, int i);
	int SetAt(char ch, int i=1);
	char GetAt(int i) { if ((i>=0) && (i<m_index)) return m_str[i]; else return 0; }

	char *Get() { return m_str; }
	double GetAsDouble() { return atof(m_str); }
	int SetFromDouble(double d, bool bStripTrailingZeroes=true, int maxDigits=8, bool bRound=false);
	int SetFromFloat(float d, bool bStripTrailingZeroes=true, int maxDigits=8, bool bRound=false);

	unsigned int GetAsUlong();

	void Sign(bool bNegative) { m_str[0] = bNegative? '-' : ' '; }
	void InvertSign() { m_str[0] = m_str[0]=='-'? ' ' : '-'; }

	CVL1String& operator=(CVL1String& str);

	int Truncate(int len);
	int StripTrailingZeroes();
	int StripDot();
	int GetDot();
	int GetDotRev();
	bool IsInteger();

	void Test();

private:
	char m_str[kVL1StringMaxLength];
	int m_index;
};


#endif // __VL1_STRING_H__
