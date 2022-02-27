#ifndef RNG_H
#define RNG_H

#include <random>
#include <time.h>
#include <chrono>
#include <memory>

class RNG
{
public:
	static void seed()
	{
		}

	static int randInt(int min, int max)
	{
	
		if (min > max)
		{
			return max;
		}
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> m_distributor(min, max);
		return m_distributor(generator);
	}

private:
};

#endif
