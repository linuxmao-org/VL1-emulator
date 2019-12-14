#ifndef __VL1Editor
#include "VL1Editor.h"
#endif

#ifndef __VL1_H__
#include "VL1.h"
#endif

#include <stdio.h>

#include "GlobalData.h"


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

	kKeyResetId = 199,
	kKeyResetX = 455,
	kKeyResetY = 67,

	kKeyDelId = 200,
	kKeyDelX = 491,
	kKeyDelY = 67,

	kKeyTempoUpId = 201,
	kKeyTempoUpX = 528,
	kKeyTempoUpY = 67,

	kKeyTempoDownId = 202,
	kKeyTempoDownX = 565,
	kKeyTempoDownY = 67,

	kKeyRhythmId = 203,
	kKeyRhythmX = 602,
	kKeyRhythmY = 67,

	kKeyMLCId = 204,
	kKeyMLCX = 639,
	kKeyMLCY = 67,

	kKeyMusicId = 205,
	kKeyMusicX = 676,
	kKeyMusicY = 67,

	kKeyAutoPlayId = 206,
	kKeyAutoPlayX = 712,
	kKeyAutoPlayY = 67,

	kKeyOneKeyPlayDotDotId = 207,
	kKeyOneKeyPlayDotDotX = 794,
	kKeyOneKeyPlayDotDotY = 56,

	kKeyOneKeyPlayDotId = 208,
	kKeyOneKeyPlayDotX = 837,
	kKeyOneKeyPlayDotY = 56,

	kTuneBodyId = 0,
	kTuneHandleId = 0,
	kTuneX = 0,
	kTuneY = 0,

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

//-----------------------------------------------------------------------------
// prototype string convert float -> percent
void percentStringConvert (float value, char* string);
void percentStringConvert (float value, char* string)
{
	 sprintf (string, "%d%%", (int)(100 * value + 0.5f));
}


float KeyToRhythm(int key)
{
	switch (key)
	{
		case kKey0: // B4 or 0
			return 0.0f;

		case kKey1: // C5 or 1
			return 0.1f;

		case kKey2: // D5 or 2
			return 0.2f;

		case kKey3: // E5 or 3
			return 0.3f;

		case kKey4: // F5 or 4
			return 0.4f;

		case kKey5: // G5 or 5
			return 0.5f;

		case kKey6: // A5 or 6
			return 0.6f;

		case kKey7: // B5 or 7
			return 0.7f;

		case kKey8: // C6 or 8
			return 0.8f;

		case kKey9: // D6 or 9
			return 0.9f;
	}

	return -1.0f;
}



//-----------------------------------------------------------------------------
// VL1Editor class implementation
//-----------------------------------------------------------------------------
VL1Editor::VL1Editor (AudioEffect *effect) : 
	AEffGUIEditor (effect)
{
	m_bOpened = false;

	m_pProgramSelector = NULL;
	m_pOctave = NULL;
	m_pMode = NULL;
	m_pVolume = NULL;
	m_pBalance = NULL;
	m_pTune = NULL;

	memset(m_pBlackWhiteKey,0,sizeof(m_pBlackWhiteKey));

	m_pKeyReset = NULL;
	m_pKeyDel = NULL;
	m_pKeyTempoUp = NULL;
	m_pKeyTempoDown = NULL;
	m_pKeyRhythm = NULL;
	m_pKeyMLC = NULL;
	m_pKeyMusic = NULL;
	m_pKeyAutoPlay = NULL;
	m_pKeyOneKeyPlay2 = NULL;
	m_pKeyOneKeyPlay1 = NULL;

	// load the background bitmap
	// we don't need to load all bitmaps, this could be done when open is called
	m_hBackground = new CBitmap(kBackgroundId);

	// init the size of the plugin
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = (short)m_hBackground->getWidth ();
	rect.bottom = (short)m_hBackground->getHeight ();

	m_bSelectRhythm = FALSE;
}

//-----------------------------------------------------------------------------
VL1Editor::~VL1Editor ()
{
	// free the background bitmap
	if (m_hBackground) m_hBackground->forget();
	m_hBackground = NULL;
}


