//
// Created by Madison on 10/31/2016.
//

#include "Base64.hpp"

const std::string flabs::Base64::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

std::string flabs::Base64::encode(const std::string encoded)
{
	return std::__cxx11::string();
}

std::string flabs::Base64::decode(const std::string encoded_string)
{
	int           in_len = encoded_string.size();
	int           i      = 0;
	int           j      = 0;
	int           in_    = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string   ret;

	while (in_len-- && (encoded_string[in_] != '=') &&
		is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] =
				(char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) +
				((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i      = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] =
			(char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] =
			((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
			ret += char_array_3[j];
	}

	return ret;
}
