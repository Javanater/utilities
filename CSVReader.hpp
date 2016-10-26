//
// Created by Madison on 10/7/2016.
//

#ifndef PROJECTS_CSVFILE_HPP
#define PROJECTS_CSVFILE_HPP

#include <boost/filesystem.hpp>
#include <sstream>

namespace flabs
{
	class CSVReader
	{
		private:
			bool                                useHeaders;
			std::vector<std::string>            headers;
			std::list<std::vector<std::string>> rows;
			std::exception                      error;
			bool                                errorOccurred;

		public:
			CSVReader(boost::filesystem::path filePath,
				bool useHeaders = false);

			const std::exception getError();

			operator bool();

			template<class OutputIt>
			void loadColumn(size_t column, OutputIt first)
			{
				for (auto& row : rows)
					if (column < row.size())
					{
						std::istringstream in(row[column]);
						typename OutputIt::value_type value;
						in >> value;
						*first++ = value;
					}
			}

			template<class OutputIt>
			void loadColumn(std::string column, OutputIt first)
			{
				for (size_t c = 0; c < headers.size(); ++c)
					if (column == headers[c])
					{
						loadColumn(c, first);
						return;
					}

				error         = std::runtime_error("Column not found");
				errorOccurred = true;
			}
	};
}

#endif //PROJECTS_CSVFILE_HPP
