#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer()
	{
        start = std::chrono::steady_clock::now();
	}
	~Timer()
	{
        stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << ":: Время выполнения " << duration.count() << " мс ::" << std::endl;
	}
private:
    std::chrono::time_point<std::chrono::steady_clock> start, stop;
};

#endif

