#include "ADSR.cpp"
#include "LineInTime.cpp"
#include <algorithm>
#include <vector>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
	CAdsr adsr;

	double sampleRate = 128.0;
	double duration = 5.0;

	double attack = 0.0;
	double decay = 4.0;
	double sustainLevel = 5.0;
	double sustainSlope = 3.0;
	double release = 2.0;

	struct tGate { double time; bool enable; };
	std::vector<tGate> gate;

	for (int c; (c = getopt(argc, argv, "hr:d:T:R:a:")) != -1;)
	{
		switch (c)
		{
			case 'h':
				fprintf(stderr, "Usage: %s [-r sample-rate] [-d duration] [-T trigger] [-R release] [-a a:d:l:s:r].\n", argv[0]);
				return 1;
			case 'r':
				sampleRate = atof(optarg);
				if (sampleRate <= 0)
				{
					fprintf(stderr, "Invalid sample rate.\n");
					return 1;
				}
				break;
			case 'd':
				duration = atof(optarg);
				if (duration <= 0)
				{
					fprintf(stderr, "Invalid duration.\n");
					return 1;
				}
				break;
			case 'T':
			case 'R':
			{
				tGate g;
				g.time = atof(optarg);
				g.enable = c == 'T';
				if (g.time < 0)
				{
					fprintf(stderr, "Invalid time point.\n");
					return 1;
				}
				gate.push_back(g);
			}
			break;
			case 'a':
			{
				unsigned n = 0;
				if (sscanf(optarg, "%lf:%lf:%lf:%lf:%lf%n", &attack, &decay, &sustainLevel, &sustainSlope, &release, &n) != 5 || n != strlen(optarg))
				{
					fprintf(stderr, "Bad specification for ADSR (should be \"a:d:l:s:r\").\n");
					return 1;
				}
#define RANGE_CHECK(x, s)												\
				if (x < 0 || x > 10)									\
				{														\
					fprintf(stderr, "The " s " is out of range, should be in [0;10].\n"); \
					return 1;											\
				}
				RANGE_CHECK(attack, "attack");
				RANGE_CHECK(decay, "decay");
				RANGE_CHECK(sustainLevel, "sustain level");
				RANGE_CHECK(sustainSlope, "sustain slope");
				RANGE_CHECK(release, "release");
#undef RANGE_CHECK
				break;
			}
			default:
				return 1;
		}
	}

	std::sort(
		gate.begin(), gate.end(),
		[](const tGate &a, const tGate &b) -> bool { return a.time < b.time; });

	CSharedData shared;
	shared.sampleRate = sampleRate;
	shared.oversampling = 1;
	adsr.Setup(&shared);

	adsr.SetAttack(attack);
	adsr.SetDecay(decay);
	adsr.SetSustainLevel(sustainLevel);
	adsr.SetSustainSlope(sustainSlope);
	adsr.SetRelease(release);

	unsigned numSamples = ceil(sampleRate * duration);
	size_t gateIndex = 0;

	for (unsigned i = 0; i < numSamples; ++i)
	{
		double t = i * (1.0 / sampleRate);
		int g = -1;
		while (gateIndex < gate.size() && t >= gate[gateIndex].time)
		{
			g = gate[gateIndex].enable;
			++gateIndex;
		}
		if (g != -1)
			adsr.Gate(g);
		double e = adsr.Clock();
		printf("%f %f %d %d\n", t, e, g == 1, g == 0);
	}

	return 0;
}
