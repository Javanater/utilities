/*
 * Pretty.h
 *
 *  Created on: Jun 24, 2016
 *      Author: Madison
 */

#ifndef PRETTY_H_
#define PRETTY_H_

#include "PrettySequence.hpp"

namespace flabs
{
	template<class T>
	class Pretty
	{
		public:
			Pretty()
			{
			}

			~Pretty()
			{
			}
	};

	template<class T>
	Pretty<T> pretty(const T& t)
	{
		Pretty<T> p(t);
		return p;
	}

	template<class T, class U>
	PrettySequence operator<<(const Pretty<T>& p, const U& u)
	{
		PrettySequence ps;
		return ps << p << u;
	}
}

#endif
