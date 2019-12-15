#include "Voice.h"
#include <math.h>


//#include "MinBLEP.h"


// Anti alias filter: two IIR stages.
/*const double a10 = 0.933145801353958530000;
const double a11 = 1.866291602707917100000;
const double a12 = 0.933145801353958530000;
const double b11 = 1.830682045295883600000;
const double b12 = 0.901901160119950470000;

const double a20 = 0.720525462518851970000;
const double a21 = 1.441050925037703900000;
const double a22 = 0.720525462518851970000;
const double b21 = 1.367993194318967800000;
const double b22 = 0.514108655756440270000;*/

/*const double a10 = 0.385187164548196570000;
const double a11 = 0.770374329096393140000;
const double a12 = 0.385187164548196570000;
const double b11 = -0.140488166692398280000;
const double b12 = 0.681236824885184330000;

const double a20 = 0.147148644889568030000;
const double a21 = 0.294297289779136050000;
const double a22 = 0.147148644889568030000;
const double b21 = -0.630266874915356160000;
const double b22 =  0.218861454473628340000;*/

/*const double a10 = 0.120021939217659450000;
const double a11 = 0.240043878435318910000;
const double a12 = 0.120021939217659450000;
const double b11 = -1.289346230692861100000;
const double b12 = 0.769433987563499120000;
const double a20 = 0.041510554800378519000;
const double a21 = 0.083021109600757037000;
const double a22 = 0.041510554800378519000;
const double b21 = -1.322430675342003600000;
const double b22 = 0.488472894543517780000;*/



CVoice::CVoice() :
	m_bModulate(false),
	m_modulation(1.0f),
	m_tune(1.0f),
	m_octave(1.0f),
	m_phase(0.0f),
	m_phaseInc(0.0f),
	m_velocity(0.0f),
	m_lastSample(0.0f),
	m_vibratoScale(0.0002f),
	m_pWaveSet(nullptr),
	m_pWave(nullptr),
	m_sampleRate(kDefaultSampleRate),
	m_oversampling(kDefaultOversampling)
{
	m_lfoTremolo.SetDcLevel(1.0f);
}


void CVoice::Setup(CWaveSet *waveSet, float sampleRate, int oversampling)
{
	m_sampleRate = sampleRate;
	m_oversampling = oversampling;
	m_pWaveSet = waveSet;
	m_pWave = &waveSet->wavePiano;

	m_vca.Setup(sampleRate, oversampling);
	m_lfoVibrato.Setup(sampleRate, oversampling);
	m_lfoTremolo.Setup(sampleRate, oversampling);
	m_envelopeShaper.Setup(sampleRate, oversampling);
}


/*void CVoice::SetOutputBuffer()
{
	SafeDeleteArray(m_pOutBuffer);
	m_outBufferSize = (kMinBLEPSize/kMinBLEPOversampling)*(m_sampleRate/kMinBLEPSampleRate);
	m_pOutBuffer = new double[m_outBufferSize];
	m_outBufferIndex = 0;
}*/


void CVoice::Reset()
{
	m_vca.Reset();
	m_lfoVibrato.Reset();
	m_lfoTremolo.Reset();
	m_lpf.SetCutoff(0.95f*m_sampleRate/m_oversampling,m_sampleRate);
	m_lpf.SetQ(4.0f);
	m_lpf2.SetCutoff(0.45f*m_sampleRate,m_sampleRate);
	m_lpf2.SetQ(2.0f);
	//m_lpf.SetChebychef1();
	//m_lpf2.SetChebychef2();
	//m_lpf.SetButterworth1();
	//m_lpf2.SetButterworth2();
}


void CVoice::SetParameter(int param, float value)
{
	value = Clipf(0.0f,value,1.0f);

	switch (param)
	{
		case kSound:
			if (value<0.1f) m_pWave = &m_pWaveSet->wavePiano; // 0
			else if (value<0.2f) m_pWave = &m_pWaveSet->waveFantasy; // 1
			else if (value<0.3f) m_pWave = &m_pWaveSet->waveViolin; // 2
			else if (value<0.4f) m_pWave = &m_pWaveSet->waveFlute; // 3
			else if (value<0.5f) m_pWave = &m_pWaveSet->waveGuitar1; // 4
			else if (value<0.6f) m_pWave = &m_pWaveSet->waveGuitar2; // 5
			else if (value<0.7f) m_pWave = &m_pWaveSet->waveEnglishHorn; // 6
			else if (value<0.8f) m_pWave = &m_pWaveSet->wavePiano; // 7, with modulation = electro 1
			else if (value<0.9f) m_pWave = &m_pWaveSet->waveFantasy; // 8, with modulation = electro 2
			else m_pWave = &m_pWaveSet->waveViolin; // 9, with modulation = electro 3

			m_bModulate = value>0.7f? true : false;
			m_modulation = 1.0f;
			break;

		case kAttack:
			m_vca.SetAttack(10.0f*value);
			break;

		case kDecay:
			m_vca.SetDecay(10.0f*value);
			break;

		case kSustainLevel:
			m_vca.SetSustainLevel(10.0f*value);
			break;

		case kSustainTime:
			m_vca.SetSustainSlope(10.0f*value);
			break;

		case kRelease:
			m_vca.SetRelease(10.0f*value);
			break;

		case kVibrato:
			value *= 10.0f;
			if (value) m_lfoVibrato.SetFrequency(15.0f/value);
			m_lfoVibrato.Enable(value!=0);
			break;

		case kTremolo:
			value *= 10.0f;
			if (value) m_lfoTremolo.SetFrequency(35.0f/value);
			m_lfoTremolo.Enable(value!=0);
			break;

		case kOctave:
			m_octave = value;
			break;

		case kTune:
			m_tune = value;
			break;

		default:
			return;
	}

	//m_antialias.SetCutoff(m_sampleRate,m_sampleRate*m_oversampling);
}


