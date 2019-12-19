/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "CairoExtra.h"

struct cairo_surface_deleter
{
	void operator()(cairo_surface_t *x) noexcept
	{
		cairo_surface_destroy(x);
	}
};
