/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "Control.h"
#include "ImageSkin.h"
#include <functional>

class ImageLabel final : public CControl
{
public:
	ImageLabel(ImageSkin skin, Widget *group);

	void setValue(double value, NotifyMode notify = kNotify) override;

	void setValueBounds(double v1, double v2);

	void onDisplay() override;

private:
	double clampToBounds(double value);

private:
	double fValueBound1 = 0, fValueBound2 = 1;
	ImageSkin fSkin;
};
