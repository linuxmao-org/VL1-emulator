#ifndef UI_VL1_H
#define UI_VL1_H

#include "DistrhoUI.hpp"
#include "SharedVL1.h"
#include "utility/CairoExtra.h"

START_NAMESPACE_DISTRHO

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
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIVL1)
};

END_NAMESPACE_DISTRHO

#endif
