//
// Created by Madison on 8/26/2016.
//

#include <Utilities/Watchdog.hpp>
#include "gtest/gtest.h"

using namespace std;
using namespace flabs;

TEST(WatchdogTest, iterative_timeout)
{
	for (uint64_t i = 100; i < 500; i += 100)
	{
		atomic<bool> timedout(false);
		Watchdog<>   watchdog([&](){timedout = true;}, i / 2);
		sleepMillis(i);
		ASSERT_EQ(true, timedout);
	}
}

TEST(WatchdogTest, iterative_notimeout)
{
	for (uint64_t i = 100; i < 500; i += 100)
	{
		atomic<bool> timedout(false);
		Watchdog<>   watchdog([&](){timedout = true;}, i * 2);
		sleepMillis(i);
		ASSERT_EQ(false, timedout);
	}
}