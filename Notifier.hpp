/*
 * Notifier.h
 *
 *  Created on: Apr 15, 2016
 *      Author: Madison
 */

#ifndef NOTIFIER_H_
#define NOTIFIER_H_

#include <list>
#include <functional>

namespace flabs
{
template<class ... Args>
class Notifier
{
private:
	std::list<std::function<void(Args...)>> listeners;

public:
	Notifier()
	{
	}

	virtual ~Notifier()
	{
	}

	/**
	 * Usage 1:
	 * <code>
	 * function<void(Data&)> f(function);
	 * notifier.addListener(f);
	 * </code>
	 *
	 * Usage 2:
	 * <code>
	 * Foo foo;
	 * using std::placeholders::_1;
	 * function<void(Data&)> f(bind(&Foo::method, &foo, _1));
	 * notifier.addListener(f);
	 * </code>
	 */
	void addListener(std::function<void(Args...)> f)
	{
		listeners.push_back(f);
	}

	void notify(Args& ... data)
	{
		for (auto& listener : listeners)
			listener(data...);
	}
};
}

#endif
