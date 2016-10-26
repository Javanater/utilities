/*
 * Monitor.h
 *
 *  Created on: Apr 20, 2016
 *      Author: Madison
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <mutex>
#include <condition_variable>

namespace flabs
{
	class Monitor
	{
		private:
			std::mutex mutexVariable;
			std::condition_variable conditionVariable;

		public:
			Monitor();
			~Monitor();
			bool wait(uint64_t timeout = 0);
			void notify();
			void notifyAll();
			void lock();
			void unlock();
	};
}

#endif
