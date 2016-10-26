//
// Created by Madison on 9/15/2016.
//

#ifndef PROJECTS_THREADNAME_HPP
#define PROJECTS_THREADNAME_HPP

#include <map>
#include <thread>
#include <string>
#include <sstream>
#include <mutex>

namespace flabs
{
	//TODO: Should this be static?
	class ThreadName
	{
		private:
			struct threadname
			{
				std::string n;

				threadname();

				bool operator<(const threadname& o) const;
			};

			static std::map<std::thread::id, threadname> names;
			static std::mutex namesMutex;

		public:
			static std::string& name();

			static std::string& name(std::thread::id i);
	};
}

#endif //PROJECTS_THREADNAME_HPP
