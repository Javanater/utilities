//
// Created by Madison on 9/6/2016.
//

#ifndef PROJECTS_SCOPECOUNTER_HPP
#define PROJECTS_SCOPECOUNTER_HPP

namespace flabs
{
	template<class T>
	class ScopeCounter
	{
		private:
			T& count;

		public:
			ScopeCounter(T& count) : count(count)
			{
				++count;
			}

			~ScopeCounter()
			{
				--count;
			}

			T value()
			{
				return count;
			}
	};
}
#endif //PROJECTS_SCOPECOUNTER_HPP
