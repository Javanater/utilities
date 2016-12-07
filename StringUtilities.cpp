#include "StringUtilities.hpp"
#include <cctype>
#include <cstring>
#include <functional>

using namespace std;

namespace flabs
{
	string join(const string sept, const vector<string>& list)
	{
		string str;
		str.assign(list[0]);

		for (unsigned int i = 1; i < list.size(); i++)
		{
			str.append(sept);
			str.append(list[i]);
		}

		return str;
	}

	string& toLower(string& str)
	{
		for (string::iterator i = str.begin(); i != str.end(); i++)
		{
			if (*i >= 'A' && *i <= 'Z')
				*i += ('a' - 'A');
		}

		return str;
	}

	char* toLower(char* str)
	{
		size_t length = strlen(str);
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] += ('a' - 'A');
		}

		return str;
	}

	string& toUpper(string& str)
	{
		for (string::iterator i = str.begin(); i != str.end(); i++)
			if (*i >= 'a' && *i <= 'z')
				*i -= ('a' - 'A');

		return str;
	}

	char* toUpper(char* str)
	{
		size_t length = strlen(str);
		for (size_t i = 0; i < length; i++)
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= ('a' - 'A');

		return str;
	}

	string decToHex(string dec)
	{
		ostringstream stream;
		stream << hex;
		stream << stol(dec);
		return stream.str();
	}

	bool startsWith(const string source, const string prefix)
	{
		return source.compare(0, prefix.length(), prefix) == 0;
	}

	bool equals(const string str1, const string str2)
	{
		if (str1.length() == str2.length())
			return str1.compare(0, str1.length(), str2) == 0;
		else
			return false;
	}

	unsigned int count(const string source, const string s)
	{
		unsigned int total = 0;
		size_t end, pos = 0;

		while (true)
		{
			end = source.find(s, pos);
			if (end == string::npos)
				break;
			pos = end + s.size();
			total++;
		}

		return total;
	}

	bool isintC(const char source)
	{
		return source >= '0' && source <= '9';
	}

	bool isSpaceC(const char source)
	{
		return isspace(source) == 0;
	}

	bool isSpace(const std::string source)
	{
		return all_of(source, isSpaceC);
	}

	string& fill(string& str, size_t width, const char filler)
	{
		ostringstream stream;
		for (size_t i = str.length(); i <= width; ++i)
			stream << filler;
		stream << str;
		str = stream.str();
		return str;
	}
}

bool flabs::endsWith(const string source, const string ending)
{
	size_t length = ending.length();

	if (source.length() >= length)
		return source.compare(source.length() - length, length, ending) == 0;
	else
		return false;
}

bool flabs::islower(const string source)
{
	if (source.length() == 0)
		return false;
	else
		for (string::const_iterator i = source.begin(); i != source.end(); i++)
			if (*i >= 'A' && *i <= 'Z')
				return false;

	return true;
}

bool flabs::isupper(const string source)
{
	if (source.length() == 0)
		return false;
	else
		for (string::const_iterator i = source.begin(); i != source.end(); i++)
			if (*i >= 'a' && *i <= 'z')
				return false;

	return true;
}

bool flabs::isint(const string source)
{
	if (source.length() == 0)
		return false;
	else
		for (string::const_iterator i = source.begin(); i != source.end(); i++)
			if (*i < '0' || *i > '9')
				return false;

	return true;
}

bool flabs::isfloat(const string source)
{
	if (source.length() == 0)
		return false;
	else if (count(source, ".") != 1)
		return false;
	else
		for (string::const_iterator i = source.begin(); i != source.end(); i++)
			if ((*i < '0' || *i > '9') && *i != '.')
				return false;

	return true;
}

bool flabs::isalpha(const string source)
{
	if (source.length() == 0)
		return false;
	else
		for (string::const_iterator i = source.begin(); i != source.end(); i++)
			if ((*i < 'a' || *i > 'z') && (*i < 'A' || *i > 'Z') && *i != ' ')
				return false;

	return true;
}
