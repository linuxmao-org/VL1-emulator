#include "VL1Lcd.h"

#ifndef __VL1_H
#include "VL1.hpp"
#endif

#include <stdio.h>


//-----------------------------------------------------------------------------
// resource id's
enum {
	// bitmaps
	kBackgroundId = 150,
	
	// Controls
	kProgSelId = 151,
	kProgSelX = 712,
	kProgSelY = 26,
	kProgSelN = 6,

	kOctaveId = 152,
	kOctaveX = 641,
	kOctaveY = 26,
	kOctaveN = 3,

	kModeId = 153,
	kModeX = 805,
	kModeY = 26,
	kModeN = 4,

	kVolumeBodyId = 154,
	kVolumeHandleId = 155,
	kVolumeX = 412,
	kVolumeY = 26,

	kBalanceBodyId = 156,
	kBalanceHandleId = 157,
	kBalanceX = 523,
	kBalanceY = 26,

	kKeyN = 2,

	// White keys
	kKeyPlusMinId = 158,
	kKeyPlusMinX = 246,
	kKeyPlusMinY = 160,

	kKeyDotId = 159,
	kKeyDotX = 283,
	kKeyDotY = 160,

	kKey0Id = 160,
	kKey0X = 320,
	kKey0Y = 160,

	kKey1Id = 161,
	kKey1X = 356,
	kKey1Y = 160,

	kKey2Id = 162,
	kKey2X = 394,
	kKey2Y = 160,

	kKey3Id = 163,
	kKey3X = 430,
	kKey3Y = 160,

	kKey4Id = 164,
	kKey4X = 467,
	kKey4Y = 160,

	kKey5Id = 165,
	kKey5X = 504,
	kKey5Y = 160,

	kKey6Id = 166,
	kKey6X = 541,
	kKey6Y = 160,

	kKey7Id = 167,
	kKey7X = 578,
	kKey7Y = 160,

	kKey8Id = 168,
	kKey8X = 614,
	kKey8Y = 160,

	kKey9Id = 169,
	kKey9X = 651,
	kKey9Y = 160,

	kKeyDivId = 170,
	kKeyDivX = 688,
	kKeyDivY = 160,

	kKeyMulId = 171,
	kKeyMulX = 725,
	kKeyMulY = 160,

	kKeySubId = 172,
	kKeySubX = 762,
	kKeySubY = 160,

	kKeyAddId = 173,
	kKeyAddX = 799,
	kKeyAddY = 160,

	kKeyEqualId = 174,
	kKeyEqualX = 836,
	kKeyEqualY = 160,

	kKeyG0sId = 175,
	kKeyG0sX = 267,
	kKeyG0sY = 105,

	kKeyA0sId = 176,
	kKeyA0sX = 304,
	kKeyA0sY = 105,

	kKeyC1sId = 177,
	kKeyC1sX = 377,
	kKeyC1sY = 105,

	kKeyD1sId = 178,
	kKeyD1sX = 414,
	kKeyD1sY = 105,

	kKeyF1sId = 179,
	kKeyF1sX = 487,
	kKeyF1sY = 105,

	kKeyG1sId = 180,
	kKeyG1sX = 524,
	kKeyG1sY = 105,

	kKeyA1sId = 181,
	kKeyA1sX = 561,
	kKeyA1sY = 105,

	kKeyC2sId = 182,
	kKeyC2sX = 635,
	kKeyC2sY = 105,

	kKeyD2sId = 183,
	kKeyD2sX = 673,
	kKeyD2sY = 105,

	kKeyF2sId = 184,
	kKeyF2sX = 746,
	kKeyF2sY = 105,

	kKeyG2sId = 185,
	kKeyG2sX = 783,
	kKeyG2sY = 105,

	kKeyA2sId = 186,
	kKeyA2sX = 820,
	kKeyA2sY = 105,

	//kFaderInc = 18,

	//kDisplayX = 50,
	//kDisplayY = 214,
	//kDisplayXWidth = 30,
	//kDisplayHeight = 14
};

