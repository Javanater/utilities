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
	class PrefixFunctionBuffer : public std::basic_streambuf<CharT, TraitsT>
	{
		private:
			std::function<std::basic_string<CharT, TraitsT>()> prefix;
			std::basic_streambuf<CharT, TraitsT>* sbuf;
			bool need_prefix;

		public:
			PrefixFunctionBuffer(const std::function<
				std::basic_string<CharT, TraitsT>()>& prefix,
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
						std::basic_string<CharT, TraitsT> pre = prefix();
						if (!pre.empty() &&
							pre.size() != sbuf->sputn(&pre[0], pre.size()))
							return TraitsT::eof();
					}
					need_prefix = c == '\n';
				}
				return sbuf->sputc(c);
			}
	};

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class PrefixFunctionOStream :
		private virtual PrefixFunctionBuffer<CharT, TraitsT>,
		public std::basic_ostream<CharT, TraitsT>
	{
		private:
			std::basic_ostream<CharT, TraitsT>* out;

		public:
			PrefixFunctionOStream(std::basic_ostream<CharT, TraitsT>& out,
				const std::function<
					std::basic_string<CharT, TraitsT>()>& prefix) :
				PrefixFunctionBuffer<CharT, TraitsT>(prefix, out.rdbuf()),
				std::ios(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(nullptr)
			{
			}

			PrefixFunctionOStream(std::basic_ostream<CharT, TraitsT>* out,
				const std::function<
					std::basic_string<CharT, TraitsT>()>& prefix) :
				PrefixFunctionBuffer<CharT, TraitsT>(prefix, out->rdbuf()),
				std::ios(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				std::ostream(
					static_cast<std::basic_streambuf<CharT, TraitsT>*>(this)),
				out(out)
			{
			}

			~PrefixFunctionOStream()
			{
				if (out)
					delete out;
			}
	};

	typedef PrefixFunctionOStream<char>    opfstream;
	typedef PrefixFunctionOStream<wchar_t> wopfstream;
}

#endif //PROJECTS_PREFIXSTREAM_HPP
