/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#ifndef __MIDI_DEFS_H__
#define __MIDI_DEFS_H__


enum
{
	kNoteOff = (unsigned char)0x80,
	kNoteOn = (unsigned char)0x90,
	kPolyphonicKeyPressure = (unsigned char)0xa0,
	kControlChange = (unsigned char)0xb0,
	kProgramChange = (unsigned char)0xc0,
	kChannelPressure = (unsigned char)0xd0,
	kPitchBend = (unsigned char)0xe0,

	kModulationWheel = (unsigned char)0x01,
	kBreathControl = (unsigned char)0x02,
	kChannelVolume = (unsigned char)0x07,
	kDamperPedal = (unsigned char)0x40,
	kAllSoundOff = (unsigned char)0x78,
	kResetAll = (unsigned char)0x79,
	kLocalControl = (unsigned char)0x7a,
	kAllNotesOff = (unsigned char)0x7b,
	kOmniOff = (unsigned char)0x7c,
	kOmniOn = (unsigned char)0x7d,
	kPolyOff = (unsigned char)0x7e,
	kPolyOn = (unsigned char)0x7f,

	kRhythm = (unsigned char)0x50,
	kRhythmOn = (unsigned char)0x51,
	kRhythmOff = (unsigned char)0x52,
	kSequencerStart = (unsigned char)0x53,
	kSequencerStop = (unsigned char)0x54,
};


#endif // __MIDI_DEFS_H__
