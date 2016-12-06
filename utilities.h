/*
 * utilities.h
 *
 *  Created on: Mar 24, 2016
 *      Author: Madison
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <chrono>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <thread>
#include <tuple>
#include <functional>
#include <utility>
#include <boost/date_time.hpp>

#define __FFL__ __FILE__, __func__, __LINE__

#define STREAM_POINTER(T)\
inline std::ostream& operator<<(std::ostream& out, const T* pointer)\
{\
    if (pointer == nullptr)\
        out << "nullptr";\
    else\
        out << *pointer;\
    return out;\
}

namespace flabs
{
//TODO: Decide if Utilities should be dependant on boost.
boost::posix_time::ptime parseDateTime(std::string dateTime, std::string format,
	std::locale locale1 = std::locale::classic());

std::time_t secondsSinceEpoch(const boost::posix_time::ptime& pt);

std::time_t secondsSinceEpoch(std::string dateTime, std::string format,
	std::locale locale1 = std::locale::classic());

std::time_t ticksSinceEpoch(const boost::posix_time::ptime& pt);

std::time_t ticksSinceEpoch(std::string dateTime, std::string format,
	std::locale locale1 = std::locale::classic());

template<class T, class ... Args>
T* construct(Args&& ... args)
{
	return new T(std::forward<Args>(args)...);
}

/**
 * Sleeps for the specified number of milliseconds.
 */
void sleepMillis(uint64_t millis);

/**
 * Sleeps for the specified number of milliseconds, or until interrupted.
 * Returns true if interrupted, false otherwise.
 */
bool isleep(uint64_t millis);

/**
 * Interrupts the thread with the given id iff that thread is currently sleeping
 * in the com::fortenberryLabs::utilities::isleep function.
 */
void interrupt(std::thread::id id);

/**
 * Convenience function for the REDICULOUSLY long way to acquire the current
 * time in nanoseconds.
 */
inline uint64_t nanos()
{
	return (uint64_t) std::chrono::high_resolution_clock::now()
		.time_since_epoch().count();
}

/**
 * Convenience function for the REDICULOUSLY long way to acquire the current
 * time in microseconds.
 */
inline uint64_t micros()
{
	return (uint64_t) std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/**
 * Convenience function for the REDICULOUSLY long way to acquire the current
 * time in milliseconds.
 */
inline uint64_t millis()
{
	return (uint64_t) std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/**
 * Drop in replacement for std::less. Dereferences the pointers before
 * comparing them. NULL/INVALID POINTERS WILL SEG-FAULT!
 */
template<class T>
struct lessPointer
{
	bool operator()(const T& x, const T& y) const
	{
		return *x < *y;
	}

	typedef T    first_argument_type;
	typedef T    second_argument_type;
	typedef bool result_type;
};

template<class T>
std::string toString(const T& t)
{
	std::ostringstream out;
	out << t;
	return out.str();
}

template<typename MAP>
struct DefaultValueMap
{
	typedef typename MAP::key_type    K;
	typedef typename MAP::mapped_type V;
	typedef typename MAP::iterator    CIT;

	DefaultValueMap(MAP& m, V default_val) : m_map(m), default_val(default_val)
	{
	}

	V& operator[](K& key)
	{
		CIT it = m_map.find(key);
		if (it == m_map.end())
		{
			V& v = m_map[key];
			v = default_val;
			return v;
		}
		return it->second;
	}

private:
	MAP& m_map;
	V default_val;
};

template<typename MAP>
DefaultValueMap<MAP> wrapMap(MAP& m, typename MAP::mapped_type default_val)
{
	return DefaultValueMap<MAP>(m, default_val);
}

inline std::string toStandardTime(double seconds)
{
	const double       MILLISECONDS = .001;
	const uintmax_t    MINUTES      = 60;
	const uintmax_t    HOURS        = MINUTES * 60;
	const uintmax_t    DAYS         = HOURS * 24;
	const uintmax_t    YEARS        = DAYS * 365;
	std::ostringstream out;

	uintmax_t years = (uintmax_t) (seconds / YEARS);
	seconds -= years * YEARS;

	uintmax_t days = (uintmax_t) (seconds / DAYS);
	seconds -= days * DAYS;

	uintmax_t hours = (uintmax_t) (seconds / HOURS);
	seconds -= hours * HOURS;

	uintmax_t minutes = (uintmax_t) (seconds / MINUTES);
	seconds -= minutes * MINUTES;

	uintmax_t secs = (uintmax_t) (seconds);
	seconds -= secs;

	uintmax_t milliseconds = (uintmax_t) (seconds / MILLISECONDS);

	out.fill('0');
	out.width(4);
	out << years;
	out << ':';
	out.width(3);
	out << days;
	out << ':';
	out.width(2);
	out << hours;
	out << ':';
	out.width(2);
	out << minutes;
	out << ':';
	out.width(2);
	out << secs;
	out << '.';
	out.width(3);
	out << milliseconds;

	return out.str();
}

// Convenience functions
template<class List>
inline void sort(List list)
{
	std::sort(list.begin(), list.end());
}

template<class List, class Function>
inline bool all_of(List& list, Function fn)
{
	return std::all_of(list.begin(), list.end(), fn);
}

template<class List, class Function>
inline Function for_each(List& list, Function fn)
{
	return std::for_each(list.begin(), list.end(), fn);
}

template<class List, class UnaryPredicate,
	class Iterator = typename List::iterator>
inline Iterator find_if(List& list, UnaryPredicate pred)
{
	return std::find_if(list.begin(), list.end(), pred);
}

template<class List, class UnaryPredicate,
	class Iterator = typename List::iterator>
inline Iterator find_if_not(List& list, UnaryPredicate pred)
{
	return std::find_if_not(list.begin(), list.end(), pred);
}

template<class List, class UnaryPredicate,
	class Iterator = typename List::iterator>
inline Iterator remove_if(List& list, UnaryPredicate pred)
{
	return std::remove_if(list.begin(), list.end(), pred);
}

template<class List, class OutputIterator>
inline OutputIterator copy(List& list, OutputIterator result)
{
	return std::copy(list.begin(), list.end(), result);
}

template<class List, class UnaryPredicate,
	class Iterator = typename List::iterator>
inline List& erase_if(List& list, UnaryPredicate pred)
{
	list.erase(remove_if(list, pred), list.end());
	return list;
}

template<std::size_t ... Ts>
struct gen_index
{
};

template<std::size_t N, std::size_t ... Ts>
struct gen_seq : gen_seq<N - 1, N - 1, Ts...>
{
};

template<std::size_t ... Ts>
struct gen_seq<0, Ts...> : gen_index<Ts...>
{
};

template<typename ... Args, std::size_t ... Is>
void untie(std::function<void(Args...)>& f, std::tuple<Args...>& tup,
	gen_index<Is...>)
{
	f(std::get<Is>(tup)...);
}

template<typename ... Args>
void untie(std::function<void(Args...)>& f, std::tuple<Args...>& tup)
{
	untie(f, tup, gen_seq<sizeof...(Args)>
		{});
}
}

#endif
