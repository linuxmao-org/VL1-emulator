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

class UIVL1 : public UI, public CControlListener
{
public:
	UIVL1();
	~UIVL1();

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

private:
	static Size<uint> getBackgroundSize();

private:
	void AddKey(int id, int idBmp, int x, int y, int nBmp, KickButton **ppKey);
	void AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, MultiSwitch **ppControl);
	void AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, Slider **ppControl);

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

	std::list<std::unique_ptr<Widget>> m_subWidgets;

	std::unique_ptr<ParameterRanges[]> m_parameterRanges;

private:
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIVL1)
};

#endif
