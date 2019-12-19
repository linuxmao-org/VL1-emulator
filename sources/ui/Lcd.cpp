/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "ui/Lcd.h"
#include "ui/ImageLabel.h"
#include "ui/ImageSkin.h"
#include "ui/BitmapCache.h"
#include "VL1Defs.h"
#include <string.h>


enum
{
	kLcdX = 243,
	kLcdY = 32,
	kCol1 = 1,
	kRow1 = 2,
	kRow2 = 11,
	kDeltaChar = 14,

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


CLcd::CLcd(Widget *pGroup)
	: Widget(pGroup)
{
	Initialize();
	Open(pGroup);
}


CLcd::~CLcd()
{
	Close();
}


void CLcd::Initialize()
{
	m_bOpen = false;
	m_pE = nullptr;
	m_pM = nullptr;
	m_pK = nullptr;
	m_pMul = nullptr;
	m_pDiv = nullptr;
	m_pAdd = nullptr;
	m_pSub = nullptr;
	memset(m_pSharp,0,kLcdMaxSharp*sizeof(m_pSharp[0]));
	memset(m_pChars,0,kLcdMaxChar*sizeof(m_pChars[0]));
	memset(m_pDot,0,kLcdMaxDot*sizeof(m_pDot[0]));
}


bool CLcd::AddChar(int id, int idBmp, int x, int y, int nBmp, ImageLabel **ppControl, Widget *pGroup)
{
	if ((!ppControl) || (!pGroup)) return false;
	cairo_surface_t *hBmp = BitmapCache::load(idBmp);
	if (!hBmp) return false;
	ImageSkin skin(hBmp, nBmp);
	ImageLabel *label = new ImageLabel(skin, this);
	m_subWidgets.emplace_back(label);
	label->setAbsolutePos(x, y);
	*ppControl = label;
	return true;
}


void CLcd::onDisplay()
{
}


void CLcd::Open(Widget *pGroup)
{
	AddChar(kChar1,kCharsId,kChar1X,kChar1Y,16,&m_pChars[0],pGroup);
	AddChar(kChar2,kCharsId,kChar2X,kChar2Y,16,&m_pChars[1],pGroup);
	AddChar(kChar3,kCharsId,kChar3X,kChar3Y,16,&m_pChars[2],pGroup);
	AddChar(kChar4,kCharsId,kChar4X,kChar4Y,16,&m_pChars[3],pGroup);
	AddChar(kChar5,kCharsId,kChar5X,kChar5Y,16,&m_pChars[4],pGroup);
	AddChar(kChar6,kCharsId,kChar6X,kChar6Y,16,&m_pChars[5],pGroup);
	AddChar(kChar7,kCharsId,kChar7X,kChar7Y,16,&m_pChars[6],pGroup);
	AddChar(kChar8,kCharsId,kChar8X,kChar8Y,16,&m_pChars[7],pGroup);
	AddChar(kChar9,kCharsId,kChar9X,kChar9Y,16,&m_pChars[8],pGroup);
	AddChar(kDot1,kDotId,kChar2X+kDotX,kChar2Y+kDotY,2,&m_pDot[0],pGroup);
	AddChar(kDot2,kDotId,kChar3X+kDotX,kChar3Y+kDotY,2,&m_pDot[1],pGroup);
	AddChar(kDot3,kDotId,kChar4X+kDotX,kChar4Y+kDotY,2,&m_pDot[2],pGroup);
	AddChar(kDot4,kDotId,kChar5X+kDotX,kChar5Y+kDotY,2,&m_pDot[3],pGroup);
	AddChar(kDot5,kDotId,kChar6X+kDotX,kChar6Y+kDotY,2,&m_pDot[4],pGroup);
	AddChar(kDot6,kDotId,kChar7X+kDotX,kChar7Y+kDotY,2,&m_pDot[5],pGroup);
	AddChar(kDot7,kDotId,kChar8X+kDotX,kChar8Y+kDotY,2,&m_pDot[6],pGroup);
	AddChar(kDot8,kDotId,kChar9X+kDotX,kChar9Y+kDotY,2,&m_pDot[7],pGroup);
	AddChar(kAdd,kAddId,kAddX,kAddY,2,&m_pAdd,pGroup);
	AddChar(kSub,kSubId,kSubX,kSubY,2,&m_pSub,pGroup);
	AddChar(kMul,kMulId,kMulX,kMulY,2,&m_pMul,pGroup);
	AddChar(kDiv,kDivId,kDivX,kDivY,2,&m_pDiv,pGroup);
	AddChar(kSharp1,kSharp1Id,kSharp1X,kSharp1Y,2,&m_pSharp[0],pGroup);
	AddChar(kSharp2,kSharp2Id,kSharp2X,kSharp2Y,2,&m_pSharp[1],pGroup);
	AddChar(kSharp3,kSharp3Id,kSharp3X,kSharp3Y,2,&m_pSharp[2],pGroup);
	AddChar(kM,kMId,kMX,kMY,2,&m_pM,pGroup);
	AddChar(kK,kKId,kKX,kKY,2,&m_pK,pGroup);
	AddChar(kErr,kEId,kEX,kEY,2,&m_pE,pGroup);
	m_bOpen = true;
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


bool CLcd::SetControlValue(ImageLabel *pControl, float value)
{
	if (!m_bOpen || !pControl) return false;
	pControl->setValue(value);
	return true;
}


void CLcd::Show(const tLcdScreenData &sd)
{
	for (int i=0; i<kLcdLine2Size; i++)
	{
		SetControlValue(m_pChars[i],MapChar(sd.line2[i]));
	}

	SetControlValue(m_pSharp[0],MapChar(sd.line1[1]));
	SetControlValue(m_pSharp[1],MapChar(sd.line1[5]));
	SetControlValue(m_pSharp[2],MapChar(sd.line1[9]));

	SetControlValue(m_pE,MapChar(sd.line1[0]));
	SetControlValue(m_pM,MapChar(sd.line1[2]));
	SetControlValue(m_pK,MapChar(sd.line1[3]));
	SetControlValue(m_pDiv,MapChar(sd.line1[4]));
	SetControlValue(m_pMul,MapChar(sd.line1[6]));
	SetControlValue(m_pSub,MapChar(sd.line1[7]));
	SetControlValue(m_pAdd,MapChar(sd.line1[8]));

	unsigned char mask = 0x80;
	unsigned char dot = sd.dot;
	for (int i=0; i<8; i++)
	{
		SetControlValue(m_pDot[i],dot&mask?1.0f:0.0f);
		mask >>= 1;
	}
}
