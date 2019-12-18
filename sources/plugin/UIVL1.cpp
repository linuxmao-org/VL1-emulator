#include "UIVL1.h"
#include "UIVL1Defs.h"
#include "PluginVL1.h"
#include "Window.hpp"
#include "Sequencer.h"
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
	: UI(getBackgroundSize().getWidth(), getBackgroundSize().getHeight()),
	  m_parameterValues(new float[kNumParams])
{
	PluginVL1 *dsp = getDsp();
	const CSharedData *pShared = dsp->GetSharedData();

	for (uint32_t p=0; p<kNumParams; ++p)
	{
		m_parameterValues[p] = pShared->parameterRanges[p].def;
	}

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
	m_subWidgets.emplace_back(m_lcd);
	m_lcd->setSize(getWidth(), getHeight());
}

UIVL1::~UIVL1()
{
}

PluginVL1 *UIVL1::getDsp() const
{
	return static_cast<PluginVL1 *>(
		reinterpret_cast<Plugin *>(getPluginInstancePointer()));
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIVL1::parameterChanged(uint32_t index, float value)
{
	float *pValues = m_parameterValues.get();

	pValues[index] = value;

	switch (index)
	{
		case kVolume:
			m_pVolume->setValue(value);
			break;

		case kBalance:
			m_pBalance->setValue(value);
			break;

		case kOctave:
			m_pOctave->setValue(value);
			break;

		case kMode:
			m_pMode->setValue(value);
			break;

		case kTune:
			// m_pTune->setValue(value);
			break;
	}

	// jpc: to handle the program button: if the parameter set has its ADSR
	//      equal to one of the presets, set the button to this position,
	//      otherwise set it to ADSR.
	int programSelection = -1;
	for (unsigned i = 0; i < kNumPrograms && programSelection == -1; ++i)
	{
		const CVL1Program &program = SharedVL1::GetFactoryPresets()[i];
		bool bIsSame = true;
		for (unsigned p = 0; p < kNumParams && bIsSame; ++p)
		{
			float value = program.GetParameter(p, HUGE_VALF);
			bIsSame = (value == HUGE_VALF) || (pValues[p] == value);
		}
		if (bIsSame)
		{
			programSelection = i;
		}
	}
	if (programSelection == -1)
		programSelection = kProgramAdsr;
	m_pProgramSelector->setValue(
		programSelection * (1.0 / (kNumPrograms - 1)), CControl::kDoNotNotify);
}

/**
  A program has been loaded on the plugin side.
  This is called by the host to inform the UI about program changes.
*/
void UIVL1::programLoaded(uint32_t index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index < kNumPrograms, );

	m_curProgram = index;

	const CVL1Program &program = SharedVL1::GetFactoryPresets()[index];
	const tParameterRange *ranges = getDsp()->GetSharedData()->parameterRanges;

	for (uint32_t i = 0; i < kNumParams; i++)
	{
		// set values for each parameter and update their widgets
		float value = program.GetParameter(i, ranges[i].def);
		parameterChanged(i, value);
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
	PluginVL1 *dsp = getDsp();

	m_lcd->Show(dsp->GetLcdScreenData());
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

static float KeyToRhythm(int key)
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

// -----------------------------------------------------------------------

void UIVL1::controlValueChanged(CControl &control)
{
	long tag = control.getTag();
	double value = control.getValue();

	switch (tag)
	{
		case kProgram:
		{
			// jpc: this loads a part of parameters: sound and envelope.
			// if it's the special ADSR program, envelope data is recalled
			// from the calculator memory.

			CVL1Program program;
			int nProgram = (int)lround(value*(kNumPrograms-1));

			if (nProgram != kProgramAdsr)
			{
				program.LoadPreset("", gVL1Preset[nProgram]);
			}
			else
			{
				PluginVL1 *dsp = getDsp();
				tVL1Preset preset;
				dsp->PerformEditSynchronous([dsp, &preset] { dsp->GetAdsrPreset(preset); });
				program.LoadPreset("", preset);
			}

			for (unsigned p = 0; p < kNumParams; ++p)
			{
				float value = program.GetParameter(p, HUGE_VALF);
				if (value != HUGE_VALF)
					setParameterValue(p, value);
			}
		}
		break;

		case kTune: // Control not yet implemented.
		case kMode:
		case kOctave:
		case kBalance:
		case kVolume:
			setParameterValue(tag,value);
			break;

		case kKeyOneKeyPlayDotDot:
		{
			PluginVL1 *dsp = getDsp();
			dsp->PerformEditSynchronous([dsp, value] { dsp->OnOneKeyPlayDotDot(value); });
		}
		break;

		case kKeyOneKeyPlayDot:
		{
			PluginVL1 *dsp = getDsp();
			dsp->PerformEditSynchronous([dsp, value] { dsp->OnOneKeyPlayDot(value); });
		}
		break;

		case kKeyTempoUp:
		case kKeyTempoDown:
			// Key down only.
			if (value!=0)
			{
				PluginVL1 *dsp = getDsp();
				int mode = dsp->GetModeI();

				// jpc: tempo parameter must be changed from Editor
				if (mode==kVL1Play || mode==kVL1Rec)
				{
					setParameterValue(kTempo, dsp->GetTempoUpDown(tag == kKeyTempoUp));
				}
				else if (mode==kVL1Cal)
				{
					dsp->PerformEditSynchronous([dsp, tag] { dsp->Calculator(tag); });
				}
			}
			break;

		case kKeyReset:
			// Key down only.
			if (value!=0)
			{
				PluginVL1 *dsp = getDsp();
				dsp->PerformEditSynchronous([dsp] { dsp->OnReset(); });
			}
			break;

		case kKeyDel:
			// Key down only.
			if (value!=0)
			{
				PluginVL1 *dsp = getDsp();
				dsp->PerformEditSynchronous([dsp] { dsp->OnDel(); });
			}
			break;

		case kKeyMLC:
			// Key down only.
			if (value!=0)
			{
				PluginVL1 *dsp = getDsp();
				int mode = dsp->GetModeI();

				// jpc: tempo parameter must be changed from Editor
				if (mode==kVL1Rec)
				{
					if (!dsp->IsPlayingDemoSong())
					{
						setParameterValue(kTempo,0.5f); // tempo = 0

						dsp->PerformEditSynchronous([dsp]
						{
							dsp->Reset();
							dsp->GetSequencer()->Clear();
						});
					}
				}
				else if (mode==kVL1Cal)
				{
					dsp->PerformEditSynchronous([dsp] { dsp->Calculator(kKeyMLC); });
				}
			}
			break;

		case kKeyMusic:
			// Key down only.
			if (value!=0)
			{
				// jpc: need to this change this parameter from Editor
				setParameterValue(kTempo,0.725f); // tempo = 4

				PluginVL1 *dsp = getDsp();
				dsp->PerformEditSynchronous([dsp] { dsp->OnMusic(); });
			}
			break;

		case kKeyAutoPlay:
			// Key down only.
			if (value!=0)
			{
				PluginVL1 *dsp = getDsp();
				dsp->PerformEditSynchronous([dsp] { dsp->OnAutoPlay(); });
			}
			break;

		case kKeyRhythm:
			// Key down only.
			if (value!=0)
			{
				// Key down only.
				if (!m_bSelectRhythm)
				{
					// Two key sequence, step one.
					m_bSelectRhythm = true;
				}
			}
			break;

		default:
			if (tag>=kKeyPlusMin && tag<=kKeyEqual)
			{
				PluginVL1 *dsp = getDsp();

				// Black and white keys only.
				if (m_bSelectRhythm)
				{
					// Key down only.
					if (value!=0)
					{
						// Two key sequence, step two.
						m_bSelectRhythm = false;
						value = KeyToRhythm(tag);
						if (value>=0)
							dsp->PerformEditSynchronous([dsp, value] { dsp->OnRhythm(value); });
					}
				}
				// Key up and down.
				else
					dsp->PerformEditSynchronous([dsp, tag, value] { dsp->HandleKey(tag, value); });
			}
	}
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
	key->setTag(id);
	key->addListener(this);
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
	sw->setTag(id);
	sw->addListener(this);
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
	slider->setTag(id);
	slider->addListener(this);
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
