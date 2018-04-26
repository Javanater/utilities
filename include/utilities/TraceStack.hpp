//
// Created by Madison on 9/7/2016.
//

#ifndef PROJECTS_STACKTRACE_HPP
#define PROJECTS_STACKTRACE_HPP

#include <queue>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <iostream>

#define TRACE_STACK flabs::TraceStack traceStack(__FILE__, __func__, __LINE__);

#ifdef DISABLE_LOG_STACK
#define LOG_STACK(log) (void)0
#else
#define LOG_STACK(log)\
flabs::TraceStack traceStack(__FILE__, __func__, __LINE__, log);
#endif

namespace flabs
{
	class StackTrace;

	struct StackTraceEntry
	{
		std::string file;
		std::string function;
		int         line;

		StackTraceEntry()
		{
		}

		StackTraceEntry(const std::string& file, const std::string& function,
			int line) : file(file), function(function), line(line)
		{
		}
	};

	class TraceStack
	{
		private:
			static std::map<std::thread::id, std::deque<StackTraceEntry>>
							  stackTraces;
			static std::mutex stackTracesMutex;
			std::deque<StackTraceEntry>& stackTrace;
			std::ostream               * log;

		public:
			TraceStack(const char* file, const char* function, int line);

			TraceStack(const char* file, const char* function, int line,
				std::ostream& log);

			~TraceStack();

			static const std::deque<StackTraceEntry>& getStackTrace();

		private:
			static std::deque<StackTraceEntry>& getStackTraceNonConst();
	};

	std::ostream&
	operator<<(std::ostream& out, const StackTraceEntry& stackTraceEntry);

	std::ostream& operator<<(std::ostream& out,
		const std::deque<StackTraceEntry>& stackTrace);
}

#endif //PROJECTS_STACKTRACE_HPP
