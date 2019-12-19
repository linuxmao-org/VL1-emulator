/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

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
#include "ui/ImageLabel.h"
#include "ui/Lcd.h"
#include <assert.h>

// -----------------------------------------------------------------------
// Init / Deinit

UIVL1::UIVL1()
	: UI(getBackgroundSize().getWidth(), getBackgroundSize().getHeight()),
	  m_tooltips(new std::unique_ptr<ImageLabel>[kNumTooltips])
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
	m_subWidgets.emplace_back(m_lcd);
	m_lcd->setSize(getWidth(), getHeight());

	// Tooltips
	AddTooltip(kTooltipVolume,kTooltipVolumeId,kTooltipVolumeX,kTooltipVolumeY);
	AddTooltip(kTooltipBalance,kTooltipBalanceId,kTooltipBalanceX,kTooltipBalanceY);
	AddTooltip(kTooltipOctave,kTooltipOctaveId,kTooltipOctaveX,kTooltipOctaveY);
	AddTooltip(kTooltipSound,kTooltipSoundId,kTooltipSoundX,kTooltipSoundY);
	AddTooltip(kTooltipMode,kTooltipModeId,kTooltipModeX,kTooltipModeY);
	AddTooltip(kTooltipReset,kTooltipResetId,kTooltipResetX,kTooltipResetY);
	AddTooltip(kTooltipDel,kTooltipDelId,kTooltipDelX,kTooltipDelY);
	AddTooltip(kTooltipTempoUp,kTooltipTempoUpId,kTooltipTempoUpX,kTooltipTempoUpY);
	AddTooltip(kTooltipTempoDown,kTooltipTempoDownId,kTooltipTempoDownX,kTooltipTempoDownY);
	AddTooltip(kTooltipRhythm,kTooltipRhythmId,kTooltipRhythmX,kTooltipRhythmY);
	AddTooltip(kTooltipMlc,kTooltipMlcId,kTooltipMlcX,kTooltipMlcY);
	AddTooltip(kTooltipMusic,kTooltipMusicId,kTooltipMusicX,kTooltipMusicY);
	AddTooltip(kTooltipAutoPlay,kTooltipAutoPlayId,kTooltipAutoPlayX,kTooltipAutoPlayY);
	AddTooltip(kTooltipOneKeyPlay,kTooltipOneKeyPlayId,kTooltipOneKeyPlayX,kTooltipOneKeyPlayY);
	AddTooltip(kTooltipCalFunctionKeys,kTooltipCalFunctionKeysId,kTooltipCalFunctionKeysX,kTooltipCalFunctionKeysY);
	AddTooltip(kTooltipCalNumericKeys,kTooltipCalNumericKeysId,kTooltipCalNumericKeysX,kTooltipCalNumericKeysY);
	AddTooltip(kTooltipRhythmKeys,kTooltipRhythmKeysId,kTooltipRhythmKeysX,kTooltipRhythmKeysY);
	AddTooltip(kTooltipM,kTooltipMId,kTooltipMX,kTooltipMY);

	for (int i = 0; i < kNumTooltips; ++i)
	{
		m_tooltips[i]->hide();
	}
}

UIVL1::~UIVL1()
{
}

PluginVL1 *UIVL1::getDsp() const
{
	return static_cast<PluginVL1 *>(
		reinterpret_cast<Plugin *>(getPluginInstancePointer()));
}

