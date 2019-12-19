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

class KickButton final : public CControl
{
public:
	KickButton(ImageSkin skin, Widget *group);

	bool hasInvertedAppearance() const { return fHasInvertedAppearance; }
	void setHasInvertedAppearance(bool inv);

	bool onMouse(const MouseEvent &event) override;
	void onDisplay() override;

private:
	bool fValue = false;
	bool fIsPressed = false;
	bool fHasInvertedAppearance = false;
	ImageSkin fSkin;
};
