#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <ctime>

using SysClock = std::chrono::system_clock;
using Milliseconds = std::chrono::milliseconds;
using Microseconds = std::chrono::microseconds;

template<class C> using TimePoint = std::chrono::time_point<C>;
template<class T> using Duration = std::chrono::duration<T>;

void GeneratorThreadFunc()
{
	TimePoint<SysClock> start = SysClock::now();

	Duration<double> elapsed_time(0);
	while (elapsed_time.count() < 30)
	{
		std::this_thread::sleep_for(Microseconds(500000));
		elapsed_time = SysClock::now() - start;
		std::cout << "elapsed time: " << elapsed_time.count() << "s" << std::endl;
	}

	return;
}

void main()
{
	std::cout << "Text Stream Generator - started" << std::endl;

	std::thread textGeneratorThread(std::bind(&GeneratorThreadFunc));
	
	textGeneratorThread.join();

	std::cout << "Text Stream Generator - stopped" << std::endl;
}