//-----------------------------------------------------------------------------
BOOL VL1Editor::AddKey(int id, int idBmp, int x, int y, int nBmp, CKickButton **ppControl)
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
BOOL VL1Editor::AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, CHorizontalSwitch **ppControl)
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
BOOL VL1Editor::AddHorizontalSlider(int id, int idBody, int idHandle, int x, int y, CHorizontalSlider **ppControl)
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
long VL1Editor::open (void *ptr)
{
	// !!! always call this !!!
	AEffGUIEditor::open (ptr);
	
	// Init background frame
	CRect rect(0,0,m_hBackground->getWidth(),m_hBackground->getHeight());
	frame = new CFrame (rect,ptr,this);
	frame->setBackground(m_hBackground);

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

	// Tune control
	//if (AddKnob(kTune,kTuneBodyId,kTuneHandleId,kTuneX,kTuneY,&m_pTune))
	//{
	//	m_pTune->setValue(effect->getParameter(kTune));
	//}

	// Keyboard
	AddKey(kKeyPlusMin,kKeyPlusMinId,kKeyPlusMinX,kKeyPlusMinY,kKeyN,&m_pBlackWhiteKey[0]);
	AddKey(kKeyPlusMinS,kKeyG0sId,kKeyG0sX,kKeyG0sY,kKeyN,&m_pBlackWhiteKey[1]);
	AddKey(kKeyDot,kKeyDotId,kKeyDotX,kKeyDotY,kKeyN,&m_pBlackWhiteKey[2]);
	AddKey(kKeyDotS,kKeyA0sId,kKeyA0sX,kKeyA0sY,kKeyN,&m_pBlackWhiteKey[3]);
	AddKey(kKey0,kKey0Id,kKey0X,kKey0Y,kKeyN,&m_pBlackWhiteKey[4]);
	AddKey(kKey1,kKey1Id,kKey1X,kKey1Y,kKeyN,&m_pBlackWhiteKey[5]);
	AddKey(kKey1S,kKeyC1sId,kKeyC1sX,kKeyC1sY,kKeyN,&m_pBlackWhiteKey[6]);
	AddKey(kKey2,kKey2Id,kKey2X,kKey2Y,kKeyN,&m_pBlackWhiteKey[7]);
	AddKey(kKey2S,kKeyD1sId,kKeyD1sX,kKeyD1sY,kKeyN,&m_pBlackWhiteKey[8]);
	AddKey(kKey3,kKey3Id,kKey3X,kKey3Y,kKeyN,&m_pBlackWhiteKey[9]);
	AddKey(kKey4,kKey4Id,kKey4X,kKey4Y,kKeyN,&m_pBlackWhiteKey[10]);
	AddKey(kKey4S,kKeyF1sId,kKeyF1sX,kKeyF1sY,kKeyN,&m_pBlackWhiteKey[11]);
	AddKey(kKey5,kKey5Id,kKey5X,kKey5Y,kKeyN,&m_pBlackWhiteKey[12]);
	AddKey(kKey5S,kKeyG1sId,kKeyG1sX,kKeyG1sY,kKeyN,&m_pBlackWhiteKey[13]);
	AddKey(kKey6,kKey6Id,kKey6X,kKey6Y,kKeyN,&m_pBlackWhiteKey[14]);
	AddKey(kKey6S,kKeyA1sId,kKeyA1sX,kKeyA1sY,kKeyN,&m_pBlackWhiteKey[15]);
	AddKey(kKey7,kKey7Id,kKey7X,kKey7Y,kKeyN,&m_pBlackWhiteKey[16]);
	AddKey(kKey8,kKey8Id,kKey8X,kKey8Y,kKeyN,&m_pBlackWhiteKey[17]);
	AddKey(kKey8S,kKeyC2sId,kKeyC2sX,kKeyC2sY,kKeyN,&m_pBlackWhiteKey[18]);
	AddKey(kKey9,kKey9Id,kKey9X,kKey9Y,kKeyN,&m_pBlackWhiteKey[19]);
	AddKey(kKey9S,kKeyD2sId,kKeyD2sX,kKeyD2sY,kKeyN,&m_pBlackWhiteKey[20]);
	AddKey(kKeyDiv,kKeyDivId,kKeyDivX,kKeyDivY,kKeyN,&m_pBlackWhiteKey[21]);
	AddKey(kKeyMul,kKeyMulId,kKeyMulX,kKeyMulY,kKeyN,&m_pBlackWhiteKey[22]);
	AddKey(kKeyMulS,kKeyF2sId,kKeyF2sX,kKeyF2sY,kKeyN,&m_pBlackWhiteKey[23]);
	AddKey(kKeySub,kKeySubId,kKeySubX,kKeySubY,kKeyN,&m_pBlackWhiteKey[24]);
	AddKey(kKeySubS,kKeyG2sId,kKeyG2sX,kKeyG2sY,kKeyN,&m_pBlackWhiteKey[25]);
	AddKey(kKeyAdd,kKeyAddId,kKeyAddX,kKeyAddY,kKeyN,&m_pBlackWhiteKey[26]);
	AddKey(kKeyAddS,kKeyA2sId,kKeyA2sX,kKeyA2sY,kKeyN,&m_pBlackWhiteKey[27]);
	AddKey(kKeyEqual,kKeyEqualId,kKeyEqualX,kKeyEqualY,kKeyN,&m_pBlackWhiteKey[28]);

	// Small keys
	AddKey(kKeyReset,kKeyResetId,kKeyResetX,kKeyResetY,kKeyN,&m_pKeyReset);
	AddKey(kKeyDel,kKeyDelId,kKeyDelX,kKeyDelY,kKeyN,&m_pKeyDel);
	AddKey(kKeyTempoUp,kKeyTempoUpId,kKeyTempoUpX,kKeyTempoUpY,kKeyN,&m_pKeyTempoUp);
	AddKey(kKeyTempoDown,kKeyTempoDownId,kKeyTempoDownX,kKeyTempoDownY,kKeyN,&m_pKeyTempoDown);
	AddKey(kKeyRhythm,kKeyRhythmId,kKeyRhythmX,kKeyRhythmY,kKeyN,&m_pKeyRhythm);
	AddKey(kKeyMLC,kKeyMLCId,kKeyMLCX,kKeyMLCY,kKeyN,&m_pKeyMLC);
	AddKey(kKeyMusic,kKeyMusicId,kKeyMusicX,kKeyMusicY,kKeyN,&m_pKeyMusic);
	AddKey(kKeyAutoPlay,kKeyAutoPlayId,kKeyAutoPlayX,kKeyAutoPlayY,kKeyN,&m_pKeyAutoPlay);
	AddKey(kKeyOneKeyPlayDotDot,kKeyOneKeyPlayDotDotId,kKeyOneKeyPlayDotDotX,kKeyOneKeyPlayDotDotY,kKeyN,&m_pKeyOneKeyPlay1);
	AddKey(kKeyOneKeyPlayDot,kKeyOneKeyPlayDotId,kKeyOneKeyPlayDotX,kKeyOneKeyPlayDotY,kKeyN,&m_pKeyOneKeyPlay2);

	// Display
	gLCD.OpenDisplay(this,frame);

	m_bOpened = true;

	return true;
}

