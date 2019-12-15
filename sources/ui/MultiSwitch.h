#pragma once
#include "ImageSkin.h"
#include "Widget.hpp"
#include "utility/CairoExtra.h"
#include <functional>

class MultiSwitch : public Widget
{
public:
	MultiSwitch(ImageSkin skin, Widget *group);

	enum Orientation
	{
		Horizontal,
		Vertical,
	};

	double value() const noexcept { return fValue; }
	void setValue(double value);

	bool valueNotified() const { return fValueNotify; }
	void setValueNotified(bool notified);

	void setValueBounds(double v1, double v2);
	void setNumSteps(unsigned numSteps);
	void setOrientation(Orientation ori);

	bool onMouse(const MouseEvent &event) override;
	bool onMotion(const MotionEvent &event) override;
	bool onScroll(const ScrollEvent &event) override;
	void onDisplay() override;

	std::function<void(double)> ValueChangedCallback;

private:
	double clampToBounds(double value);

private:
	double fValue = 0;
	double fValueBound1 = 0, fValueBound2 = 1;
	unsigned fNumSteps = 100;
	Orientation fOrientation = Horizontal;
	bool fValueNotify = true;
	bool fIsDragging = false;
	ImageSkin fSkin;
};
