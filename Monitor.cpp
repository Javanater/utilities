/*
 * Monitor.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: Madison
 */

#include <utilities/Monitor.hpp>
#include <chrono>

using namespace std;

namespace flabs
{
	Monitor::Monitor()
	{
	}

	Monitor::~Monitor()
	{
	}

	bool Monitor::wait(uint64_t timeout)
	{
		unique_lock<mutex> uniqueLock(mutexVariable);
		return conditionVariable.wait_for(uniqueLock, chrono::milliseconds(timeout))
		    != cv_status::timeout;
	}

	void Monitor::notify()
	{
		unique_lock<mutex> uniqueLock(mutexVariable);
		conditionVariable.notify_one();
	}

	void Monitor::notifyAll()
	{
		unique_lock<mutex> uniqueLock(mutexVariable);
		conditionVariable.notify_all();
	}

	void Monitor::lock()
	{
		mutexVariable.lock();
	}

	void Monitor::unlock()
	{
		mutexVariable.unlock();
	}
}
