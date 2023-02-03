#ifndef DOWNSAMPLE_H
#define DOWNSAMPLE_H

#include "printer/Timer.h"
#include <iostream>
#include <vector>

// Передискретизация
template <class T>
struct Downsampler {
    static std::vector<T> downsample(const std::vector<T>& signal, int parameterDown)
	{
		Timer time;
        std::cout << "Передискретизация сигнала" << std::endl;
        uint32_t copySize = 1 + (signal.size() / parameterDown);
        if (signal.size() % parameterDown == 0)
		{
            copySize = signal.size() / parameterDown;
		}

		std::vector<T> copy(copySize);
		uint32_t j = 0;
        for (uint32_t i = 1; i < signal.size(); i += parameterDown)
		{
			copy[j] = signal[i];
			j++;
		}

		return copy;
	}
};

#endif
