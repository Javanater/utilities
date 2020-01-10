//
// Created by Madison on 12/8/2016.
//

#include <utilities/utilities.hpp>
#include <utilities/parallel_for.hpp>
#include "gtest/gtest.h"

using namespace std;
using namespace flabs;

TEST(parallel_forTest, too_many_fast)
{
	vector<int> numbers(100000);

	for (int i = 0; i < numbers.size(); ++i)
		numbers[i] = i;

	parallel_for(numbers, [](int& i){i = -1;});

	for (int    i : numbers)
		ASSERT_EQ(-1, i);
}

TEST(parallel_forTest, too_few_fast)
{
	vector<int> numbers(2);

	for (int i = 0; i < numbers.size(); ++i)
		numbers[i] = i;

	parallel_for(numbers, [](int& i){i = -1;});

	for (int    i : numbers)
		ASSERT_EQ(-1, i);
}

TEST(parallel_forTest, too_many_slow)
{
	vector<int> numbers(1000);

	for (int i = 0; i < numbers.size(); ++i)
		numbers[i] = i;

	parallel_for(numbers, [](int& i)
	{
		i = -1;
		sleepMillis(10);
	});

	for (int    i : numbers)
		ASSERT_EQ(-1, i);
}

TEST(parallel_forTest, too_few_slow)
{
	vector<int> numbers(4);

	for (int i = 0; i < numbers.size(); ++i)
		numbers[i] = i;

	parallel_for(numbers, [](int& i)
	{
		i = -1;
		sleepMillis(1000);
	});

	for (int    i : numbers)
		ASSERT_EQ(-1, i);
}
