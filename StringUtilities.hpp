#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <stdarg.h>
#include <list>
#include "utilities.hpp"

namespace flabs
{
	bool startsWith(const std::string source, const std::string prefix);
	bool endsWith(const std::string source, const std::string ending);
	bool equals(const std::string str1, const std::string str2);
	bool islower(const std::string source);
	bool isupper(const std::string source);
	bool isfloat(const std::string source);
	bool isalpha(const std::string source);
	bool isint(const std::string source);
	bool isintC(const char source);
	bool isSpaceC(const char source);
	bool isSpace(const std::string source);
	unsigned int count(const std::string source, const std::string s);
	std::string join(const std::string sept, const std::vector<std::string>& list);
	std::string& toLower(std::string& str);
	std::string& toUpper(std::string& str);
	char* toLower(char* str);
	char* toUpper(char* str);
	std::string decToHex(std::string dec);
	std::string& fill(std::string& str, size_t width, const char filler = ' ');

	template<class UnaryPredicate>
	std::string ltrim(std::string s, UnaryPredicate predicate = isSpaceC)
	{
		s.erase(s.begin(), find_if(s, predicate));
		return s;
	}

	template<class UnaryPredicate>
	std::string rtrim(std::string s, UnaryPredicate predicate = isSpaceC)
	{
		s.erase(find_if(s.rbegin(), s.rend(), predicate).base(), s.end());
		return s;
	}

	template<class UnaryPredicate>
	std::string trim(std::string s, UnaryPredicate predicate)
	{
		return ltrim(rtrim(s, predicate), predicate);
	}

	inline std::string trim(std::string s)
	{
		return trim(s, isSpaceC);
	}

	// TODO: Remove this function and use fmt library instead
	template<int BUFFER_SIZE = 1024>
	std::string format(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		char buffer[BUFFER_SIZE];
		vsprintf_s(buffer, format, args);
		va_end(args);
		return std::string(buffer);
	}

//	template <typename T>
//	T parse(const std::string source, T default = 0)
//	{
//		T result = default;
//		std::stringstream stream;
//		stream << source;
//		stream >> result;
//		return result;
//	}

	template<class List = std::list<std::string>>
	List split(const std::string str, const std::string split)
	{
		List list;
		size_t end, pos = 0;

		do
		{
			end = str.find(split, pos);
			list.push_back(str.substr(pos, end - pos));
			pos = end + split.size();
		}
		while (end != std::string::npos);

		return list;
	}

	template<class List = std::list<std::string>>
	List splitChar(const std::string str, const std::string split)
	{
		List list;
		size_t end, pos = 0;

		do
		{
			end = str.find_first_of(split, pos);
			list.push_back(str.substr(pos, end - pos));
			pos = end + 1;
		}
		while (end != std::string::npos);

		return list;
	}

	template<class List>
	std::string join(const std::string sept, List& list)
	{
		std::ostringstream stream;

		if (list.size() > 0)
		{
			typename List::iterator i = list.begin();
			stream << *i;

			for (++i; i != list.end(); ++i)
				stream << sept << *i;
		}

		return stream.str();
	}
}
