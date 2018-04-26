//
// Created by Madison on 9/11/2016.
//

#ifndef PROJECTS_THREADSTREAM_HPP
#define PROJECTS_THREADSTREAM_HPP

#include <iostream>
#include <sstream>
#include <functional>
#include <thread>
#include <mutex>
#include <map>
#include <list>

namespace flabs
{
	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class ThreadBuffer : public std::basic_streambuf<CharT, TraitsT>
	{
		public:
			typedef std::basic_streambuf<CharT, TraitsT> buf;
			typedef std::basic_ostream<CharT, TraitsT>   stream;

		private:
			std::map<std::thread::id, stream*> threadStreams;
			std::mutex                         threadStreamsMutex;
			std::function<stream*()>           createOStream;
			std::function<void(stream*)>       destroyOStream;

		public:
			ThreadBuffer(const std::function<stream*()>& createOStream,
				std::function<void(stream*)> destroyOStream) : createOStream(
				createOStream), destroyOStream(destroyOStream)
			{
			}

			virtual ~ThreadBuffer()
			{
				std::lock_guard<std::mutex> lock(threadStreamsMutex);
				for (auto& pair : threadStreams)
					destroyOStream(pair.second);
			}

		protected:
			int overflow(int c)
			{
				//TODO: Skip conversion
				CharT car = (CharT) c;
				write(&car, 1);
				return c;
			}

			std::streamsize xsputn(const CharT* s, std::streamsize n)
			{
				write(s, n);
				return n;
			}

			inline void write(const CharT* s, std::streamsize n)
			{
				//TODO: Return characters written
				threadStreamsMutex.lock();
				if (threadStreams.count(std::this_thread::get_id()) == 0)
					threadStreams[std::this_thread::get_id()] = createOStream();
				stream* out = threadStreams[std::this_thread::get_id()];
				threadStreamsMutex.unlock();
				//TODO: Skip std::string creation
				std::basic_string<CharT, TraitsT> text(s, n);
				*out << text;
			}
	};

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class ThreadOStream : public std::basic_ostream<CharT, TraitsT>
	{
		public:
			typedef std::basic_ostream<CharT, TraitsT> stream;

			static void destroy(stream* o)
			{
				delete o;
			}

			ThreadOStream(const std::function<stream*()>& createOStream,
				std::function<void(
					stream*)> destroyOStream = destroy) : std::basic_ostream<
				CharT, TraitsT>(
				new ThreadBuffer<CharT, TraitsT>(createOStream, destroyOStream))
			{
				this->setf(std::ios::unitbuf);
			}

			virtual ~ThreadOStream()
			{
				delete this->rdbuf();
			}
	};

	typedef ThreadOStream<char>    otstream;
	typedef ThreadOStream<wchar_t> wotstream;
}
#endif //PROJECTS_THREADSTREAM_HPP
