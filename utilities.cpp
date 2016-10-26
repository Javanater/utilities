/*
 * utilities.cpp
 *
 *  Created on: Apr 15, 2016
 *      Author: Madison
 */

#include "utilities.h"
#include "Monitor.h"
#include <map>

using namespace std;
using boost::posix_time::ptime;
using boost::posix_time::time_input_facet;
using boost::gregorian::date;
using boost::posix_time::time_duration;

namespace flabs
{
	mutex                    sleepMonitorMutex;
	map<thread::id, Monitor> sleepMonitors;
	ptime                    epoch(date(1970, 1, 1));

	ptime parseDateTime(string dateTime, string format, std::locale locale1)
	{
		locale        locale2(locale1, new time_input_facet(format));
		istringstream is(dateTime);
		is.imbue(locale2);
		ptime pt;
		is >> pt;
		return pt;
	}

	time_t secondsSinceEpoch(const ptime& pt)
	{
		time_duration diff = pt - epoch;
		return diff.ticks() / time_duration::rep_type::ticks_per_second;
	}

	std::time_t secondsSinceEpoch(std::string dateTime, std::string format,
		std::locale locale1)
	{
		return secondsSinceEpoch(parseDateTime(dateTime, format, locale1));
	}

	std::time_t ticksSinceEpoch(const boost::posix_time::ptime& pt)
	{
		time_duration diff = pt - epoch;
		return diff.ticks();
	}

	std::time_t ticksSinceEpoch(std::string dateTime, std::string format,
		std::locale locale1)
	{
		return ticksSinceEpoch(parseDateTime(dateTime, format, locale1));
	}

	void sleepMillis(uint64_t millis)
	{
		this_thread::sleep_for(chrono::milliseconds(millis));
	}

	bool isleep(uint64_t millis)
	{
		Monitor* monitor;

		{
			unique_lock<mutex> lock(sleepMonitorMutex);
			monitor = &sleepMonitors[this_thread::get_id()];
		}

		return monitor->wait(millis);
	}

	void interrupt(thread::id id)
	{
		Monitor* monitor;

		{
			unique_lock<mutex> lock(sleepMonitorMutex);
			monitor = &sleepMonitors[id];
		}

		monitor->notifyAll();
	}
}

