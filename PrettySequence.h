/*
 * PrettySequence.h
 *
 *  Created on: Jun 24, 2016
 *      Author: Madison
 */

#ifndef PRETTYSEQUENCE_H_
#define PRETTYSEQUENCE_H_

#include <map>
#include <list>
#include <string>
#include "utilities.h"
#include "StringUtilities.h"

namespace flabs
{
	class PrettySequence
	{
		public:
			std::map<int, std::list<std::string>> lines;
			std::list<size_t> lineWidths;
			int minimum = 0;

		public:
			PrettySequence()
			{
			}

			~PrettySequence()
			{
			}

			friend std::ostream& operator<<(std::ostream& out, PrettySequence sequence)
			{
				int lineIndex = sequence.minimum;
				for (size_t i = 0; i <= sequence.lines.size(); ++i, ++lineIndex)
				{
					auto width = sequence.lineWidths.begin();
					for (std::string& string : sequence.lines[lineIndex])
					{
						out.width(*width);
						out << string;
						++width;
					}
					out.width(0);
					out << std::endl;
				}
				return out;
			}
	};

	template<class U>
	PrettySequence operator<<(PrettySequence sequence, const U& u)
	{
		std::string prettyString = trim(toString(u));
		std::list<std::string> prettyLines = split(prettyString, "\n");
		int offset = -prettyLines.size() / 2;
		size_t width = 0;
		int lineIndex = 0;

		if (offset < sequence.minimum)
			sequence.minimum = offset;

		for (const std::string& line : prettyLines)
		{
			if (width < line.length())
				width = line.length();
			sequence.lines[lineIndex++ + offset].push_back(std::move(line));
		}

		sequence.lineWidths.push_back(width);

		return sequence;
	}
}

#endif
