#include <random>

long double PiApproximation(int NumSamples)
{
	int SamplesInCircle = 0;

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<long double> Dist(-1.0, 1.0);

#pragma omp parallel for reduction (+:SamplesInCircle) private(Dist, gen, rd)
		for (int i = 0; i < NumSamples; i++)
		{
			long double x = Dist(gen);
			long double y = Dist(gen);

			SamplesInCircle += (x * x + y * y < 1);
		}

return 4.0L * (long double)SamplesInCircle / (long double)NumSamples;

}