void CVoice::NoteOn(float frequency, float velocity)
{
	int oct = floorf(2.0f*m_octave);
	//float octave = oct==0? 0.5f : oct==1? 1.0f : 2.0f;
	float octave = oct==0? 1.0f : oct==1? 2.0f : 4.0f;
	m_phaseInc = m_pWave->GetPitchScale()*m_tune*octave*frequency*((float)m_pWave->GetSize()/(m_sampleRate*m_oversampling));
	m_phase = 0.0f;
	m_velocity = velocity;
	m_vca.Gate(true);
	//if (!m_bNoteIsOn) m_vca.Reset(); // Skip for legato.
	m_lfoTremolo.Reset();
	m_lfoVibrato.Reset();
	m_vibratoScale = 0.000001f*m_phaseInc;
}


void CVoice::NoteOff()
{
	m_vca.Gate(false);
}


//nMask = sizeofwavetable-1 where sizeofwavetable is a power of two.
/*double Interpolate(double *pWavetable, int nMask, double location)
{
  // 5-point spline

  int nearest_sample = (int) location;
  double x = location - (double) nearest_sample;

  double p0 = pWavetable[(nearest_sample-2)&nMask];
  double p1 = pWavetable[(nearest_sample-1)&nMask];
  double p2 = pWavetable[nearest_sample];
  double p3 = pWavetable[(nearest_sample+1)&nMask];
  double p4 = pWavetable[(nearest_sample+2)&nMask];
  double p5 = pWavetable[(nearest_sample+3)&nMask];

  return p2 + 0.04166666666*x*((p3-p1)*16.0+(p0-p4)*2.0
  + x *((p3+p1)*16.0-p0-p2*30.0- p4
  + x *(p3*66.0-p2*70.0-p4*33.0+p1*39.0+ p5*7.0- p0*9.0
  + x *( p2*126.0-p3*124.0+p4*61.0-p1*64.0- p5*12.0+p0*13.0
  + x *((p3-p2)*50.0+(p1-p4)*25.0+(p5-p0)*5.0)))));
};*/


/*double InterpolateCubic(double *pWavetable, int nMask, double location)
{
  int inpos = (int) location;
  double finpos = location - (double) inpos;

	double xm1 = pWavetable[(inpos-1)&nMask];
	double x0  = pWavetable[inpos];
	double x1  = pWavetable[(inpos+1)&nMask];
	double x2  = pWavetable[(inpos+2)&nMask];
	double a = 0.5*(3.0*(x0-x1) - xm1 + x2);
	double b = 2.0*x1 + xm1 - 0.5*(5.0*x0+x2);
	double c = 0.5*(x1-xm1);
	return (((a*finpos) + b)*finpos + c)*finpos + x0;
}*/


/*double InterpolateCubic2(double xm1, double x0, double x1, double x2, double finpos)
{
	double a = 0.5*(3.0*(x0-x1) - xm1 + x2);
	double b = 2.0*x1 + xm1 - 0.5*(5.0*x0+x2);
	double c = 0.5*(x1-xm1);
	return (((a*finpos) + b)*finpos + c)*finpos + x0;
}*/


float CVoice::Clock()
{
	if (m_vca.IsIdle()) return 0.0f;

	float *pWaveData = m_pWave->Get();
	long waveSize = m_pWave->GetSize();

	float sample = 0.0f;

	//float ph1[8];
	//float ph2[8];
	//float ph3[8];

	for (int i=0; i<m_oversampling; i++)
	{
		//ph1[i] = m_phase;
		//ph3[i] = m_phaseInc;
		//if (m_phase<0)
		//{
		//	m_phase = 0.0f;
		//}

		long p1 = (long)m_phase;
		long p2 = (p1+1)%waveSize;
		float temp = m_phase - (float)p1;
		float s = (1.0f-temp)*pWaveData[p1] + temp*pWaveData[p2];

		s *= (0.5f + 0.5f*m_lfoTremolo.Clock());
		s *= m_vca.Clock();
		temp = s>1.0e-15f? 1.0f : 0.0f;
		//sample += temp*m_envelopeShaper.Clock(s);
		s = temp*m_envelopeShaper.Clock(s);
		//sample += m_antialias.Clock(s);
		sample += m_lpf.Clock(s);
		//sample = s;

		m_phaseInc += m_vibratoScale*m_lfoVibrato.Clock();
		m_phase += m_modulation*m_phaseInc;

		//ph2[i] = m_phase;

		if (m_phase>=(float)waveSize)
		{
			m_phase -= (float)waveSize;
		}
	}

	sample *= m_velocity/m_oversampling;
	//sample *= m_velocity;
	//sample = m_lpf2.Clock(sample);

	return sample;
}


void CVoice::Trigger()
{
	if (m_bModulate)
	{
		m_modulation = m_modulation>0.5f? 0.5f : 1.0f;
	}
}
