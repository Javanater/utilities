//
// Created by Madison on 10/31/2016.
//

#ifndef PROJECTS_BASE64_HPP
#define PROJECTS_BASE64_HPP

#include <string>

namespace flabs
{
	class Base64
	{
		public:
			static const std::string base64_chars;

			static std::string encode(const std::string decoded);

			static std::string decode(const std::string encoded);

			static inline bool is_base64(unsigned char c)
			{
				return (isalnum(c) || (c == '+') || (c == '/'));
			}
	};
}

#endif //PROJECTS_BASE64_HPP
