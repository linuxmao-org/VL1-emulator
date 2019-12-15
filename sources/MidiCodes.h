#ifndef __MIDI_DEFS_H__
#define __MIDI_DEFS_H__


enum
{
	kNoteOff = 0x80,
	kNoteOn = 0x90,
	kPolyphonicKeyPressure = 0xa0,
	kControlChange = 0xb0,
	kProgramChange = 0xc0,
	kChannelPressure = 0xd0,
	kPitchBend = 0xe0,
};


#endif // __MIDI_DEFS_H__
