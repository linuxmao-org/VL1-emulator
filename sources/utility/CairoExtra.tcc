#include "CairoExtra.h"

struct cairo_surface_deleter
{
	void operator()(cairo_surface_t *x) noexcept
	{
		cairo_surface_destroy(x);
	}
};
