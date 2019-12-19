/*
 * VL1: a Casio VL-Tone emulator
 * Copyright (C) 2006 PolyValens
 * Copyright (C) 2019 Jean Pierre Cimalando
 *
 * SPDX-License-Identifier: CC0-1.0 or MIT
 */

#pragma once

//-----------------------------------------------------------------------------
// resource id's
enum {
	// bitmaps
	kBackgroundId = 150,

	// Controls
	kProgSelId = 151,
	kProgSelX = 712,
	kProgSelY = 26,
	kProgSelN = 6,

	kOctaveId = 152,
	kOctaveX = 641,
	kOctaveY = 26,
	kOctaveN = 3,

	kModeId = 153,
	kModeX = 805,
	kModeY = 26,
	kModeN = 4,

	kVolumeBodyId = 154,
	kVolumeHandleId = 155,
	kVolumeX = 412,
	kVolumeY = 26,

	kBalanceBodyId = 156,
	kBalanceHandleId = 157,
	kBalanceX = 523,
	kBalanceY = 26,

	kKeyN = 2,

	// White keys
	kKeyPlusMinId = 158,
	kKeyPlusMinX = 246,
	kKeyPlusMinY = 160,

	kKeyDotId = 159,
	kKeyDotX = 283,
	kKeyDotY = 160,

	kKey0Id = 160,
	kKey0X = 320,
	kKey0Y = 160,

	kKey1Id = 161,
	kKey1X = 356,
	kKey1Y = 160,

	kKey2Id = 162,
	kKey2X = 394,
	kKey2Y = 160,

	kKey3Id = 163,
	kKey3X = 430,
	kKey3Y = 160,

	kKey4Id = 164,
	kKey4X = 467,
	kKey4Y = 160,

	kKey5Id = 165,
	kKey5X = 504,
	kKey5Y = 160,

	kKey6Id = 166,
	kKey6X = 541,
	kKey6Y = 160,

	kKey7Id = 167,
	kKey7X = 578,
	kKey7Y = 160,

	kKey8Id = 168,
	kKey8X = 614,
	kKey8Y = 160,

	kKey9Id = 169,
	kKey9X = 651,
	kKey9Y = 160,

	kKeyDivId = 170,
	kKeyDivX = 688,
	kKeyDivY = 160,

	kKeyMulId = 171,
	kKeyMulX = 725,
	kKeyMulY = 160,

	kKeySubId = 172,
	kKeySubX = 762,
	kKeySubY = 160,

	kKeyAddId = 173,
	kKeyAddX = 799,
	kKeyAddY = 160,

	kKeyEqualId = 174,
	kKeyEqualX = 836,
	kKeyEqualY = 160,

	kKeyG0sId = 175,
	kKeyG0sX = 267,
	kKeyG0sY = 105,

	kKeyA0sId = 176,
	kKeyA0sX = 304,
	kKeyA0sY = 105,

	kKeyC1sId = 177,
	kKeyC1sX = 377,
	kKeyC1sY = 105,

	kKeyD1sId = 178,
	kKeyD1sX = 414,
	kKeyD1sY = 105,

	kKeyF1sId = 179,
	kKeyF1sX = 487,
	kKeyF1sY = 105,

	kKeyG1sId = 180,
	kKeyG1sX = 524,
	kKeyG1sY = 105,

	kKeyA1sId = 181,
	kKeyA1sX = 561,
	kKeyA1sY = 105,

	kKeyC2sId = 182,
	kKeyC2sX = 635,
	kKeyC2sY = 105,

	kKeyD2sId = 183,
	kKeyD2sX = 673,
	kKeyD2sY = 105,

	kKeyF2sId = 184,
	kKeyF2sX = 746,
	kKeyF2sY = 105,

	kKeyG2sId = 185,
	kKeyG2sX = 783,
	kKeyG2sY = 105,

	kKeyA2sId = 186,
	kKeyA2sX = 820,
	kKeyA2sY = 105,

	kKeyResetId = 199,
	kKeyResetX = 455,
	kKeyResetY = 67,

	kKeyDelId = 200,
	kKeyDelX = 491,
	kKeyDelY = 67,

