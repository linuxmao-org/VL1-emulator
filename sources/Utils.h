#ifndef __UTILS_H__
#define __UTILS_H__


//#include "VstGui.h"


int TRACE(const char *lpszFormat, ...);


template <class T>
class CMinMax
{
public:
	static const T& Min(const T& v1, const T& v2) { return v1<v2? v1 : v2; }
	static const T& Max(const T& v1, const T& v2) { return v1>v2? v1 : v2; }
	static const T& Clip(const T& min, const T& v, const T& max) { return Max(min,Min(v,max)); }
};


typedef CMinMax<double> tMinMaxDouble;
typedef CMinMax<float> tMinMaxFloat;

#define Minf(a,b) tMinMaxFloat::Min((a),(b))
#define Maxf(a,b) tMinMaxFloat::Max((a),(b))
#define Clipf(mi,v,ma) tMinMaxFloat::Clip((mi),(v),(ma))

#define SafeDelete(a) if (a) { delete a; a = nullptr; }
#define SafeDeleteArray(a) if (a) { delete [] a; a = nullptr; }


inline int Float2Int(float f)
{
	return (int)(f+0.5f);
}


inline int GetDigitN(int i, long int digitNr)
{
	for (int j=0; j<digitNr; j++)
	{
		i = i/10;
	}
	i -= (i/10)*10;
	if (i<0) i = 0;
	if (i>9) i = 9;
	return i;
}


inline int GetInterval(float value, float intervals)
{
	for (float i=0.0f; i<intervals; i+=1.0f)
	{
		if ((value>=i/intervals) && (value<(i+1.0f)/intervals)) return (int)i;
	}
	return (int)intervals;
}


inline int FloatToInt(float value, int min, int max)
{
	return GetInterval(value,(float)(min>0?max-min-1:max-min)) + min;
}


#endif // __UTILS_H__
