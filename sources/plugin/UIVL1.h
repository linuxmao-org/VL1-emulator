/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef UI_VL1_H
#define UI_VL1_H

#include "DistrhoUI.hpp"
#include "SharedVL1.h"
#include "ui/Control.h"
#include "utility/CairoExtra.h"
#include <list>

class KickButton;
class MultiSwitch;
class Slider;
class CLcd;
class ImageLabel;
class PluginVL1;

class UIVL1 : public UI, public CControlListener
{
public:
	UIVL1();
	~UIVL1();

	PluginVL1 *getDsp() const;

	void setParameterValue01(uint32_t index, float value);

protected:
	void parameterChanged(uint32_t, float value) override;
	void programLoaded(uint32_t index) override;
	void sampleRateChanged(double newSampleRate) override;

	void uiIdle() override;
	void uiReshape(uint width, uint height) override;

	void onDisplay() override;

	bool onKeyboard(const KeyboardEvent &ev) override;
	bool onSpecial(const SpecialEvent &ev) override;
	bool onMouse(const MouseEvent &ev) override;
	bool onMotion(const MotionEvent &ev) override;
	bool onScroll(const ScrollEvent &ev) override;

protected:
	void controlValueChanged(CControl &control) override;
	void controlBeganChangeGesture(CControl &control) override;
	void controlEndedChangeGesture(CControl &control) override;

private:
	static Size<uint> getBackgroundSize();

private:
	void AddKey(int id, int idBmp, int x, int y, int nBmp, KickButton **ppKey);
	void AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, MultiSwitch **ppControl);
	void AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, Slider **ppControl);
	void AddTooltip(int id, int idBmp, int x, int y);

	void SetCurrentTooltips();

	Slider *m_pVolume;
	Slider *m_pBalance;
	MultiSwitch *m_pProgramSelector;
	MultiSwitch *m_pOctave;
	MultiSwitch *m_pMode;

	KickButton *m_pBlackWhiteKey[29]; // 17 white + 12 black keys
	KickButton *m_pKeyReset;
	KickButton *m_pKeyDel;
	KickButton *m_pKeyTempoUp;
	KickButton *m_pKeyTempoDown;
	KickButton *m_pKeyRhythm;
	KickButton *m_pKeyMLC;
	KickButton *m_pKeyMusic;
	KickButton *m_pKeyAutoPlay;
	KickButton *m_pKeyOneKeyPlay2;
	KickButton *m_pKeyOneKeyPlay1;

	CLcd *m_lcd;

	bool m_bSelectRhythm = false;

	int m_curProgram = 0;

	Point<int> m_lastMousePosition = {};

	std::unique_ptr<std::unique_ptr<ImageLabel>[]> m_tooltips;

	std::list<std::unique_ptr<Widget>> m_subWidgets;

private:
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIVL1)
};

#endif
