/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "ImageLabel.h"
#include "Cairo.hpp"
#include "ImageSkin.h"
#include "Window.hpp"

ImageLabel::ImageLabel(ImageSkin skin, Widget *group)
	: Widget(group), fSkin(skin)
{
	setSize(skin.getWidth(), skin.getHeight());
}

void ImageLabel::setValue(double value)
{
	value = clampToBounds(value);

	if (fValue == value)
		return;

	fValue = value;
	if (ValueChangedCallback && fValueNotify)
		ValueChangedCallback(value);
	repaint();
}

void ImageLabel::setValueNotified(bool notified)
{
	fValueNotify = notified;
}

void ImageLabel::setValueBounds(double v1, double v2)
{
	fValueBound1 = v1;
	fValueBound2 = v2;
	setValue(fValue);
}

void ImageLabel::onDisplay()
{
	const ImageSkin &skin = fSkin;
	cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

	int w = getWidth();
	int h = getHeight();

	//
	double v1 = fValueBound1;
	double v2 = fValueBound2;

	//
	double value = fValue;
	double fill = 0;
	if (v1 != v2)
		fill = (value - v1) / (v2 - v1);

	//
	cairo_surface_t *image = skin.getImageForRatio(fill);
	cairo_rectangle(cr, 0, 0, w, h);
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_fill(cr);
}

double ImageLabel::clampToBounds(double value)
{
	double vmin = fValueBound1;
	double vmax = fValueBound2;
	if (vmin > vmax)
		std::swap(vmin, vmax);

	value = (value < vmin) ? vmin : value;
	value = (value > vmax) ? vmax : value;
	return value;
}
