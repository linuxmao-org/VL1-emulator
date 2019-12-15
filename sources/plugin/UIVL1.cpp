#include "UIVL1.h"
#include "UIVL1Defs.h"
#include "Window.hpp"
#include "VL1Program.h"
#include "resource.h"
#include "ui/BitmapCache.h"
#include "ui/KickButton.h"
#include "ui/MultiSwitch.h"
#include "ui/Slider.h"
#include "ui/Lcd.h"
#include <assert.h>

// -----------------------------------------------------------------------
// Init / Deinit

UIVL1::UIVL1()
	: UI(getBackgroundSize().getWidth(), getBackgroundSize().getHeight())
{
	// Program Select switch
	AddHorizontalSwitch(kProgram,kProgSelId,kProgSelX,kProgSelY,kProgSelN,kProgSelN,&m_pProgramSelector);

	// Octave switch
	AddHorizontalSwitch(kOctave,kOctaveId,kOctaveX,kOctaveY,kOctaveN,kOctaveN,&m_pOctave);

	// Mode switch
	AddHorizontalSwitch(kMode,kModeId,kModeX,kModeY,kModeN,kModeN,&m_pMode);

	// Volume slider
	AddHorizontalSlider(kVolume,kVolumeBodyId,kVolumeHandleId,kVolumeX,kVolumeY,&m_pVolume);

	// Balance slider
	AddHorizontalSlider(kBalance,kBalanceBodyId,kBalanceHandleId,kBalanceX,kBalanceY,&m_pBalance);

	// Tune control
	//AddKnob(kTune,kTuneBodyId,kTuneHandleId,kTuneX,kTuneY,&m_pTune);

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
	m_lcd = new CLcd(this);
	m_lcd->setSize(getWidth(), getHeight());
}

UIVL1::~UIVL1()
{
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIVL1::parameterChanged(uint32_t index, float value)
{
	switch (index)
	{
#pragma message("TODO implement me")
		default:
			(void)value;
	}
}

/**
  A program has been loaded on the plugin side.
  This is called by the host to inform the UI about program changes.
*/
void UIVL1::programLoaded(uint32_t index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	const CVL1Program &program = SharedVL1::GetFactoryPresets()[index];

	for (uint32_t i = 0; i < kNumParams; i++)
	{
		// set values for each parameter and update their widgets
		parameterChanged(i, program.GetParameter(i));
	}
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIVL1::sampleRateChanged(double newSampleRate)
{
	(void)newSampleRate;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIVL1::uiIdle()
{
}

/**
  Window reshape function, called when the parent window is resized.
*/
void UIVL1::uiReshape(uint width, uint height)
{
	(void)width;
	(void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UIVL1::onDisplay()
{
	cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

	cairo_surface_t *hBackground = BitmapCache::load(kBackgroundId);

	cairo_set_source_surface(cr, hBackground, 0, 0);
	cairo_paint(cr);
}

// -----------------------------------------------------------------------
// Optional widget callbacks; return true to stop event propagation, false otherwise.

/**
  A function called when a key is pressed or released.
*/
bool UIVL1::onKeyboard(const KeyboardEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when a special key is pressed or released.
*/
bool UIVL1::onSpecial(const SpecialEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when a mouse button is pressed or released.
*/
bool UIVL1::onMouse(const MouseEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called when the mouse pointer moves.
*/
bool UIVL1::onMotion(const MotionEvent &ev)
{
	return false;
	(void)ev;
}

/**
  A function called on scrolling (e.g. mouse wheel or track pad).
*/
bool UIVL1::onScroll(const ScrollEvent &ev)
{
	return false;
	(void)ev;
}

// -----------------------------------------------------------------------

void UIVL1::AddKey(int id, int idBmp, int x, int y, int nBmp, KickButton **ppKey)
{
	assert(ppKey);
	cairo_surface_t *hBmp = BitmapCache::load(idBmp);
	ImageSkin skin(hBmp, nBmp);
	KickButton *key = new KickButton(skin, this);
	m_subWidgets.emplace_back(key);
	key->setAbsolutePos(x, y);
	*ppKey = key;
}

void UIVL1::AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, MultiSwitch **ppControl)
{
	assert(ppControl);
	cairo_surface_t *hBmp = BitmapCache::load(idBmp);
	ImageSkin skin(hBmp, nBmp);
	MultiSwitch *sw = new MultiSwitch(skin, this);
	m_subWidgets.emplace_back(sw);
	sw->setAbsolutePos(x, y);
	sw->setNumSteps(nPos);
	*ppControl = sw;
}

void UIVL1::AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, Slider **ppControl)
{
	assert(ppControl);
	cairo_surface_t *hBmpBody = BitmapCache::load(idBmpBody);
	cairo_surface_t *hBmpHandle = BitmapCache::load(idBmpHandle);
	Slider *slider = new Slider(hBmpBody, hBmpHandle, this);
	m_subWidgets.emplace_back(slider);
	slider->setAbsolutePos(x, y);
	*ppControl = slider;
}

// -----------------------------------------------------------------------

Size<uint> UIVL1::getBackgroundSize()
{
	cairo_surface_t *img = BitmapCache::load(kBackgroundId);
	return Size<uint>(
		cairo_image_surface_get_width(img),
		cairo_image_surface_get_height(img));
}

// -----------------------------------------------------------------------

UI *DISTRHO::createUI()
{
	return new UIVL1();
}
