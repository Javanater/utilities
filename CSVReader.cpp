//
// Created by Madison on 10/7/2016.
//

#include "CSVReader.hpp"

using std::string;
using std::exception;
using std::ifstream;
using std::getline;
using std::istringstream;
using boost::filesystem::path;
using boost::filesystem::canonical;
using boost::filesystem::absolute;

flabs::CSVReader::CSVReader(path filePath, bool useHeaders) :
	useHeaders(useHeaders), errorOccurred(false)
{
	try
	{
		ifstream csvFile(absolute(filePath).generic_string());
		if (!csvFile)
			return;
		string line;
		while (getline(csvFile, line))
		{
			rows.emplace_back();
			auto& row = *--rows.end();
			istringstream lineIn(line);
			string value;
			while (getline(lineIn, value, ','))
				row.push_back(value);
		}
	}
	catch (const exception& e)
	{
		error = e;
		errorOccurred = true;
	}
}

const exception flabs::CSVReader::getError()
{
	return error;
}

flabs::CSVReader::operator bool()
{
	return errorOccurred;
}