void UIVL1::setParameterValue01(uint32_t index, float value)
{
	setParameterValue(index, SharedVL1::ParameterValueFrom01(index, value));
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIVL1::parameterChanged(uint32_t index, float value)
{
	value = SharedVL1::ParameterValueTo01(index, value);

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

	for (uint32_t i = 0; i < kNumParams; i++)
	{
		// set values for each parameter and update their widgets
		float value = program.GetParameter(i, HUGE_VALF);
		if (value == HUGE_VALF)
			value = SharedVL1::GetParameterRange(i).def;
		else
			value = SharedVL1::ParameterValueFrom01(i, value);
		parameterChanged(i, value);
	}

	m_pProgramSelector->setValue(
		index * (1.0/(kNumPrograms-1)), CControl::kDoNotNotify);

	PluginVL1 *dsp = getDsp();
	bool isEditingAdsr = (index == kProgramAdsr);
	dsp->PerformEditSynchronous([dsp, isEditingAdsr] { dsp->SetEditingAdsr(isEditingAdsr); });
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

	SetCurrentTooltips();
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
	m_lastMousePosition = ev.pos;
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

			PluginVL1 *dsp = getDsp();
			int nProgram = (int)lround(value*(kNumPrograms-1));

			// jpc: set the flag to indicate whether calculator memory will write ADSR
			bool isEditingAdsr = (nProgram == kProgramAdsr);
			dsp->PerformEditSynchronous([dsp, isEditingAdsr] { dsp->SetEditingAdsr(isEditingAdsr); });

			CVL1Program program;
			if (nProgram != kProgramAdsr)
			{
				program.LoadPreset("", gVL1Preset[nProgram]);
			}
			else
			{
				tVL1Preset preset;
				dsp->PerformEditSynchronous([dsp, &preset]
				{
					memcpy(&preset, dsp->GetAdsrPreset(), sizeof(tVL1Preset));
				});
				program.LoadPreset("", preset);
			}

			for (unsigned p = 0; p < kNumParams; ++p)
			{
				float value = program.GetParameter(p, HUGE_VALF);
				if (value != HUGE_VALF)
					setParameterValue01(p, value);
			}
		}
		break;

		case kTune: // Control not yet implemented.
		case kMode:
		case kOctave:
		case kBalance:
		case kVolume:
			setParameterValue01(tag,value);
			break;

		case kKeyOneKeyPlayDotDot:
		{
			PluginVL1 *dsp = getDsp();

			// jpc: M+ can update ADSR memory in Cal+ADSR mode, so send the
			//      parameter changes accordingly when this happens.

			tVL1Preset preset;
			bool needUpdateAdsr = false;

			dsp->PerformEditSynchronous([dsp, value, &preset, &needUpdateAdsr]
			{
				dsp->OnOneKeyPlayDotDot(value);
				if (dsp->GetModeI()==kVL1Cal && dsp->IsEditingAdsr())
				{
					memcpy(&preset, dsp->GetAdsrPreset(), sizeof(tVL1Preset));
					needUpdateAdsr = true;
				}
			});

			if (needUpdateAdsr)
			{
				CVL1Program program;
				program.LoadPreset("", preset);

				for (unsigned p = 0; p < kNumParams; ++p)
				{
					float value = program.GetParameter(p, HUGE_VALF);
					if (value != HUGE_VALF)
						setParameterValue01(p, value);
				}
			}
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
					setParameterValue01(kTempo, dsp->GetTempoUpDown(tag == kKeyTempoUp));
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
						setParameterValue(kTempo,0); // tempo = 0

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
				setParameterValue(kTempo,4); // tempo = 4

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

void UIVL1::controlBeganChangeGesture(CControl &control)
{
	long tag = control.getTag();

	switch (tag)
	{
		case kTune: // Control not yet implemented.
		case kMode:
		case kOctave:
		case kBalance:
		case kVolume:
			editParameter(tag, true);
			break;
	}
}

void UIVL1::controlEndedChangeGesture(CControl &control)
{
	long tag = control.getTag();

	switch (tag)
	{
		case kTune: // Control not yet implemented.
		case kMode:
		case kOctave:
		case kBalance:
		case kVolume:
			editParameter(tag, false);
			break;
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

void UIVL1::AddTooltip(int id, int idBmp, int x, int y)
{
	cairo_surface_t *hBmp = BitmapCache::load(idBmp);
	ImageSkin skin(hBmp, 1, ImageSkin::kOrientationVertical);
	ImageLabel *label = new ImageLabel(skin, this);
	m_tooltips[id].reset(label);
	label->setAbsolutePos(x, y);
	label->setTag(id);
}

void UIVL1::SetCurrentTooltips()
{
	bool enabled[kNumTooltips] = {};

	int mode = (int)lroundf(SharedVL1::ParameterValueFrom01(kMode, m_pMode->getValue()));

	if (mode != kVL1Off)
	{
		int mX = m_lastMousePosition.getX();
		int mY = m_lastMousePosition.getY();

		struct TipOnHover
		{
			CControl *control;
			unsigned tooltip;
			bool enableInCalMode;
		};

		const TipOnHover onHover[] =
		{
			{m_pVolume, kTooltipVolume, 0},
			{m_pBalance, kTooltipBalance, 0},
			{m_pOctave, kTooltipOctave, 0},
			{m_pProgramSelector, kTooltipSound, 0},
			{m_pMode, kTooltipMode, 1},

			{m_pKeyReset, kTooltipReset, 0},
			{m_pKeyDel, kTooltipDel, 0},
			{m_pKeyTempoUp, kTooltipTempoUp, 0},
			{m_pKeyTempoDown, kTooltipTempoDown, 0},
			{m_pKeyRhythm, kTooltipRhythm, 0},
			{m_pKeyMLC, kTooltipMlc, 0},
			{m_pKeyMusic, kTooltipMusic, 0},
			{m_pKeyAutoPlay, kTooltipAutoPlay, 0},

			{m_pKeyOneKeyPlay1, kTooltipOneKeyPlay, 0},
			{m_pKeyOneKeyPlay2, kTooltipOneKeyPlay, 0},
		};

		for (const TipOnHover o : onHover)
		{
			if (mode == kVL1Cal && !o.enableInCalMode)
				continue;

			int x = o.control->getAbsoluteX(), y = o.control->getAbsoluteY();
			int w = o.control->getWidth(), h = o.control->getHeight();
			if (mX >= x && mX < x + w && mY >= y && mY < y + h)
				enabled[o.tooltip] = true;
		}

		if (mode == kVL1Cal)
		{
			enabled[kTooltipCalFunctionKeys] = true;
			enabled[kTooltipCalNumericKeys] = true;
			enabled[kTooltipM] = true;
		}
		else if (m_bSelectRhythm)
		{
			enabled[kTooltipRhythmKeys] = true;
		}
	}

	for (int i = 0; i < kNumTooltips; ++i)
	{
		m_tooltips[i]->setVisible(enabled[i]);
	}
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
