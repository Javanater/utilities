//
// Created by Madison on 9/7/2016.
//

#ifndef PROJECTS_RUNNINGLOG_HPP
#define PROJECTS_RUNNINGLOG_HPP

#include <boost/filesystem.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdlib.h>

namespace flabs
{
	template<class CharT, class TraitsT/* = std::char_traits<CharT>*/>
	class FileQueue;

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class FileQueueBuffer : public std::basic_streambuf<CharT, TraitsT>
	{
		private:
			typedef FileQueue<CharT, TraitsT> FQ;
			FQ* fileQueue;

		public:
			FileQueueBuffer(FQ* fileQueue) : fileQueue(fileQueue)
			{
			}

			virtual ~FileQueueBuffer()
			{
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

			void write(const CharT* s, std::streamsize n)
			{
				boost::system::error_code errorCode;

				//Make sure there is at least 1 path in the queue
				if (fileQueue->logPathQueue.empty())
					fileQueue->logPathQueue
						.push(fileQueue->generateLogFilePath());

				//Make sure the log file path exists
				create_directories(fileQueue->logStorageDirectory, errorCode);

				if (errorCode)
				{
					//TODO: How to handle errors in a logging library?
					std::cout << "boost::filesystem::create_directories("
						<< fileQueue->logStorageDirectory
						<< ") failed. boost::system:::error_code=" << errorCode
						<< std::endl;
					return;
				}

				//Get existing file size
				uintmax_t fileSize = file_size(fileQueue->logPathQueue.back(),
					errorCode);
				if (errorCode.value() == 2)
					fileSize = 0;
				else if (errorCode.value() != 0)
				{
					boost::system::system_error error(errorCode);
					std::cout << "boost::filesystem::file_size("
						<< fileQueue->logPathQueue.back()
						<< ") failed. boost::system:::error_code=" << errorCode
						<< " boost::system::system_error.what()="
						<< error.what() << std::endl;
					return;
				}

				//Check if this entry will make the file too big
				if (fileSize + n * sizeof(CharT) >
					fileQueue->maximumLogFileSize)
				{
					//Check if we have too many files
					if (fileQueue->logPathQueue.size() >=
						fileQueue->maximumLogFilesToKeep)
					{
						//Delete the last log file
						if (!remove(fileQueue->logPathQueue.front(),
							errorCode) || errorCode)
						{
							std::cout << "boost::filesystem::remove("
								<< fileQueue->logPathQueue.front()
								<< ") failed. boost::system:::error_code="
								<< errorCode << std::endl;
							return;
						}
						fileQueue->logPathQueue.pop();
					}

					//Create a new log file
					fileQueue->logPathQueue
						.push(fileQueue->generateLogFilePath());
				}

				//Open the file for writing
				std::ofstream output(fileQueue->logPathQueue.back()
						.generic_string(),
					std::ofstream::app | std::ofstream::binary);

				//Check if the file opened
				if (!output)
				{
					//TODO: How to handle errors in a logging library?
					std::cout << "std::ofstream("
						<< fileQueue->logPathQueue.back().generic_string()
						<< ", std::ofstream::app | std::ofstream::binary) failed."
						<< std::endl;
					return;
				}

				//Write to the file
				output.write(s, n);
				output.close();
			}
	};

	template<class CharT, class TraitsT = std::char_traits<CharT>>
	class FileQueue : public std::basic_ostream<CharT, TraitsT>
	{
		private:
			boost::filesystem::path             logStorageDirectory;
			uint32_t                            maximumLogFileSize;
			uint32_t                            maximumLogFilesToKeep;
			std::queue<boost::filesystem::path> logPathQueue;
			std::ostringstream                  buffer;

			friend class FileQueueBuffer<CharT, TraitsT>;

		public:
			FileQueue(const boost::filesystem::path logStorageDirectory,
				uint32_t maximumLogFileSize = 20480,
				uint32_t maximumLogFilesToKeep = 2) : logStorageDirectory(
				logStorageDirectory), maximumLogFileSize(maximumLogFileSize),
				maximumLogFilesToKeep(maximumLogFilesToKeep),
				std::basic_ostream<CharT, TraitsT>(
					new FileQueueBuffer<CharT, TraitsT>(this))
			{
			}

			virtual ~FileQueue()
			{
				delete this->rdbuf();
			}

			const boost::filesystem::path& getLogStorageDirectory() const
			{
				return logStorageDirectory;
			}

			uint32_t getMaximumLogFileSize() const
			{
				return maximumLogFileSize;
			}

			uint32_t getMaximumLogFilesToKeep() const
			{
				return maximumLogFilesToKeep;
			}

		private:
			//TODO: Move to Utilities
			static std::string random_string(size_t length)
			{
				auto        randchar = []()->char
				{
					const char   charset[] = "0123456789"
						"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
						"abcdefghijklmnopqrstuvwxyz";
					const size_t max_index = (sizeof(charset) - 1);
					return charset[rand() % max_index];
				};
				std::string str(length, 0);
				std::generate_n(str.begin(), length, randchar);
				return str;
			}

		protected:
			virtual std::string generateLogFileName() const
			{
				boost::posix_time::ptime
								   now  =
					boost::posix_time::microsec_clock::local_time();
				std::ostringstream out;
				std::string        time =
									   boost::posix_time::to_iso_extended_string(
										   now);
				std::replace(time.begin(), time.end(), ':', '-');
				std::replace(time.begin(), time.end(), '.', '-');
				out << time << '-' << random_string(5) << ".txt";
				return out.str();
			}

			virtual boost::filesystem::path generateLogFilePath() const
			{
				boost::filesystem::path logFilePath;

				do
				{
					logFilePath = logStorageDirectory.generic_string() + '/' +
						generateLogFileName();
				}
				while (boost::filesystem::exists(logFilePath));

				return logFilePath;
			}
	};

	typedef FileQueue<char>    ofqstream;
	typedef FileQueue<wchar_t> wofqstream;
}

#endif //PROJECTS_RUNNINGLOG_HPP
