/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "utility/CairoExtra.h"

namespace BitmapCache
{
	cairo_surface_t *load(unsigned id);
	void clear();
};
