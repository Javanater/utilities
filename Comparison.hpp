/*
 * Comparison.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Madison
 */

#ifndef COMPARISON_H_
#define COMPARISON_H_

namespace flabs
{
	template<class X>
	inline bool operator>(const X& lhs, const X& rhs)
	{
		return rhs < lhs;
	}

	template<class X>
	inline bool operator<=(const X& lhs, const X& rhs)
	{
		return !(lhs > rhs);
	}

	template<class X>
	inline bool operator>=(const X& lhs, const X& rhs)
	{
		return !(lhs < rhs);
	}

	template<class X>
	inline bool operator==(const X& lhs, const X& rhs)
	{
		return !(lhs < rhs) && !(lhs > rhs);
	}

	template<class X>
	inline bool operator!=(const X& lhs, const X& rhs)
	{
		return !(lhs == rhs);
	}
}

#endif
