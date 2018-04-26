//
// Created by Madison on 9/14/2016.
//

#ifndef PROJECTS_LOG_HPP
#define PROJECTS_LOG_HPP

#include <utilities/FileQueue.hpp>
#include <utilities/ThreadOStream.hpp>
#include <utilities/PrefixFunctionOStream.hpp>
#include <utilities/DelimiterBufferedOStream.hpp>
#include <utilities/ThreadName.hpp>

namespace flabs
{

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class VerboseLog : public ThreadOStream<CharT, TraitsT>
	{
		public:
			typedef std::basic_string<CharT, TraitsT>        string;
			typedef std::basic_ostringstream<CharT, TraitsT> ostringstream;
			typedef ThreadOStream<CharT, TraitsT>            otstream;
			typedef PrefixFunctionOStream<CharT, TraitsT>    opfstream;
			typedef DelimiterBufferedOStream<CharT, TraitsT> odbstream;
			typedef FileQueue<CharT, TraitsT>                ofqstream;

			VerboseLog(const boost::filesystem::path logDirectory,
				uint32_t maximumLogFileSize = 20480) : otstream(
				std::bind(create, this)), logDirectory(logDirectory),
				maximumLogFileSize(maximumLogFileSize)
			{
			}

			VerboseLog& name(string n)
			{
				ThreadName::name() = n;
				return *this;
			}

		private:
			const boost::filesystem::path logDirectory;
			uint32_t                      maximumLogFileSize;

			static string timestamp()
			{
				ostringstream out;
				out << boost::posix_time::to_iso_extended_string(
					boost::posix_time::microsec_clock::local_time()) << ": ";
				return out.str();
			}

			typename otstream::stream* create()
			{
				ostringstream out;
				out << logDirectory.generic_string() << '/'
					<< ThreadName::name();
				return new opfstream(
					new odbstream(new ofqstream(out.str(), maximumLogFileSize)),
					timestamp);
			}
	};

	typedef VerboseLog<char>    ovstream;
	typedef VerboseLog<wchar_t> wovstream;
}
#endif //PROJECTS_LOG_HPP
