//-------------------------------------------------------------------------------------------------------
// VSTPlug GUI AppWizard - VL1
//
// Code is based on example from Steinberg VST SDK 2.3
//-------------------------------------------------------------------------------------------------------

#ifndef __VL1Editor
#define __VL1Editor


// include VSTGUI
#ifndef __vstgui__
#include "vstgui.h"
#endif


#include "Utils.h"


//-----------------------------------------------------------------------------
class VL1Editor : public AEffGUIEditor, public CControlListener
{
public:
	VL1Editor(AudioEffect *effect);
	virtual ~VL1Editor();

public:
	virtual long open(void *ptr);
	virtual void close();

	virtual void setParameter(long index, float value);
	virtual void valueChanged(CDrawContext* context, CControl* control);

private:
	// Controls
	CHorizontalSlider *m_pVolume;
	CHorizontalSlider *m_pBalance;
	CHorizontalSwitch *m_pProgramSelector;
	CHorizontalSwitch *m_pOctave;
	CHorizontalSwitch *m_pMode;

	BOOL AddKey(int id, int idBmp, int x, int y, int n, CKickButton **ppKey);
	BOOL AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, CHorizontalSwitch **ppControl);
	BOOL AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, CHorizontalSlider **ppControl);
	
	void HandleKey(int key, float value);
	void SendKey(int byte1, int byte2, int byte3);

	CKickButton *m_pKeyPlusMin;
	CKickButton *m_pKeyPlusMinS;
	CKickButton *m_pKeyDot;
	CKickButton *m_pKeyDotS;
	CKickButton *m_pKey0;
	CKickButton *m_pKey1;
	CKickButton *m_pKey1S;
	CKickButton *m_pKey2;
	CKickButton *m_pKey2S;
	CKickButton *m_pKey3;
	CKickButton *m_pKey4;
	CKickButton *m_pKey4S;
	CKickButton *m_pKey5;
	CKickButton *m_pKey5S;
	CKickButton *m_pKey6;
	CKickButton *m_pKey6S;
	CKickButton *m_pKey7;
	CKickButton *m_pKey8;
	CKickButton *m_pKey8S;
	CKickButton *m_pKey9;
	CKickButton *m_pKey9S;
	CKickButton *m_pKeyDiv;
	CKickButton *m_pKeyMul;
	CKickButton *m_pKeyMulS;
	CKickButton *m_pKeySub;
	CKickButton *m_pKeySubS;
	CKickButton *m_pKeyAdd;
	CKickButton *m_pKeyAddS;
	CKickButton *m_pKeyEqual;

	CKickButton *m_pKeyReset;
	CKickButton *m_pKeyDel;
	CKickButton *m_pKeyTempoUp;
	CKickButton *m_pKeyTempoDown;
	CKickButton *m_pKeyRhythm;
	CKickButton *m_pKeyMLC;
	CKickButton *m_pKeyMusic;
	CKickButton *m_pKeyAutoPlay;
	CKickButton *m_pKeyOneKeyPlay2;
	CKickButton *m_pKeyOneKeyPlay1;
	
	// Bitmap
	CBitmap *m_hBackground;

	// Others
	bool m_bOpened;

	BOOL Serialize(BOOL bRead);
	char m_iniFile[128];

	BOOL m_bSelectRhythm;
	void Reset();
	BOOL m_bIgnoreNextEvent;
	BOOL m_bOneKeyPlay;
	BOOL m_bDemoSong;
	float m_program;
};

#endif
