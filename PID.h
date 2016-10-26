/*
 * Updateable.h
 *
 *  Created on: Mar 23, 2016
 *      Author: Madison
 */

#ifndef PID_H_
#define PID_H_

#include <math.h>

namespace flabs
{
	template<double P, double D, double I = 0, double INTEGRAL_LIMIT = 0>
	class PID
	{
		private:
			double lastDifference;
			double integral;
			double desiredValue;

		public:
			PID(double desiredValue = 0) :
					lastDifference(0), integral(0), desiredValue(desiredValue)
			{
			}

			virtual ~PID()
			{
			}

			double operator()(double currentValue)
			{
				double difference = desiredValue - currentValue;
				double derivative = difference - lastDifference;
				double output = difference * P + integral * I - derivative * D;
				lastDifference = difference;
				if (I != 0)
				{
					integral += difference;
					if (INTEGRAL_LIMIT > 0)
						integral = std::min(std::max(integral, INTEGRAL_LIMIT), -INTEGRAL_LIMIT);
				}
				return output;
			}

			PID& setDesiredValue(double desiredValue)
			{
				this->desiredValue = desiredValue;
				return *this;
			}
	};
}

#endif
