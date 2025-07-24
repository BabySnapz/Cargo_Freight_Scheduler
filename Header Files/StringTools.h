#pragma once
#include <string>
#include <algorithm>
#include <cctype>

// removes whitespace from front and back of a string 
inline const std::string& trimWhitespace(const std::string& aString) {
	auto front = aString.begin(), back = aString.end();

	while (front != back && std::isspace(*front))
		++front;
	if (front == back)
		return "";
	do { --back; } while (std::distance(front, back) > 0 && std::isspace(*back));
	return std::string(front, back + 1);
}
