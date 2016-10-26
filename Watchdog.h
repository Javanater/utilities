/*
 * Watchdog.h
 *
 *  Created on: Apr 15, 2016
 *      Author: Madison
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <string>
#include <thread>
#include <tuple>
#include <atomic>
#include "utilities.h"
#include "Notifier.h"

namespace flabs
{
	template<class ... Args>
	class Watchdog
	{
		private:
			std::function<void(Args...)> f;
			std::tuple<Args...> args;
			uint64_t timeout;
			std::atomic<bool> timedout;
			std::atomic<bool> keepWatching;
			std::atomic<uint64_t> lastUpdatedTime;
			std::thread watchdogThread;

		public:
			/**
			 * Creates a Watchdog object with a timeout of <code>timeout</code> milliseconds.
			 */
			Watchdog(std::function<void(Args...)> func, Args&&... args, uint64_t timeout = 1000) :
					f(func), args(std::make_tuple(std::forward<Args>(args)...)), timeout(timeout),
					    timedout(false), keepWatching(true), lastUpdatedTime(millis()),
					    watchdogThread(&Watchdog::watch, this)
			{
			}

			~Watchdog()
			{
				keepWatching = false;
				interrupt(watchdogThread.get_id());
				watchdogThread.join();
			}

			/**
			 * Updates the arguments that will be used if the watch dog wakes up.
			 *
			 * return - a reference to this object
			 */
			Watchdog& update(Args&&... args)
			{
				this->args = std::make_tuple(std::forward<Args>(args)...);
				return *this;
			}

			/**
			 * "Pets" the watch dog to keep it asleep.
			 *
			 * return - a reference to this object
			 */
			Watchdog& pet()
			{
				lastUpdatedTime = millis();
				return *this;
			}

			bool isTimedout() const
			{
				return timedout;
			}

			uint64_t getTimeout() const
			{
				return timeout;
			}

		private:
			void watch()
			{
				while (keepWatching)
				{
					if (isleep(timeout - (millis() - lastUpdatedTime)) || !keepWatching)
						break;

					if (!timedout && millis() - lastUpdatedTime >= timeout)
					{
						timedout = true;
						untie(f, args);
					}
					else if (timedout && millis() - lastUpdatedTime < timeout)
					{
						timedout = false;
						untie(f, args);
					}
				}
			}
	};
}

#endif
