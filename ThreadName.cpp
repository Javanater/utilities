//
// Created by Madison on 9/15/2016.
//

#include "ThreadName.hpp"

std::map<std::thread::id, flabs::ThreadName::threadname>
	flabs::ThreadName::names;
std::mutex flabs::ThreadName::namesMutex;

flabs::ThreadName::threadname::threadname()
{
	std::ostringstream out;
	out << std::this_thread::get_id();
	n = out.str();
}

bool
flabs::ThreadName::threadname::operator<(const ThreadName::threadname& o) const
{
	return n < o.n;
}

std::string& flabs::ThreadName::name()
{
	return name(std::this_thread::get_id());
}

std::string& flabs::ThreadName::name(std::thread::id i)
{
	std::lock_guard<std::mutex> lock(namesMutex);
	return names[i].n;
}
