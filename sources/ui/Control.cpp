/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "Control.h"

void CControl::setValue(double value, NotifyMode notify)
{
	if (fValue == value)
		return;

	fValue = value;

	if (notify == kNotify)
	{
		for (CControlListener *cl : fListeners)
			cl->controlValueChanged(*this);
	}

	repaint();
}

void CControl::addListener(CControlListener *cl)
{
	DISTRHO_SAFE_ASSERT_RETURN(cl != nullptr, );

	fListeners.push_back(cl);
}

void CControl::removeListener(CControlListener *cl)
{
	auto it = std::find(fListeners.begin(), fListeners.end(), cl);

	DISTRHO_SAFE_ASSERT_RETURN(it != fListeners.end(), );

	fListeners.erase(it);
}

void CControl::beginChangeGesture()
{
	for (CControlListener *cl : fListeners)
		cl->controlBeganChangeGesture(*this);
}

void CControl::endChangeGesture()
{
	for (CControlListener *cl : fListeners)
		cl->controlEndedChangeGesture(*this);
}
