/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "MultiSwitch.h"
#include "Cairo.hpp"
#include "Window.hpp"
#include <cmath>

///
MultiSwitch::MultiSwitch(ImageSkin skin, Widget *group)
	: CControl(group), fSkin(skin)
{
	unsigned wBody = skin.getWidth();
	unsigned hBody = skin.getHeight();
	setSize(wBody, hBody);
}

void MultiSwitch::setValue(double value, NotifyMode notify)
{
	double v1 = fValueBound1;
	double v2 = fValueBound2;
	unsigned n = fNumSteps;

	if (v1 != v2 && n > 0)
	{
		double fill = (value - v1) / (v2 - v1);
		value = std::round(fill * (n - 1)) / (n - 1) * (v2 - v1) + v1;
	}

	CControl::setValue(clampToBounds(value), notify);
}

void MultiSwitch::setValueBounds(double v1, double v2)
{
	fValueBound1 = v1;
	fValueBound2 = v2;
	setValue(getValue());
}

void MultiSwitch::setNumSteps(unsigned numSteps)
{
	fNumSteps = numSteps;
}

void MultiSwitch::setOrientation(Orientation ori)
{
	if (fOrientation == ori)
		return;

	fOrientation = ori;
	repaint();
}

bool MultiSwitch::onMouse(const MouseEvent &event)
{
	DGL::Size<uint> wsize = getSize();
	DGL::Point<int> mpos = event.pos;

	if (!fIsDragging && event.press && event.button == 1)
	{
		bool insideX = mpos.getX() >= 0 && (unsigned)mpos.getX() < wsize.getWidth();
		bool insideY = mpos.getY() >= 0 && (unsigned)mpos.getY() < wsize.getHeight();

		if (!insideX || !insideY)
			return false;

		fIsDragging = true;

		double fill = 0;
		if (fOrientation == Horizontal)
		{
			fill = mpos.getX() / (double)wsize.getWidth();
			setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
		}
		else
		{
			fill = 1.0 - (mpos.getY() / (double)wsize.getHeight());
			setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
		}

		return true;
	}
	else if (fIsDragging && !event.press && event.button == 1)
	{
		fIsDragging = false;
		return true;
	}

	return false;
}

bool MultiSwitch::onMotion(const MotionEvent &event)
{
	DGL::Size<uint> wsize = getSize();
	DGL::Point<int> mpos = event.pos;

	if (fIsDragging)
	{
		double fill = 0;
		bool doNotSet = false;
		if (fOrientation == Horizontal)
			fill = mpos.getX() / (double)wsize.getWidth();
		else if (fOrientation == Vertical)
			fill = 1.0 - (mpos.getY() / (double)wsize.getHeight());
		fill = (fill < 0) ? 0 : fill;
		fill = (fill > 1) ? 1 : fill;
		if (!doNotSet)
			setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
		return true;
	}

	return false;
}

bool MultiSwitch::onScroll(const ScrollEvent &event)
{
	DGL::Size<uint> wsize = getSize();
	DGL::Point<int> mpos = event.pos;

	bool inside = mpos.getX() >= 0 && mpos.getY() >= 0 && (unsigned)mpos.getX() < wsize.getWidth() &&
	              (unsigned)mpos.getY() < wsize.getHeight();

	if (inside)
	{
		double amount = event.delta.getX() - event.delta.getY();
		if (fOrientation == Vertical)
			amount = -amount;
		setValue(getValue() + amount * (fValueBound2 - fValueBound1) / fNumSteps);
		return true;
	}

	return false;
}

void MultiSwitch::onDisplay()
{
	cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

	const ImageSkin &skin = fSkin;
	int wBody = skin.getWidth();
	int hBody = skin.getHeight();

	//
	double v1 = fValueBound1;
	double v2 = fValueBound2;

	//
	double fill = 0;
	if (v1 != v2)
		fill = (getValue() - v1) / (v2 - v1);

	//
	cairo_surface_t *image = skin.getImageForRatio(fill);
	cairo_rectangle(cr, 0, 0, wBody, hBody);
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_fill(cr);
}

double MultiSwitch::clampToBounds(double value)
{
	double vmin = fValueBound1;
	double vmax = fValueBound2;
	if (vmin > vmax)
		std::swap(vmin, vmax);

	value = (value < vmin) ? vmin : value;
	value = (value > vmax) ? vmax : value;
	return value;
}
