/*
 * Timer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: Madison
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <thread>
#include <functional>
#include <queue>
#include <atomic>
#include "Monitor.hpp"

namespace flabs
{
//			class Timer
//			{
//				private:
//					struct TimerTask
//					{
//							int id;
//							std::function<void(int)> callback;
//							uint64_t nextCallTime;
//							uint64_t period;
//
//							inline bool operator<(const TimerTask& task)
//							{
//								return nextCallTime < task.nextCallTime;
//							}
//					};
//
//					std::priority_queue<TimerTask> tasks;
//					std::atomic<bool> keepRunning;
//					Monitor queueMonitor;
//					std::thread timerThread;
//					std::atomic<int> nextID;
//
//				public:
//					Timer();
//					virtual ~Timer();
//					int addTask(uint64_t delay, uint64_t period, std::function<void(int)> callBack);
//					bool removeTask(int id);
//
//				private:
//					void processQueue();
//			};
}

#endif
