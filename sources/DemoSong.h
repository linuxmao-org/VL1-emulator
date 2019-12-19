/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __DEMO_SONG_H__
#define __DEMO_SONG_H__


#include "VL1Defs.h"
#include "MidiDefs.h"


struct tSequencerEvent;


#define kDemoSongLength  467


extern const tSequencerEvent gDemoSongData[kDemoSongLength];

#endif // __DEMO_SONG_H__
