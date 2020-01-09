//
// Created by Madison on 9/7/2016.
//

#include <utilities/ExecuteOnScopeExit.hpp>

flabs::ExecuteOnScopeExit::ExecuteOnScopeExit(
	const std::function<void()>& f) : f(f)
{
}

flabs::ExecuteOnScopeExit::~ExecuteOnScopeExit()
{
	f();
}
