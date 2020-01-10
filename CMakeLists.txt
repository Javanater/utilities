#https://foonathan.net/blog/2016/03/03/cmake-install.html

cmake_minimum_required(VERSION 3.5)

project(utilities)

set(header_path "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(HEADERS
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
	src/Monitor.cpp
	src/Pretty.cpp
	src/PrettySequence.cpp
	src/StringUtilities.cpp
	src/Timer.cpp
	src/utilities.cpp
	src/ExecuteOnScopeExit.cpp
	src/TraceStack.cpp
	src/ThreadName.cpp
	src/CSVReader.cpp
	src/Base64.cpp
)

set(tool_dest "bin")
set(include_dest "include/${PROJECT_NAME}")
set(main_lib_dest "lib")
set(lib_dest "${main_lib_dest}/${CMAKE_BUILD_TYPE}")

find_package(Boost REQUIRED chrono thread)

add_library(${PROJECT_NAME} ${HEADERS} ${src})

set(INSTALL_SUFFIX /${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
	$<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>)

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX}>)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_Test
	test/parallel_forTest.cpp
    test/WatchdogTest.cpp
)

target_link_libraries(${PROJECT_NAME}_Test
	${PROJECT_NAME}
	Boost::unit_test_framework
    GTest::Main
)

if(USE_POSTFIX AND CMAKE_CONFIGURATION_TYPES)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d" MINSIZEREL_POSTFIX "_m" RELWITHDEBINFO_POSTFIX "_r")
endif()

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX})
install(EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

configure_file(scripts/${PROJECT_NAME}.pc.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