#if MOTIF
// resource for MOTIF (format XPM)
#include "casio_vl1_big.xpm"
#include "progsel2.xpm"
#include "octave.xpm"
#include "mode.xpm"
#include "volumeBody.xpm"
#include "volumeHandle.xpm"
#include "balanceBody.xpm"
#include "balanceHandle.xpm"
#include "keyPlusMin.xpm"
#include "keyDot.xpm"
#include "key0.xpm"
#include "key1.xpm"
#include "key2.xpm"
#include "key3.xpm"
#include "key4.xpm"
#include "key5.xpm"
#include "key6.xpm"
#include "key7.xpm"
#include "key8.xpm"
#include "key9.xpm"
#include "keyDiv.xpm"
#include "keyMul.xpm"
#include "keySub.xpm"
#include "keyAdd.xpm"
#include "keyEqual.xpm"
#include "keyG0s.xpm"
#include "keyA0s.xpm"
#include "keyC1s.xpm"
#include "keyD1s.xpm"
#include "keyF1s.xpm"
#include "keyG1s.xpm"
#include "keyA1s.xpm"
#include "keyC2s.xpm"
#include "keyD2s.xpm"
#include "keyF2s.xpm"
#include "keyG2s.xpm"
#include "keyA2s.xpm"

CResTable xpmResources = 
{
  { kBackgroundId, casio_vl1_big },
	{ kProgSelId, progsel2 },
	{ kOctaveId, octave },
	{ kModeId, mode },
	{ kvolumeBodyId, volumeBody },
	{ kvolumeHandleId, volumeHandle },
	{ kbalanceBodyId, balanceBody },
	{ kbalanceHandleId, balanceHandle },
	{ kKeyPlusMin, keyPlusMin },
	{ kKeyDot, keyDot },
	{ kKey0, key0 },
	{ kKey1, key1 },
	{ kKey2, key2 },
	{ kKey3, key3 },
	{ kKey4, key4 },
	{ kKey5, key5 },
	{ kKey6, key6 },
	{ kKey7, key7 },
	{ kKey8, key8 },
	{ kKey9, key9 },
	{ kKeyDiv, keyDiv },
	{ kKeyMul, keyMul },
	{ kKeySub, keySub },
	{ kKeyAdd, keyAdd },
	{ kKeyEqual, keyEqual },
	{ kKeyG0s, key9G0s },
	{ kKeyA0s, key9A0s },
	{ kKeyC1s, key9C1s },
	{ kKeyD1s, key9D1s },
	{ kKeyF1s, key9F1s },
	{ kKeyG1s, key9G1s },
	{ kKeyA1s, key9A1s },
	{ kKeyC2s, key9C2s },
	{ kKeyD2s, key9D2s },
	{ kKeyF2s, key9F2s },
	{ kKeyG2s, key9G2s },
	{ kKeyA2s, key9A2s },
  { 0, 0}
};
#endif


VL1Lcd::VL1Lcd()
{
	m_pSharp1 = NULL;
	m_pSharp2 = NULL;
	m_pSharp3 = NULL;
	m_pM = NULL;
	m_pK = NULL;
	m_pMul = NULL;
	m_pDiv = NULL;
	m_pAdd = NULL;
	m_pSub = NULL;
	m_pChar1 = NULL;
	m_pChar2 = NULL;
	m_pChar3 = NULL;
	m_pChar4 = NULL;
	m_pChar5 = NULL;
	m_pChar7 = NULL;
	m_pChar8 = NULL;
	m_pChar9 = NULL;
}


VL1Lcd::~VL1Lcd()
{
}


//-----------------------------------------------------------------------------
BOOL VL1Lcd::AddChar(int id, int idBmp, int x, int y, int nBmp, CKickButton **ppControl)
{
	if (!ppControl) return FALSE;
	CBitmap *hBmp = new CBitmap(idBmp);
	if (!hBmp) return FALSE;
	int h = hBmp->getHeight()/nBmp;
	*ppControl = new CKickButton(CRect(x,y,x+hBmp->getWidth(),y+h),this,id,h,hBmp,CPoint(0,0));
	if (*ppControl) frame->addView(*ppControl);
	hBmp->forget();
	return *ppControl!=NULL;
}

//-----------------------------------------------------------------------------
BOOL VL1Lcd::AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, CHorizontalSwitch **ppControl)
{
	if (!ppControl) return FALSE;
	CBitmap *hBmp = new CBitmap(idBmp);
	if (!hBmp) return FALSE;
	int h = hBmp->getHeight()/nBmp;
	*ppControl = new CHorizontalSwitch(CRect(x,y,x+hBmp->getWidth(),y+h),this,id,nBmp,h,nPos,hBmp,CPoint(0,0));
	if (*ppControl) frame->addView(*ppControl);
	hBmp->forget();
	return *ppControl!=NULL;
}

