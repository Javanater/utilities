/*
 * Timer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: Madison
 */

#include <utilities/Timer.hpp>
#include <utilities/utilities.hpp>

using namespace std;

namespace flabs
{
//			Timer::Timer() : nextID(0)
//			{
//				timerThread = thread(processQueue, this);
//			}
//
//			Timer::~Timer()
//			{
//				keepRunning = false;
//				interrupt(timerThread.get_id());
//				timerThread.join();
//			}
//
//			int Timer::addTask(uint64_t delay, uint64_t period, std::function<void(int)> callBack)
//			{
//				TimerTask task;
//				task.id = nextID++;
//				task.callback = callBack;
//				task.period = period;
//				task.nextCallTime = micros() + delay;
//				lock_guard<Monitor> lock(queueMonitor);
//
//			}
//
//			bool Timer::removeTask(int id)
//			{
//				return false;
//			}
//
//			void Timer::processQueue()
//			{
//				keepRunning = true;
//				while (keepRunning)
//				{
//				}
//			}
}
