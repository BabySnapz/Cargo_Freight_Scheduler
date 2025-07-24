#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>

// removes whitespace from front and back of a string 
inline  std::string trimWhitespace(const std::string& aString) {
	auto front = aString.begin(), back = aString.end();

	while (front != back && std::isspace(*front))
		++front;
	if (front == back)
		return "";
	do { --back; } while (std::distance(front, back) > 0 && std::isspace(*back));
	return std::string(front, back + 1);
}
// splits a line of string by a specified delimiter
static std::vector<std::string> split(const std::string& aString, char delim) {
	std::vector<std::string> tokensCollection;
	std::string token;
	std::istringstream ss(aString);

	while (std::getline(ss, token, delim)) {
		tokensCollection.push_back(trimWhitespace(token));
	}
	return tokensCollection;
}