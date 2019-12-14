#ifndef __WAVE_H__
#define __WAVE_H__


class CWave
{
public:
	CWave();
	CWave::CWave(int type, int size);
	~CWave();

	void CWave::Create(int type, int size, float width=0.25f);

	float *Get() { return m_pData; }
	long GetSize() { return m_size; }
	float GetPitchScale() { return m_pitchScale; }

	void DumpToFile(char *pFilePath);

private:
	float *m_pData;
	long m_size;
	float m_pitchScale;
	//char *m_pName;

	void MakeSinc(float width);
	void MakePulse(float dutyCycle);
	void MakePiano();
	void MakeFantasy();
	void MakeViolin();
	void MakeFlute();
	void MakeGuitar1();
	void MakeGuitar2();
	void MakeEnglishHorn();
	//void MakeNoise();
};


extern char *gpWaveNames[10];


#endif // __WAVE_H__