	kKeyTempoUpId = 201,
	kKeyTempoUpX = 528,
	kKeyTempoUpY = 67,

	kKeyTempoDownId = 202,
	kKeyTempoDownX = 565,
	kKeyTempoDownY = 67,

	kKeyRhythmId = 203,
	kKeyRhythmX = 602,
	kKeyRhythmY = 67,

	kKeyMLCId = 204,
	kKeyMLCX = 639,
	kKeyMLCY = 67,

	kKeyMusicId = 205,
	kKeyMusicX = 676,
	kKeyMusicY = 67,

	kKeyAutoPlayId = 206,
	kKeyAutoPlayX = 712,
	kKeyAutoPlayY = 67,

	kKeyOneKeyPlayDotDotId = 207,
	kKeyOneKeyPlayDotDotX = 794,
	kKeyOneKeyPlayDotDotY = 56,

	kKeyOneKeyPlayDotId = 208,
	kKeyOneKeyPlayDotX = 837,
	kKeyOneKeyPlayDotY = 56,

	kTuneBodyId = 0,
	kTuneHandleId = 0,
	kTuneX = 0,
	kTuneY = 0,

	//kFaderInc = 18,

	//kDisplayX = 50,
	//kDisplayY = 214,
	//kDisplayXWidth = 30,
	//kDisplayHeight = 14

	// Tooltips
	kTooltipVolume = 0,
	kTooltipBalance,
	kTooltipOctave,
	kTooltipSound,
	kTooltipMode,
	kTooltipReset,
	kTooltipDel,
	kTooltipTempoUp,
	kTooltipTempoDown,
	kTooltipRhythm,
	kTooltipMlc,
	kTooltipMusic,
	kTooltipAutoPlay,
	kTooltipOneKeyPlay,
	kTooltipCalFunctionKeys,
	kTooltipCalNumericKeys,
	kTooltipRhythmKeys,
	kTooltipM,
	kNumTooltips,

	kTooltipVolumeId = 209,
	kTooltipVolumeX = 400,
	kTooltipVolumeY = 5,

	kTooltipBalanceId = 210,
	kTooltipBalanceX = 493,
	kTooltipBalanceY = 5,

	kTooltipOctaveId = 211,
	kTooltipOctaveX = 563,
	kTooltipOctaveY = 5,

	kTooltipSoundId = 212,
	kTooltipSoundX = 610,
	kTooltipSoundY = 5,

	kTooltipModeId = 213,
	kTooltipModeX = 757,
	kTooltipModeY = 5,

	kTooltipResetId = 214,
	kTooltipResetX = 444,
	kTooltipResetY = 47,

	kTooltipDelId = 215,
	kTooltipDelX = 488,
	kTooltipDelY = 47,

	kTooltipTempoUpId = 216,
	kTooltipTempoUpX = 504,
	kTooltipTempoUpY = 47,

	kTooltipTempoDownId = 217,
	kTooltipTempoDownX = 532,
	kTooltipTempoDownY = 47,

	kTooltipRhythmId = 218,
	kTooltipRhythmX = 584,
	kTooltipRhythmY = 47,

	kTooltipMlcId = 219,
	kTooltipMlcX = 628,
	kTooltipMlcY = 47,

	kTooltipMusicId = 220,
	kTooltipMusicX = 663,
	kTooltipMusicY = 47,

	kTooltipAutoPlayId = 221,
	kTooltipAutoPlayX = 690,
	kTooltipAutoPlayY = 47,

	kTooltipOneKeyPlayId = 222,
	kTooltipOneKeyPlayX = 736,
	kTooltipOneKeyPlayY = 61,

	kTooltipCalFunctionKeysId = 224,
	kTooltipCalFunctionKeysX = 454,
	kTooltipCalFunctionKeysY = 47,

	kTooltipCalNumericKeysId = 225,
	kTooltipCalNumericKeysX = 251,
	kTooltipCalNumericKeysY = 194,

	kTooltipRhythmKeysId = 226,
	kTooltipRhythmKeysX = 312,
	kTooltipRhythmKeysY = 128,

	kTooltipMId = 227,
	kTooltipMX = 771,
	kTooltipMY = 68,
};
