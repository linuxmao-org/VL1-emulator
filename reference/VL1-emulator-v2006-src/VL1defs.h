#ifndef __VL1_DEFS_H__
#define __VL1_DEFS_H__


#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#ifndef TRUE
#define TRUE (!FALSE)
#endif // TRUE

#ifndef BOOL
typedef int BOOL;
#endif // BOOL


// ASIC clock
const float kAsicClock = 200000.0f; // Hz
const float kTempoUnit = 0.034f; // sec
const float kMinTempoPeriod = 0.170f; // sec
const float kPi = 3.141592654f;


#define kWhole  32
#define kHalf  (kWhole/2)
#define kQuarter  (kWhole/4)
#define kEighth  (kWhole/8)
#define kSixteenth  (kWhole/16)
#define kThirtytwoth  (kWhole/32)


#define kDefaultSampleRate  44100
#define kDefaultOversampling  16


// Constants
enum
{
	// Global
	kNumOutputs = 2,
	kWaveTableSize = 32, //4096,

	// Modes
	kVL1Play = 0,
	kVL1Rec,
	kVL1Cal,
	kVL1Off,

	kProgramPiano = (char)0,
	kProgramFantasy = (char)1,
	kProgramViolin = (char)2,
	kProgramFlute = (char)3,
	kProgramGuitar = (char)4,
	kProgramAdsr = (char)5,
	kNumPrograms, // This should always be the last program.

	// Casio parameters for sounds.
	kParamsPiano = 453200,
	kParamsFantasy = 10099630,
	kParamsViolin = 23099130,
	kParamsFlute = 33099130,
	kParamsGuitar = 41071200,

	// Sounds
	kPiano = 0,
	kFantasy = 1,
	kViolin = 2,
	kFlute = 3,
	kGuitar1 = 4,
	kGuitar2 = 5,
	kEnglishHorn = 6,
	kElectro1 = 7,
	kElectro2 = 8,
	kElectro3 = 9,
	kNumSounds,
	kSinc,
	kADSR = 10,

	// Rhythm sounds.
	kPock = 0, // About 750 Hz square wave.
	kPeek, // kPock at double speed.
	kNoise, // Noise with "complicated" envelope.
	kMaxRhythmSound,

	// Rhythms.
	kNoRhythm = -1,
	kMarch = 0,
	kWaltz,
	k4Beat,
	kSwing,
	kRock1,
	kRock2,
	kBossanova,
	kSamba,
	kRhumba,
	kBeguine,
	kMaxRhythm,

	// Parameters Tags
	// The order is important for the display in the host.
	kProgram = 0,
	kMode,
	kVolume,
	kBalance,
	kOctave,
	kTune,
	kSound,
	kAttack,
	kDecay,
	kSustainLevel,
	kSustainTime,
	kRelease,
	kVibrato,
	kTremolo,
	kTempo,
	kNumParams, // This should always be the last parameter.

	// Keyboard
	kKeyPlusMin = 55,
	kKeyPlusMinS = 56,
	kKeyDot = 57,
	kKeyDotS = 58,
	kKey0 = 59,
	kKey1 = 60, // Middle C
	kKey1S = 61,
	kKey2 = 62,
	kKey2S = 63,
	kKey3 = 64,
	kKey4 = 65,
	kKey4S = 66,
	kKey5 = 67,
	kKey5S = 68,
	kKey6 = 69,
	kKey6S = 70,
	kKey7 = 71,
	kKey8 = 72,
	kKey8S = 73,
	kKey9 = 74,
	kKey9S = 75,
	kKeyDiv = 76,
	kKeyMul = 77,
	kKeyMulS = 78,
	kKeySub = 79,
	kKeySubS = 80,
	kKeyAdd = 81,
	kKeyAddS = 82,
	kKeyEqual = 83,

	kKeyReset,
	kKeyDel,
	kKeyTempoUp,
	kKeyTempoDown,
	kKeyRhythm,
	kKeyMLC,
	kKeyMusic,
	kKeyAutoPlay,
	kKeyOneKeyPlayDotDot,
	kKeyOneKeyPlayDot,

	//kDisplay,
	kChar1,
	kChar2,
	kChar3,
	kChar4,
	kChar5,
	kChar6,
	kChar7,
	kChar8,
	kChar9,
	kSharp1,
	kSharp2,
	kSharp3,
	kDot1,
	kDot2,
	kDot3,
	kDot4,
	kDot5,
	kDot6,
	kDot7,
	kDot8,
	kAdd,
	kSub,
	kDiv,
	kMul,
	kK,
	kM,
	kErr,
};


extern const char *gVL1SoundNames[];
extern const char *gVL1PresetNames[];


typedef float tVL1Preset[8];

const tVL1Preset gVL1Preset[kNumPrograms] = 
{  
//  sound  A     D     Sl    St    R     V     T
	{ 0.0f, 0.0f, 0.4f, 0.5f, 0.3f, 0.2f, 0.0f, 0.0f }, // Piano
	{ 0.1f, 0.0f, 0.0f, 0.9f, 0.9f, 0.6f, 0.3f, 0.0f }, // Fantasy
	{ 0.2f, 0.3f, 0.0f, 0.9f, 0.9f, 0.1f, 0.3f, 0.0f }, // Violin
	{ 0.3f, 0.3f, 0.0f, 0.9f, 0.9f, 0.1f, 0.3f, 0.0f }, // Fute
	{ 0.4f, 0.1f, 0.0f, 0.7f, 0.1f, 0.2f, 0.0f, 0.0f }, // Guitar
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, // ADSR
};


