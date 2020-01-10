//
// Created by Madison on 12/8/2016.
//

#ifndef PROJECTS_PARALLEL_FOR_HPP
#define PROJECTS_PARALLEL_FOR_HPP

#include <functional>
#include <vector>
#include <thread>
#include <mutex>

namespace flabs
{
template<class Iterator, class Fn>
void parallel_for(Iterator begin, Iterator end, Fn fn, uint32_t maxThreads = 8)
{
	std::vector<std::thread> threadPool(maxThreads);
	std::mutex               beginMutex;
	beginMutex.lock();

	for (; begin != end; ++begin)
	{
		Iterator it = begin;
		threadPool[maxThreads - 1] = std::thread([&, it]()
		{
			Iterator it2 = it;
			while (true)
			{
				fn(*it2);
				std::lock_guard<std::mutex> lock(beginMutex);

				if (begin == end)
					break;

				it2 = ++begin;
			}
		});

		if (!--maxThreads)
			break;
	}

	beginMutex.unlock();
	for (std::thread& thread : threadPool)
		try
		{
			thread.join();
		}
		catch (std::exception e)
		{
		}
}

template<class List, class Fn>
void parallel_for(List& list, Fn fn, uint32_t maxThreads = 8)
{
	parallel_for(std::begin(list), std::end(list), fn, maxThreads);
}
}

#endif //PROJECTS_PARALLEL_FOR_HPP
