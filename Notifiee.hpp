/*
 * Notifiee.h
 *
 *  Created on: Apr 15, 2016
 *      Author: Madison
 */

#ifndef NOTIFIEE_H_
#define NOTIFIEE_H_

namespace flabs
{
	template<class Data>
	class Notifiee
	{
		public:
			Notifiee()
			{
			}

			virtual ~Notifiee()
			{
			}

			virtual void notified(Data& data) = 0;
	};
}

#endif
