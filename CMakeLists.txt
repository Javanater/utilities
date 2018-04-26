#https://foonathan.net/blog/2016/03/03/cmake-install.html

cmake_minimum_required(VERSION 3.5)

project(utilities)

set(header_path "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(header
	${header_path}/Comparison.hpp
	${header_path}/Monitor.hpp
	${header_path}/Notifier.hpp
	${header_path}/PID.hpp
	${header_path}/Pretty.hpp
	${header_path}/PrettySequence.hpp
	${header_path}/StringUtilities.hpp
	${header_path}/Timer.hpp
	${header_path}/utilities.hpp
	${header_path}/Watchdog.hpp
	${header_path}/ScopeCounter.hpp
	${header_path}/FileQueue.hpp
	${header_path}/ExecuteOnScopeExit.hpp
	${header_path}/TraceStack.hpp
	${header_path}/ThreadOStream.hpp
	${header_path}/PrefixFunctionOStream.hpp
	${header_path}/DelimiterBufferedOStream.hpp
	${header_path}/VerboseLog.hpp
	${header_path}/ThreadName.hpp
	${header_path}/PrefixOStream.hpp
	${header_path}/CSVReader.hpp
	${header_path}/Base64.hpp
	${header_path}/parallel_for.hpp)

set(src
	Monitor.cpp
	Pretty.cpp
	PrettySequence.cpp
	StringUtilities.cpp
	Timer.cpp
	utilities.cpp
	ExecuteOnScopeExit.cpp
	TraceStack.cpp
	ThreadName.cpp
	CSVReader.cpp
	Base64.cpp)

set(tool_dest "bin")
set(include_dest "include/${PROJECT_NAME}")
set(main_lib_dest "lib/${PROJECT_NAME}")
set(lib_dest ${main_lib_dest}/${CMAKE_BUILD_TYPE}")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED chrono system thread)

add_library(${PROJECT_NAME} ${header} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> # for headers when building
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> # for config_impl.hpp when building
    $<INSTALL_INTERFACE:${include_dest}> # for client in install mode
    $<INSTALL_INTERFACE:${lib_dest}> # for config_impl.hpp in install mode)

target_include_directories(${PROJECT_NAME} ${Boost_INCLUDE_DIR})

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} DESTINATION "${lib_dest}")

install(FILES ${header} DESTINATION "${include_dest}")

install(EXPORT ${PROJECT_NAME} DESTINATION "${lib_dest}")