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
#include <tuple>
#include "Notifiee.hpp"

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

			/**
			 * Usage:
			 * <code>
			 * Bar bar; // Extends Notifiee
			 * notifier.addNotifiee(bar);
			 * </code>
			 */
			//TODO: Allow Arbitrary argument count (placeholders), or get rid of
			//      Notifiee
//			void addNotifiee(Notifiee<Args...>& notifiee)
//			{
//				using std::placeholders::_1;
//				std::function<void(Args...)>
//					f(std::bind(&Notifiee<Args...>::notified, &notifiee, _1));
//				listeners.push_back(f);
//			}

			void notify(Args& ... data)
			{
				for (auto listener = listeners.begin();
					listener != listeners.end(); ++listener)
					(*listener)(data...);
			}
	};
}

#endif
