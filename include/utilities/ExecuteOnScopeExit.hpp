//
// Created by Madison on 9/7/2016.
//

#ifndef PROJECTS_EXECUTEONRETURN_HPP
#define PROJECTS_EXECUTEONRETURN_HPP

#include <boost/function.hpp>

namespace flabs
{
	class ExecuteOnScopeExit
	{
		private:
			std::function<void()> f;

		public:
			ExecuteOnScopeExit(const std::function<void()>& f);
			~ExecuteOnScopeExit();
	};
}

#endif //PROJECTS_EXECUTEONRETURN_HPP
