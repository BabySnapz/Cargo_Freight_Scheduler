#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

namespace StringTools {
	// removes whitespace from front and back of a string 
	inline  std::string trimWhitespace(const std::string& aString) {
		auto first = aString.begin(), last = aString.end() - 1;

		while (first != last && std::isspace(static_cast<unsigned char>(*first))) { //static cast to guard against signed char 
			++first;
		} 
			
		if (first == last) {
			return "";
		}

		--last;
		
		while (last >= first && std::isspace(static_cast<unsigned char>(*last))) {
			--last;
		}

		return std::string(first, last + 1);
	}

	// splits a line of string by a specified delimiter
	inline std::vector<std::string> split(const std::string& aString, char delim) {
		std::vector<std::string> tokensCollection;
		std::string token;
		std::istringstream ss(aString);

		while (std::getline(ss, token, delim)) {
			tokensCollection.push_back(trimWhitespace(token));
		}
		return tokensCollection;
	}
}
