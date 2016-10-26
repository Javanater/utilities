cmake_minimum_required(VERSION 3.5)
project(Utilities)
set(SOURCE_FILES Comparison.h Monitor.cpp Monitor.h Notifiee.h Notifier.h PID.h
		Pretty.h Pretty.cpp PrettySequence.h PrettySequence.cpp
		StringUtilities.h StringUtilities.cpp Timer.h Timer.cpp utilities.h
		utilities.cpp Watchdog.h ScopeCounter.hpp FileQueue.hpp
		ExecuteOnScopeExit.cpp ExecuteOnScopeExit.hpp TraceStack.cpp
		TraceStack.hpp ThreadOStream.hpp PrefixFunctionOStream.hpp
		DelimiterBufferedOStream.hpp VerboseLog.hpp ThreadName.cpp
		ThreadName.hpp PrefixOStream.hpp CSVReader.cpp CSVReader.hpp)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})