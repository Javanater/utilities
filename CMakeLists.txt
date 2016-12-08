cmake_minimum_required(VERSION 3.5)
project(Utilities)
set(SOURCE_FILES Comparison.hpp Monitor.cpp Monitor.hpp Notifier.hpp PID.hpp
		Pretty.hpp Pretty.cpp PrettySequence.hpp PrettySequence.cpp
		StringUtilities.hpp StringUtilities.cpp Timer.hpp Timer.cpp utilities.hpp
		utilities.cpp Watchdog.hpp ScopeCounter.hpp FileQueue.hpp
		ExecuteOnScopeExit.cpp ExecuteOnScopeExit.hpp TraceStack.cpp
		TraceStack.hpp ThreadOStream.hpp PrefixFunctionOStream.hpp
		DelimiterBufferedOStream.hpp VerboseLog.hpp ThreadName.cpp
		ThreadName.hpp PrefixOStream.hpp CSVReader.cpp CSVReader.hpp Base64.cpp Base64.hpp)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})