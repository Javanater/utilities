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
using boost::posix_time::time_facet;
using boost::gregorian::date;
using boost::posix_time::time_duration;
using boost::posix_time::seconds;

namespace flabs
{
mutex                    sleepMonitorMutex;
map<thread::id, Monitor> sleepMonitors;
ptime                    epoch(date(1970, 1, 1));

ptime parseDateTime(string dateTime, string format, locale locale1)
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

ptime toPTime(const time_t& secondsSinceEpoch)
{
	time_duration dur = seconds(secondsSinceEpoch);
	return epoch + dur;
}

time_t secondsSinceEpoch(string dateTime, string format, locale locale1)
{
	return secondsSinceEpoch(parseDateTime(dateTime, format, locale1));
}

time_t ticksSinceEpoch(const ptime& pt)
{
	time_duration diff = pt - epoch;
	return diff.ticks();
}

time_t ticksSinceEpoch(string dateTime, string format, locale locale1)
{
	return ticksSinceEpoch(parseDateTime(dateTime, format, locale1));
}

string formatDateTime(time_t secondsSinceEpoch, string format, locale locale1)
{
	locale        locale2(locale1, new time_facet(format.c_str()));
	ostringstream os;
	os.imbue(locale2);;
	ptime pt = toPTime(secondsSinceEpoch);
	os << pt;
	return os.str();
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

