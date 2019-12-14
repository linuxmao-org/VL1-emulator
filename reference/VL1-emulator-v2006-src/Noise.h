#ifndef __NOISE_H__
#define __NOISE_H__


class CNoise
{
public:
	CNoise();

	void Set(int length=16 /*bits*/, int mask=0x1d87);
	int Clock();

private:
	unsigned int m_shiftRegister;
	int m_length;
	int m_mask;
};


#endif // __NOISE_H__
