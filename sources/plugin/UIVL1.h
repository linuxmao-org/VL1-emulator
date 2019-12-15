#ifndef UI_VL1_H
#define UI_VL1_H

#include "DistrhoUI.hpp"
#include "SharedVL1.h"
#include "utility/CairoExtra.h"
#include <list>

class KickButton;

class UIVL1 : public UI
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

private:
	static cairo_surface_t *loadCachedBitmap(unsigned id);
	static void clearBitmapCache();

	static Size<uint> getBackgroundSize();

private:
	#pragma message("TODO implement these components: slider, switch, button")
	typedef Widget CHorizontalSlider;
	typedef Widget CHorizontalSwitch;

	void AddKey(int id, int idBmp, int x, int y, int nBmp, KickButton **ppKey);
	void AddHorizontalSwitch(int id, int idBmp, int x, int y, int nPos, int nBmp, CHorizontalSwitch **ppControl);
	void AddHorizontalSlider(int id, int idBmpBody, int idBmpHandle, int x, int y, CHorizontalSlider **ppControl);

	CHorizontalSlider *m_pVolume;
	CHorizontalSlider *m_pBalance;
	CHorizontalSwitch *m_pProgramSelector;
	CHorizontalSwitch *m_pOctave;
	CHorizontalSwitch *m_pMode;

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

	std::list<std::unique_ptr<Widget>> m_subWidgets;

private:
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIVL1)
};

#endif
