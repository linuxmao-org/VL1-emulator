/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once
#include "Cairo.hpp"
#include <memory>

struct cairo_surface_deleter;
typedef std::unique_ptr<_cairo_surface, cairo_surface_deleter> cairo_surface_u;

cairo_surface_t *
cairo_image_surface_create_from_png_data(const unsigned char *data, unsigned length);

cairo_surface_t *
cairo_image_surface_create_from_png_resource(unsigned int id);

#include "CairoExtra.tcc"

