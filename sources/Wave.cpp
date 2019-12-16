#include "Wave.h"
#include "SharedData.h"
#include "VL1Defs.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


CWave::CWave() :
	m_pData(nullptr),
	m_size(0),
	m_pitchScale(1.0f)
{
}


CWave::CWave(int type, int size, CSharedData *pShared)
{
	Create(type,size,pShared);
}


CWave::~CWave()
{
	if (m_pData) delete [] m_pData;
	m_pData = nullptr;
}

void CWave::DumpToFile(const char *pFilePath)
{
	int n = 1; //10
	FILE *f = fopen(pFilePath,"wb");
	if (f)
	{
		for (int i=0; i<n; i++)
		{
			fwrite(m_pData,m_size,sizeof(float),f);
		}
		fclose(f);
	}
}


void CWave::Create(int type, int size, CSharedData *pShared, float width)
{
	//bool bWriteFile = true;
	bool bWriteFile = false;

	int oversampling = pShared->oversampling;

	if ((m_pData) && (size!=m_size/oversampling))
	{
		delete [] m_pData;
		m_pData = nullptr;
	}

	if (!m_pData) m_pData = new float[size*oversampling];

	if (m_pData)
	{
		m_size = size*oversampling;
		memset(m_pData,0,m_size*sizeof(float));

		switch (type)
		{
			case kPiano:
				MakePiano();
				if (bWriteFile) DumpToFile("piano.raw");
			break;

			case kFantasy:
				MakeFantasy();
				if (bWriteFile) DumpToFile("fantasy.raw");
			break;

			case kViolin:
				MakeViolin();
				if (bWriteFile) DumpToFile("violin.raw");
			break;

			case kFlute:
				MakeFlute();
				if (bWriteFile) DumpToFile("flute.raw");
			break;

			case kGuitar1:
				MakeGuitar1();
				if (bWriteFile) DumpToFile("guitar1.raw");
			break;

			case kGuitar2:
				MakeGuitar2();
				if (bWriteFile) DumpToFile("guitar2.raw");
			break;

			case kEnglishHorn:
				MakeEnglishHorn();
				if (bWriteFile) DumpToFile("horn.raw");
			break;

			//case kWaveNoise:
			//	MakeNoise();
			//break;

			case kSinc:
				MakeSinc(width);
				if (bWriteFile) DumpToFile("sinc.raw");
			break;

		}
	}

}


void CWave::MakeSinc(float width) // width as a fraction of T (m_size)
{
	float kPi = M_PI;
	float k2Pi = 2.0 * M_PI;

	float dt = k2Pi/(width*(float)m_size);
	float dt2 = kPi/(float)m_size;
	int dx = 0.5*m_size;

	for (int i=0; i<m_size; i++)
	{
		float t = (float)(i-dx)*dt;
		if (t!=0.0f) m_pData[i] = sinf(t)/t;
		else m_pData[i] = 1.0f;
		m_pData[i] *= sinf((float)i*dt2);
	}
}


void CWave::MakePulse(float dutyCycle)
{
	int i;
	int size = m_size;

	float h0 = dutyCycle*size;
	//float h1 = 1.02*dutyCycle*size;

	for (i=0; i<(int)h0; i++)
	{
		m_pData[i] = 1.0f;
	}
	/*for (; i<(int)h1; i++)
	{
		m_pData[i] = 1.0 - 2.0*(i-h0)/(h1-h0);
	}*/
	for (; i<size; i++)
	{
		m_pData[i] = 0.0f;
	}
}


void CWave::MakePiano()
{
	MakePulse(11.0f/16.0f);
	m_pitchScale = 1.0f;
}


void CWave::MakeFantasy()
{
	MakePulse(0.5f);
	m_pitchScale = 2.0f;
}


//*
void CWave::MakeViolin()
{
	long i;
	long size = m_size;

	for (i=0; i<(4*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(5*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(8*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(9*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(11*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(12*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(13*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(14*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(15*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<size; i++)
	{
		m_pData[i] = 0.0f;
	}

	m_pitchScale = 1.0f;
}

/*/
#include <math.h>
void CWave::MakeViolin()
{
	long i;
	long size = m_size;

	float max = -100.0f;
	float min = 100.0f;

	for (i=0; i<size; i++)
	{
		float w = 2.0f*kPi*(float)i/(float)size;
		m_pData[i] = 0.298f*sinf(w);
		m_pData[i] += 0.098f*sinf(3.0f*w);
		m_pData[i] += 0.058f*sinf(5.0f*w);
		m_pData[i] += 0.042f*sinf(7.0f*w);
		m_pData[i] += 0.033f*sinf(9.0f*w);
		if (m_pData[i]>max) max = m_pData[i];
		if (m_pData[i]<min) min = m_pData[i];
	}

	for (i=0; i<size; i++)
	{
		m_pData[i] = (m_pData[i]-min)/(max-min);
	}

	m_pitchScale = 1.0f;
}
//*/


void CWave::MakeFlute()
{
	MakePulse(0.5f);
	m_pitchScale = 1.0f;
}


void CWave::MakeGuitar1()
{
	long i;
	long size = m_size;

	for (i=0; i<size/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(7*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(8*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<size; i++)
	{
		m_pData[i] = 0.0f;
	}

	m_pitchScale = 0.5f;
}


void CWave::MakeGuitar2()
{
	long i;
	long size = m_size;

	for (i=0; i<size/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(2*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(6*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<(8*size)/16; i++)
	{
		m_pData[i] = 0.0f;
	}
	for (; i<(10*size)/16; i++)
	{
		m_pData[i] = 1.0f;
	}
	for (; i<size; i++)
	{
		m_pData[i] = 0.0f;
	}

	m_pitchScale = 0.5f;
}


void CWave::MakeEnglishHorn()
{
	MakePulse(1.0f/7.0f);
	m_pitchScale = 0.5f;
}


/*void CWave::MakeNoise()
{
	m_pitchScale = 1.0f;
}*/