// Envelopes
// ---------
// An envelope can take on at most 15 different levels (not counting 0).
// Envelope time is discrete.
// An envelope phase (A, D, S or R) is linear and can be defined by
// a start level, a stop level and the number of time units.

const float kEnvelopeDivisor = 2400.0f;
const float kEnvelopeTimeUnit = kEnvelopeDivisor/kAsicClock; // sec

const float kEnvelopeLevels = 15.0f;
const float kEnvelopeStep = 1.0f/kEnvelopeLevels;

typedef struct
{
	float lBegin;
	float lEnd;
	float tUnits;
}
tEnvelopePhaseInfo;

#define kEnvelopeRange  11 // ADSR values go from 0 to 9.


const tEnvelopePhaseInfo gAttack[kEnvelopeRange] =
{
	{ 15.0f, 15.0f,  0.0f }, // 0
	{ 11.0f, 15.0f,  1.0f }, // 1
	{  7.0f, 15.0f,  4.0f }, // 2
	{  5.0f, 15.0f,  7.0f }, // 3
	{  4.0f, 15.0f, 10.0f }, // 4
	{  4.0f, 15.0f, 13.0f }, // 5
	{  3.0f, 15.0f, 16.0f }, // 6
	{  3.0f, 15.0f, 19.0f }, // 7
	{  3.0f, 15.0f, 22.0f }, // 8
	{  3.0f, 15.0f, 25.0f }, // 9
	{  2.0f, 15.0f, 28.0f }, // 10
};


const tEnvelopePhaseInfo gDecay[kEnvelopeRange] =
{
	{ 15.0f, 0.0f,  0.0f }, // 0
	{ 15.0f, 0.0f,  9.0f }, // 1
	{ 15.0f, 0.0f, 18.0f }, // 2
	{ 15.0f, 0.0f, 27.0f }, // 3
	{ 15.0f, 0.0f, 39.0f }, // 4
	{ 15.0f, 0.0f, 48.0f }, // 5
	{ 15.0f, 0.0f, 58.0f }, // 6
	{ 15.0f, 0.0f, 67.0f }, // 7
	{ 15.0f, 0.0f, 78.0f }, // 8
	{ 15.0f, 0.0f, 87.0f }, // 9
	{ 15.0f, 0.0f, 98.0f }, // 10
};


const tEnvelopePhaseInfo gSustainLevel[kEnvelopeRange] =
{
	{ 15.0f,  1.0f, 0.0f }, // 0
	{ 15.0f,  2.0f, 0.0f }, // 1
	{ 15.0f,  4.0f, 0.0f }, // 2
	{ 15.0f,  6.0f, 0.0f }, // 3
	{ 15.0f,  8.0f, 0.0f }, // 4
	{ 15.0f, 10.0f, 0.0f }, // 5
	{ 15.0f, 12.0f, 0.0f }, // 6
	{ 15.0f, 13.0f, 0.0f }, // 7
	{ 15.0f, 14.0f, 0.0f }, // 8
	{ 15.0f, 15.0f, 0.0f }, // 9
	{ 15.0f, 15.0f, 0.0f }, // 10
};


const tEnvelopePhaseInfo gSustainSlope[kEnvelopeRange] =
{
	{ 15.0f, 0.0f,   0.0f }, // 0
	{ 15.0f, 0.0f,  79.0f }, // 1
	{ 15.0f, 0.0f, 154.0f }, // 2
	{ 15.0f, 0.0f, 231.0f }, // 3
	{ 15.0f, 0.0f, 312.0f }, // 4
	{ 15.0f, 0.0f, 389.0f }, // 5
	{ 15.0f, 0.0f, 467.0f }, // 6
	{ 15.0f, 0.0f, 543.0f }, // 7
	{ 15.0f, 0.0f, 615.0f }, // 8
	{ 15.0f, 0.0f,  -1.0f }, // 9, infinite
	{ 15.0f, 0.0f,  -1.0f }, // 10, infinite
};


const tEnvelopePhaseInfo gRelease[kEnvelopeRange] =
{
	{ 14.0f, 0.0f,   0.0f }, // 0
	{ 14.0f, 0.0f,  26.0f }, // 1
	{ 14.0f, 0.0f,  48.0f }, // 2
	{ 14.0f, 0.0f,  73.0f }, // 3
	{ 14.0f, 0.0f,  96.0f }, // 4
	{ 14.0f, 0.0f, 116.0f }, // 5
	{ 14.0f, 0.0f, 142.0f }, // 6
	{ 14.0f, 0.0f, 167.0f }, // 7
	{ 14.0f, 0.0f, 193.0f }, // 8
	{ 14.0f, 0.0f, 217.0f }, // 9
	{ 14.0f, 0.0f, 242.0f }, // 10
};


#endif // __VL1_DEFS_H__
