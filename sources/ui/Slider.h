#pragma once
#include "Control.h"
#include "utility/CairoExtra.h"

class Slider : public CControl
{
public:
	Slider(cairo_surface_t *imgBody, cairo_surface_t *imgHandle, Widget *group);

	enum Orientation
	{
		Horizontal,
		Vertical,
	};

	double value() const noexcept { return fValue; }
	void setValue(double value);

	void setValueBounds(double v1, double v2);
	void setNumSteps(unsigned numSteps);
	void setOrientation(Orientation ori);

	bool onMouse(const MouseEvent &event) override;
	bool onMotion(const MotionEvent &event) override;
	bool onScroll(const ScrollEvent &event) override;
	void onDisplay() override;

private:
	double clampToBounds(double value);

private:
	double fValue = 0;
	double fValueBound1 = 0, fValueBound2 = 1;
	unsigned fNumSteps = 100;
	Orientation fOrientation = Horizontal;
	bool fIsDragging = false;
	cairo_surface_t *fImgBody = nullptr;
	cairo_surface_t *fImgHandle = nullptr;
};
