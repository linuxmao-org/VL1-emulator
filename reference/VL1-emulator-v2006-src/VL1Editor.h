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
	CKnob *m_pTune;

	BOOL AddKey(int id, int idBmp, int x, int y, int n, CKickButton **ppKey);
	BOOL AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, CHorizontalSwitch **ppControl);
	BOOL AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, CHorizontalSlider **ppControl);
	
	void HandleKey(int key, float value);
	void SendKey(int byte1, int byte2, int byte3);

	CKickButton *m_pBlackWhiteKey[29]; // 17 white + 12 black keys
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
	//int m_mode;
	BOOL m_bSelectRhythm;
};

#endif
