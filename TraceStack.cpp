//
// Created by Madison on 9/7/2016.
//

#include <sstream>
#include "TraceStack.hpp"

using std::map;
using std::deque;
using std::mutex;
using std::ostream;
using std::ostringstream;
using flabs::TraceStack;
using flabs::StackTraceEntry;
using std::this_thread::get_id;
using std::thread;

map<thread::id, deque<StackTraceEntry>> TraceStack::stackTraces;
mutex                           TraceStack::stackTracesMutex;

TraceStack::TraceStack(const char* file, const char* function,
	int line) : stackTrace(getStackTraceNonConst()), log(nullptr)
{
	stackTrace.emplace_back(file, function, line);
}

TraceStack::TraceStack(const char* file, const char* function, int line,
	ostream& log) : stackTrace(getStackTraceNonConst()), log(&log)
{
	stackTrace.emplace_back(file, function, line);
	log << stackTrace;
}

TraceStack::~TraceStack()
{
	stackTrace.pop_back();
	if (log)
		*log << stackTrace;
}

const deque<StackTraceEntry>& TraceStack::getStackTrace()
{
	return getStackTraceNonConst();
}

deque<StackTraceEntry>& TraceStack::getStackTraceNonConst()
{
	stackTracesMutex.lock();
	deque<StackTraceEntry>& stackTrace = stackTraces[get_id()];
	stackTracesMutex.unlock();
	return stackTrace;
}

ostream& flabs::operator<<(ostream& out, const StackTraceEntry& stackTraceEntry)
{
	out << stackTraceEntry.file << ';' << stackTraceEntry.function << ';'
		<< stackTraceEntry.line;
	return out;
}

ostream&
flabs::operator<<(ostream& out, const deque<StackTraceEntry>& stackTrace)
{
	ostringstream tabs;
	for (const StackTraceEntry& entry : stackTrace)
	{
		out << tabs.str() << entry << '\n';
		tabs << '\t';
	}
	return out;
}
