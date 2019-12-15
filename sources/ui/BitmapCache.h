#pragma once
#include "utility/CairoExtra.h"

namespace BitmapCache
{
	cairo_surface_t *load(unsigned id);
	void clear();
};