//-----------------------------------------------------------------------------
BOOL VL1Lcd::AddHorizontalSlider(int id, int idBody, int idHandle, int x, int y, CHorizontalSlider **ppControl)
{
	if (!ppControl) return FALSE;
	CBitmap *hBmpBody = new CBitmap(idBody);
	CBitmap *hBmpHandle = new CBitmap(idHandle);
	int minPos = x;
	int maxPos = minPos + hBmpBody->getWidth() - hBmpHandle->getWidth() - 1;
	CRect rect(x,y,x+hBmpBody->getWidth(),y+hBmpBody->getHeight());
	*ppControl = new CHorizontalSlider(rect,this,id,minPos,maxPos,hBmpHandle,hBmpBody,CPoint(0,0),kLeft|kHorizontal);
	if (*ppControl)
	{
		(*ppControl)->setOffsetHandle(CPoint(1,0));
		frame->addView(*ppControl);
	}
	hBmpBody->forget();
	hBmpHandle->forget();
	return *ppControl!=NULL;
}

//-----------------------------------------------------------------------------
long VL1Lcd::open (void *ptr)
{
	// !!! always call this !!!
	AEffGUIEditor::open (ptr);
	
	// load some bitmaps
	//CBitmap* hFaderBody   = new CBitmap (kFaderBodyId);
	//CBitmap* hFaderHandle = new CBitmap (kFaderHandleId);

	//--init background frame-----------------------------------------------
	CRect rect(0,0,m_hBackground->getWidth(),m_hBackground->getHeight());
	frame = new CFrame (rect,ptr,this);
	frame->setBackground(m_hBackground);

	//--init the faders------------------------------------------------
	//int minPos = kFaderY;
	//int maxPos = kFaderY + hFaderBody->getHeight () - hFaderHandle->getHeight () - 1;
	//CPoint point (0, 0);
	CPoint offset (1, 0);

	// Talent
	/*rect (kFaderX, kFaderY,
          kFaderX + hFaderBody->getWidth (), kFaderY + hFaderBody->getHeight ());
	talentFader = new CVerticalSlider (rect, this, kVolume, minPos, maxPos, hFaderHandle, hFaderBody, point);
	talentFader->setOffsetHandle (offset);
	talentFader->setValue (effect->getParameter (kVolume));
	frame->addView (talentFader);*/


	//--init the display------------------------------------------------
	// Talent
	/*rect (kDisplayX, kDisplayY,
          kDisplayX + kDisplayXWidth, kDisplayY + kDisplayHeight);
	talentDisplay = new CParamDisplay (rect, 0, kCenterText);
	talentDisplay->setFont (kNormalFontSmall);
	talentDisplay->setFontColor (kWhiteCColor);
	talentDisplay->setBackColor (kBlackCColor);
	talentDisplay->setFrameColor (kBlueCColor);
	talentDisplay->setValue (effect->getParameter (kVolume));
	frame->addView (talentDisplay);*/

	// Program Select switch
	if (AddHorizontalSwitch(kProgram,kProgSelId,kProgSelX,kProgSelY,kProgSelN,kProgSelN,&m_pProgramSelector))
	{
		m_pProgramSelector->setValue(effect->getParameter(kProgram));
	}

	// Octave switch
	if (AddHorizontalSwitch(kOctave,kOctaveId,kOctaveX,kOctaveY,kOctaveN,kOctaveN,&m_pOctave))
	{
		m_pOctave->setValue(effect->getParameter(kOctave));
	}

	// Mode switch
	if (AddHorizontalSwitch(kMode,kModeId,kModeX,kModeY,kModeN,kModeN,&m_pMode))
	{
		m_pMode->setValue(effect->getParameter(kMode));
	}

	// Volume slider
	if (AddHorizontalSlider(kVolume,kVolumeBodyId,kVolumeHandleId,kVolumeX,kVolumeY,&m_pVolume))
	{
		m_pVolume->setValue(effect->getParameter(kVolume));
	}

	// Balance slider
	if (AddHorizontalSlider(kBalance,kBalanceBodyId,kBalanceHandleId,kBalanceX,kBalanceY,&m_pBalance))
	{
		m_pBalance->setValue(effect->getParameter(kBalance));
	}

	// Keyboard
	AddKey(kKeyPlusMin,kKeyPlusMinId,kKeyPlusMinX,kKeyPlusMinY,kKeyN,&m_pKeyPlusMin);
	AddKey(kKeyPlusMinS,kKeyG0sId,kKeyG0sX,kKeyG0sY,kKeyN,&m_pKeyPlusMinS);
	AddKey(kKeyDot,kKeyDotId,kKeyDotX,kKeyDotY,kKeyN,&m_pKeyDot);
	AddKey(kKeyDotS,kKeyA0sId,kKeyA0sX,kKeyA0sY,kKeyN,&m_pKeyDotS);
	AddKey(kKey0,kKey0Id,kKey0X,kKey0Y,kKeyN,&m_pKey0);
	AddKey(kKey1,kKey1Id,kKey1X,kKey1Y,kKeyN,&m_pKey1);
	AddKey(kKey1S,kKeyC1sId,kKeyC1sX,kKeyC1sY,kKeyN,&m_pKey1S);
	AddKey(kKey2,kKey2Id,kKey2X,kKey2Y,kKeyN,&m_pKey2);
	AddKey(kKey2S,kKeyD1sId,kKeyD1sX,kKeyD1sY,kKeyN,&m_pKey2S);
	AddKey(kKey3,kKey3Id,kKey3X,kKey3Y,kKeyN,&m_pKey3);
	AddKey(kKey4,kKey4Id,kKey4X,kKey4Y,kKeyN,&m_pKey4);
	AddKey(kKey4S,kKeyF1sId,kKeyF1sX,kKeyF1sY,kKeyN,&m_pKey4S);
	AddKey(kKey5,kKey5Id,kKey5X,kKey5Y,kKeyN,&m_pKey5);
	AddKey(kKey5S,kKeyG1sId,kKeyG1sX,kKeyG1sY,kKeyN,&m_pKey5S);
	AddKey(kKey6,kKey6Id,kKey6X,kKey6Y,kKeyN,&m_pKey6);
	AddKey(kKey6S,kKeyA1sId,kKeyA1sX,kKeyA1sY,kKeyN,&m_pKey6S);
	AddKey(kKey7,kKey7Id,kKey7X,kKey7Y,kKeyN,&m_pKey7);
	AddKey(kKey8,kKey8Id,kKey8X,kKey8Y,kKeyN,&m_pKey8);
	AddKey(kKey8S,kKeyC2sId,kKeyC2sX,kKeyC2sY,kKeyN,&m_pKey8S);
	AddKey(kKey9,kKey9Id,kKey9X,kKey9Y,kKeyN,&m_pKey9);
	AddKey(kKey9S,kKeyD2sId,kKeyD2sX,kKeyD2sY,kKeyN,&m_pKey9S);
	AddKey(kKeyDiv,kKeyDivId,kKeyDivX,kKeyDivY,kKeyN,&m_pKeyDiv);
	AddKey(kKeyMul,kKeyMulId,kKeyMulX,kKeyMulY,kKeyN,&m_pKeyMul);
	AddKey(kKeyMulS,kKeyF2sId,kKeyF2sX,kKeyF2sY,kKeyN,&m_pKeyMulS);
	AddKey(kKeySub,kKeySubId,kKeySubX,kKeySubY,kKeyN,&m_pKeySub);
	AddKey(kKeySubS,kKeyG2sId,kKeyG2sX,kKeyG2sY,kKeyN,&m_pKeySubS);
	AddKey(kKeyAdd,kKeyAddId,kKeyAddX,kKeyAddY,kKeyN,&m_pKeyAdd);
	AddKey(kKeyAddS,kKeyA2sId,kKeyA2sX,kKeyA2sY,kKeyN,&m_pKeyAddS);
	AddKey(kKeyEqual,kKeyEqualId,kKeyEqualX,kKeyEqualY,kKeyN,&m_pKeyEqual);

	m_bOpened = true;

	return true;
}

