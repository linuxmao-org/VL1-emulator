/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once

struct Resource
{
	unsigned int id;
	unsigned int type;
	const unsigned char *data;
	unsigned int size;
};

const Resource *GetResource(unsigned int id);