//-----------------------------------------------------------------------------
void VL1Editor::close ()
{
	m_bOpened = false;

	gLCD.CloseDisplay();

	delete frame;
	frame = 0;
}

//-----------------------------------------------------------------------------
void VL1Editor::setParameter (long index, float value)
{
	if (!m_bOpened) return;

	// called from VL1Edit
	switch (index)
	{
		case kVolume:
			if (m_pVolume) m_pVolume->setValue(effect->getParameter(index));
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

		case kTune:
			if (m_pTune) m_pTune->setValue(effect->getParameter(index));
			break;

		default:
			if (index>=kKeyPlusMin && index<=kKeyEqual)
			{
				if (m_pBlackWhiteKey[index-kKeyPlusMin])
				{
					m_pBlackWhiteKey[index-kKeyPlusMin]->setValue(value);
				}
			}
	}
	
	postUpdate ();
}

//-----------------------------------------------------------------------------
void VL1Editor::valueChanged(CDrawContext *pContext, CControl *pControl)
{
	long tag = pControl->getTag();
	float value = pControl->getValue();

	switch (tag)
	{
		case kTune: // Control not yet implemented.
		case kMode:
		case kProgram:
		case kOctave:
		case kBalance:
		case kVolume:
		case kKeyOneKeyPlayDotDot:
		case kKeyOneKeyPlayDot:
			effect->setParameterAutomated(tag,value);
			break;

		case kKeyReset:
		case kKeyDel:
		case kKeyTempoUp:
		case kKeyTempoDown:
		case kKeyMLC:
		case kKeyMusic:
		case kKeyAutoPlay:
			// Key down only.
			if (value!=0) effect->setParameterAutomated(tag,value);
			break;

		case kKeyRhythm:
			if (value!=0)
			{
				// Key down only.
				if (!m_bSelectRhythm)
				{
					// Two key sequence, step one.
					m_bSelectRhythm = TRUE;
				}
			}
			break;

		default:
			if (tag>=kKeyPlusMin && tag<=kKeyEqual)
			{
				// Black and white keys only.
				if (m_bSelectRhythm)
				{
					// Key down only.
					if (value!=0)
					{
						// Two key sequence, step two.
						m_bSelectRhythm = FALSE;
						value = KeyToRhythm(tag);
						if (value>=0) effect->setParameterAutomated(kKeyRhythm,value);
					}
				}
				// Key up and down.
				else ((CVL1*)effect)->HandleKey(tag,value);
			}
	}
}
