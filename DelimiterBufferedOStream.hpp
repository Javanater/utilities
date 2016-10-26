//
// Created by Madison on 9/13/2016.
//

#ifndef PROJECTS_DELIMITERBUFFEREDOSTREAM_HPP
#define PROJECTS_DELIMITERBUFFEREDOSTREAM_HPP

#include <iostream>
#include <sstream>

namespace flabs
{
	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class DelimiterBuffer : public std::basic_streambuf<CharT, TraitsT>
	{
		private:
			CharT delimiter;
			std::basic_streambuf<CharT, TraitsT>* sbuf;
			std::basic_ostringstream<CharT, TraitsT> buffer;

		public:
			DelimiterBuffer(const CharT delimiter,
				std::basic_streambuf<CharT, TraitsT>* sbuf) : delimiter(
				delimiter), sbuf(sbuf)
			{
			}

		protected:
			int sync()
			{
				overflow(TraitsT::eof());
				return sbuf->pubsync();
			}

			int overflow(int c)
			{
				if (c != TraitsT::eof())
					buffer << (CharT) c;
				if (c == delimiter || c == TraitsT::eof())
				{
					std::basic_string<CharT, TraitsT> s = buffer.str();
					sbuf->sputn(s.c_str(), s.length());
					buffer.str("");
				}
				return c;
			}
	};

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class DelimiterBufferedOStream : private virtual DelimiterBuffer<CharT,
		TraitsT>, public std::basic_ostream<CharT, TraitsT>
	{
		private:
			std::basic_ostream<CharT, TraitsT>* out;

		public:
			DelimiterBufferedOStream(std::basic_ostream<CharT, TraitsT>& out,
				const CharT delimiter = '\n') : DelimiterBuffer<CharT, TraitsT>(
				delimiter, out.rdbuf()), std::ios(
				static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(nullptr)
			{
			}

			DelimiterBufferedOStream(std::basic_ostream<CharT, TraitsT>* out,
				const CharT delimiter = '\n') : DelimiterBuffer<CharT, TraitsT>(
				delimiter, out->rdbuf()), std::ios(
				static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(out)
			{
			}

			~DelimiterBufferedOStream()
			{
				if (out)
					delete out;
			}
	};

	typedef DelimiterBufferedOStream<char>    odbstream;
	typedef DelimiterBufferedOStream<wchar_t> wodbstream;
}

#endif //PROJECTS_DELIMITERBUFFEREDOSTREAM_HPP
