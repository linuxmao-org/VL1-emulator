/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "Widget.hpp"
#include "ImageSkin.h"
#include <functional>

class ImageLabel : public Widget
{
public:
	ImageLabel(ImageSkin skin, Widget *group);

	double value() const noexcept { return fValue; }
	void setValue(double value);

	bool valueNotified() const { return fValueNotify; }
	void setValueNotified(bool notified);

	void setValueBounds(double v1, double v2);

	void onDisplay() override;

	std::function<void(double)> ValueChangedCallback;

private:
	double clampToBounds(double value);

private:
	double fValue = 0;
	double fValueBound1 = 0, fValueBound2 = 1;
	bool fValueNotify = true;
	ImageSkin fSkin;
};
