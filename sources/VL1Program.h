#ifndef __VL1_PROGRAM_H__
#define __VL1_PROGRAM_H__


#include "VL1Defs.h"
#include <string.h>


#define kVL1ProgramVersion  1000


typedef struct
{
	long version;
	char name[24];
	float params[kNumParams];
}
tVL1ProgramData;


class CVL1Program
{
public:

	CVL1Program()
	{
		memset(&m_data,0,sizeof(m_data));
		strcpy(m_data.name,"Default");
		m_data.version = kVL1ProgramVersion;
		//memset(m_params,0,sizeof(m_params));
		//strcpy(m_name,"Default");
	}

	~CVL1Program() {}

	inline float GetParameter(unsigned int i)
	{
		switch (i)
		{
			case kSound:
			case kAttack:
			case kDecay:
			case kSustainLevel:
			case kSustainTime:
			case kRelease:
			case kVibrato:
			case kTremolo:
				//return m_params[i];
				return m_data.params[i];
		}
		return -1.0f;
	}

	inline void SetParameter(unsigned int i, float p)
	{
		switch (i)
		{
			case kSound:
			case kAttack:
			case kDecay:
			case kSustainLevel:
			case kSustainTime:
			case kRelease:
			case kVibrato:
			case kTremolo:
				//m_params[i] = p;
				m_data.params[i] = p;
		}
	}

	CVL1Program& operator=(CVL1Program& p)
	{

		memcpy(&m_data,&p.m_data,sizeof(m_data));
		//memcpy(m_params,p.m_params,sizeof(m_params));
		//strcpy(m_name,p.m_name);
		return *this;
	}

	void LoadPreset(const char *pName, const tVL1Preset p)
	{
		strcpy(m_data.name,pName);
		//strcpy(m_name,pName);
		SetParameter(kSound,p[0]);
		SetParameter(kAttack,p[1]);
		SetParameter(kDecay,p[2]);
		SetParameter(kSustainLevel,p[3]);
		SetParameter(kSustainTime,p[4]);
		SetParameter(kRelease,p[5]);
		SetParameter(kVibrato,p[6]);
		SetParameter(kTremolo,p[7]);
	}

	inline char *GetName() { return m_data.name; }
	inline void *GetData() { return &m_data; }
	inline long GetDataSize() { return sizeof(m_data); }

protected:
	tVL1ProgramData m_data;
	//char m_name[24];

//protected:
	//float m_params[kNumParams];
};


#endif // __VL1_PROGRAM_H__
