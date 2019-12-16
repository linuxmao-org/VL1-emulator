#include "VL1String.h"
#include <memory.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>


CVL1String::CVL1String()
{
	Clear();
}


CVL1String::CVL1String(char *pStr)
{
	strcpy(m_str,pStr);
	m_index = strlen(pStr);
}


void CVL1String::Clear()
{
	memset(m_str,0,kVL1StringMaxLength);
	m_index = 0;
}


int CVL1String::Zero()
{
	m_str[0] = ' ';
	m_str[1] = '0';
	m_index = 1;
	return Length();
}


int CVL1String::Truncate(int len)
{
	if (Length()>len)
	{
		m_str[len] = '\0';
		m_index = len;
	}
	return Length();
}


int CVL1String::Add(char ch)
{
	if (m_index<kVL1StringMaxLength-1)
	{
		if (m_index==1 && ch=='.') m_index++;
		m_str[m_index++] = ch;
		return Length();
	}
	return -1;
}


int CVL1String::InsertAt(char ch, int i)
{
	if ((i>=0) && (i<m_index) && (m_index<kVL1StringMaxLength-1))
	{
		memmove(&m_str[i+1],&m_str[i],1);
		m_str[i] = ch;
		m_index = Length();
		return Length();
	}
	return -1;
}


int CVL1String::SetAt(char ch, int i)
{
	if ((i>=0) && (i<m_index))
	{
		m_str[i] = ch;
		m_index = Length();
		return Length();
	}
	return -1;
}


int CVL1String::StripTrailingZeroes()
{
	int j = Length();
	while ((j>0) && (m_str[j-1]=='0')) j--;
	if (j>0) m_str[j] = '\0';
	j--;
	if ((j>0) && (m_str[j]=='.')) m_str[j] = '\0';
	m_index = Length();
	return Length();
}


int CVL1String::StripDot()
{
	int dot = -1;
	int j = 0;
	for (int i=0; i<Length(); i++)
	{
		if (m_str[i]!='.') m_str[j++] = m_str[i];
		else dot = i;
	}
	m_str[j] = '\0';
	m_index = Length();
	return dot;
}


int CVL1String::GetDot()
{
	for (int i=0; i<Length(); i++)
	{
		if (m_str[i]=='.') return i;
	}
	return -1;
}


int CVL1String::GetDotRev()
{
	for (int i=Length()-1; i>=0; i--)
	{
		if (m_str[i]=='.') return i;
	}
	return -1;
}


bool CVL1String::IsInteger()
{
	if (strchr(m_str,'.')==nullptr) return true;
	for (int i=Length()-1; i>=0; i--)
	{
		if ((m_str[i]=='.') || (m_str[i]==' ') || (m_str[i]=='-') || (m_str[i]=='+')) return true;
		if (m_str[i]!='0') return false;
	}
	return true;
}


CVL1String& CVL1String::operator=(CVL1String& str)
{
	strcpy(m_str,str.Get());
	m_index = Length();
	return *this;
}


int CVL1String::SetFromDouble(double d, bool bStripTrailingZeroes, int maxDigits, bool bRound)
{
	int digits = 0;
	if (fabs(d)<1.0) digits = 1;
	else
	{
		double d2 = 1.0;
		while (fabs(d)>d2)
		{
			digits++;
			d2 *= 10.0;
		}
	}
	if (!bRound) maxDigits++;
	m_index = sprintf(m_str,"% 0*.*f",maxDigits,maxDigits-digits,d);
	if (!bRound) m_str[m_index-1] = '\0';
	if (bStripTrailingZeroes) StripTrailingZeroes();
	return Length();
}


int CVL1String::SetFromFloat(float d, bool bStripTrailingZeroes, int maxDigits, bool bRound)
{
	int digits = 0;
	if (fabsf(d)<1.0f) digits = 1;
	else
	{
		float d2 = 1.0f;
		while (fabsf(d)>d2)
		{
			digits++;
			d2 *= 10.0f;
		}
	}
	if (!bRound) maxDigits++;
	m_index = sprintf(m_str,"% 0*.*f",maxDigits,maxDigits-digits,d);
	if (!bRound) m_str[m_index-1] = '\0';
	if (bStripTrailingZeroes) StripTrailingZeroes();
	return Length();
}

// Ignores the dot!
unsigned int CVL1String::GetAsUlong()
{
	unsigned int result = 0;
	int weight = 1;
	for (int i=Length()-1; i>=0; i--)
	{
		if (isdigit((unsigned char)m_str[i]))
		{
			result += (m_str[i]-'0')*weight;
			weight *= 10;
		}
		else if ((m_str[i]==' ') || (m_str[i]=='-')) break;
	}
	return result;
}


void CVL1String::Test()
{
	SetFromDouble(sqrt(2.0),8,true);
	SetFromDouble(-sqrt(2.0),8,false);
	SetFromDouble(-sqrt(2.0)+1,8,false);
	SetFromDouble(-sqrt(2.0)+2,8,false);
	strcpy(m_str,"-1.890000");
	StripTrailingZeroes();
	strcpy(m_str," 120.890000");
	StripTrailingZeroes();
}