//-----------------------------------------------------------------------------
void VL1Lcd::close ()
{
	m_bOpened = false;

	delete frame;
	frame = 0;
}

//-----------------------------------------------------------------------------
void VL1Lcd::setParameter (long index, float value)
{
	if (!m_bOpened)
		return;

	// called from VL1Edit
	switch (index)
	{
		case kVolume:
			if (m_pVolume) m_pVolume->setValue(effect->getParameter(index));
			//if (talentDisplay) talentDisplay->setValue (effect->getParameter (index));
			break;

		case kBalance:
			if (m_pBalance) m_pBalance->setValue(effect->getParameter(index));
			break;

		case kProgram:
			if (m_pProgramSelector) m_pProgramSelector->setValue(effect->getParameter(index));
			break;

		case kOctave:
			if (m_pOctave) m_pOctave->setValue(effect->getParameter(index));
			break;

		case kMode:
			if (m_pMode) m_pMode->setValue(effect->getParameter(index));
			break;
	}
	
	postUpdate ();
}

//-----------------------------------------------------------------------------
void VL1Lcd::valueChanged (CDrawContext* context, CControl* control)
{
	unsigned char velocity = 100;

	long tag = control->getTag();
	float value = control->getValue();

	switch (tag)
	{
		case kVolume:
		case kBalance:
		case kProgram:
		case kOctave:
		case kMode:
			effect->setParameterAutomated(tag,value);
			control->update(context);
			break;

		case kKeyPlusMin: // G4 or "+/-" (octave switch in "middle" position)
			SendKey(value?kNoteOn:kNoteOff,0,velocity);
			break;
		case kKeyPlusMinS: // G#4
			SendKey(value?kNoteOn:kNoteOff,1,velocity);
			break;
		case kKeyDot: // A4 or "."
			SendKey(value?kNoteOn:kNoteOff,2,velocity);
			break;
		case kKeyDotS: // A#4
			SendKey(value?kNoteOn:kNoteOff,3,velocity);
			break;
		case kKey0: // B4 or 0
			SendKey(value?kNoteOn:kNoteOff,4,velocity);
			break;
		case kKey1: // C5 or 1
			SendKey(value?kNoteOn:kNoteOff,5,velocity);
			break;
		case kKey1S: // C#5
			SendKey(value?kNoteOn:kNoteOff,6,velocity);
			break;
		case kKey2: // D5 or 2
			SendKey(value?kNoteOn:kNoteOff,7,velocity);
			break;
		case kKey2S: // D#5
			SendKey(value?kNoteOn:kNoteOff,8,velocity);
			break;
		case kKey3: // E5 or 3
			SendKey(value?kNoteOn:kNoteOff,9,velocity);
			break;
		case kKey4: // F5 or 4
			SendKey(value?kNoteOn:kNoteOff,10,velocity);
			break;
		case kKey4S: // F#5
			SendKey(value?kNoteOn:kNoteOff,11,velocity);
			break;
		case kKey5: // G5 or 5
			SendKey(value?kNoteOn:kNoteOff,12,velocity);
			break;
		case kKey5S: // G#5
			SendKey(value?kNoteOn:kNoteOff,13,velocity);
			break;
		case kKey6: // A5 or 6
			SendKey(value?kNoteOn:kNoteOff,14,velocity);
			break;
		case kKey6S: // A#5
			SendKey(value?kNoteOn:kNoteOff,15,velocity);
			break;
		case kKey7: // B5 or 7
			SendKey(value?kNoteOn:kNoteOff,16,velocity);
			break;
		case kKey8: // C6 or 8
			SendKey(value?kNoteOn:kNoteOff,17,velocity);
			break;
		case kKey8S: // C#6
			SendKey(value?kNoteOn:kNoteOff,18,velocity);
			break;
		case kKey9: // D6 or 9
			SendKey(value?kNoteOn:kNoteOff,19,velocity);
			break;
		case kKey9S: // D#6
			SendKey(value?kNoteOn:kNoteOff,20,velocity);
			break;
		case kKeyDiv: // E6 or ":"
			SendKey(value?kNoteOn:kNoteOff,21,velocity);
			break;
		case kKeyMul: // F6 or "x"
			SendKey(value?kNoteOn:kNoteOff,22,velocity);
			break;
		case kKeyMulS: // F#6
			SendKey(value?kNoteOn:kNoteOff,23,velocity);
			break;
		case kKeySub: // G6 or "-"
			SendKey(value?kNoteOn:kNoteOff,24,velocity);
			break;
		case kKeySubS: // G#6
			SendKey(value?kNoteOn:kNoteOff,25,velocity);
			break;
		case kKeyAdd: // A6 or "+"
			SendKey(value?kNoteOn:kNoteOff,26,velocity);
			break;
		case kKeyAddS: // A#6
			SendKey(value?kNoteOn:kNoteOff,27,velocity);
			break;
		case kKeyEqual: // B6 or "="
			SendKey(value?kNoteOn:kNoteOff,28,velocity);
			break;
	}

}


//-----------------------------------------------------------------------------
void VL1Lcd::SendKey(unsigned char noteOnOff, unsigned char note, unsigned char velocity)
{
	unsigned char offset = 55;

	VstMidiEvent event;
	memset(&event,0,sizeof(event));
	event.type = kVstMidiType;
	event.byteSize = 24;
	event.midiData[0] = noteOnOff;
	event.midiData[1] = note + offset;
	event.midiData[2] = velocity;

	VstEvents events;
	events.events[0] = (VstEvent *)&event;
	events.events[1] = NULL;
	events.numEvents = 1;
	events.reserved = 0;
	((AudioEffectX*)effect)->processEvents(&events);
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
