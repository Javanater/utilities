//
// Created by Madison on 9/12/2016.
//

#ifndef PROJECTS_PREFIXSTREAM_HPP
#define PROJECTS_PREFIXSTREAM_HPP

#include <iostream>
#include <functional>

namespace flabs
{
	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class PrefixBuffer : public std::basic_streambuf<CharT, TraitsT>
	{
		private:
			std::basic_string<CharT, TraitsT> prefix;
			std::basic_streambuf<CharT, TraitsT>* sbuf;
			bool need_prefix;

		public:
			PrefixBuffer(const std::basic_string<CharT, TraitsT> prefix,
				std::basic_streambuf<CharT, TraitsT>* sbuf) :
				prefix(prefix), sbuf(sbuf), need_prefix(true)
			{
			}

		protected:
			int sync()
			{
				return sbuf->pubsync();
			}

			int overflow(int c)
			{
				if (c != TraitsT::eof())
				{
					if (need_prefix)
					{
						if (prefix.size() !=
							sbuf->sputn(&prefix[0], prefix.size()))
							return TraitsT::eof();
					}
					need_prefix = c == '\n';
				}
				return sbuf->sputc(c);
			}
	};

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class PrefixOStream :
		private virtual PrefixBuffer<CharT, TraitsT>,
		public std::basic_ostream<CharT, TraitsT>
	{
		private:
			std::basic_ostream<CharT, TraitsT>* out;

		public:
			PrefixOStream(std::basic_ostream<CharT, TraitsT>& out,
				const std::basic_string<CharT, TraitsT> prefix) :
				PrefixBuffer<CharT, TraitsT>(prefix, out.rdbuf()), std::ios(
				static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(nullptr)
			{
			}

			PrefixOStream(std::basic_ostream<CharT, TraitsT>* out,
				const std::basic_string<CharT, TraitsT> prefix) :
				PrefixBuffer<CharT, TraitsT>(prefix, out->rdbuf()), std::ios(
				static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(out)
			{
			}

			~PrefixOStream()
			{
				if (out)
					delete out;
			}
	};

	typedef PrefixOStream<char>    opstream;
	typedef PrefixOStream<wchar_t> wopstream;
}

#endif //PROJECTS_PREFIXSTREAM_HPP
