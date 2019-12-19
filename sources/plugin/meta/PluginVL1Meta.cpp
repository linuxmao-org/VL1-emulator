/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#include "plugin/PluginVL1.h"

const char *PluginVL1::getLabel() const noexcept
{
	return "VL1";
}

const char *PluginVL1::getDescription() const
{
	return "An emulator of Casio VL-Tone VL1";
}

const char *PluginVL1::getMaker() const noexcept
{
	return "PolyValens";
}

const char *PluginVL1::getHomePage() const
{
	return "http://www.polyvalens.com/blog/vl-1/";
}

const char *PluginVL1::getLicense() const noexcept
{
#pragma message("TODO decide a license for plugin")
	return "Not decided";
}

uint32_t PluginVL1::getVersion() const noexcept
{
	return d_version(0, 1, 0);
}

int64_t PluginVL1::getUniqueId() const noexcept
{
	return d_cconst('c', 'p', 'v', '1');
}
