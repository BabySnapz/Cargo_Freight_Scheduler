#include <stdexcept>
#include "FreightParams.h"
#include "StringTools.h"

using namespace std;
using namespace StringTools;

void FreightParams::fieldsFromFile(const vector<string>& tokens) {
	if (tokens.size() != 4) {
		throw runtime_error("Expected 4 fields for a freight entry, received \"" + to_string(tokens.size()) + "\" fields.");
	}
	id = trimWhitespace(tokens[0]);
	location = trimWhitespace(tokens[1]);
	time = trimWhitespace(tokens[2]);
	if (id.empty() || location.empty() || time.empty()) {
		throw runtime_error("There are missing fields (id/location/time) for a freight entry.");
	}
	string freightTypeToken = trimWhitespace(tokens[3]);
	if (freightTypeToken.empty()) {
		throw runtime_error("Missing Freight Type.");
	}
	freightType = stringToFreightType(freightTypeToken);
}

FreightParams& FreightParams::setID(const string& id_) {
	id = id_;
	return *this;
}

FreightParams& FreightParams::setLocation(const string& location_) {
	location = location_;
	return *this;
}

FreightParams& FreightParams::setTime(const string& time_) {
	time = time_;
	return *this;
}

FreightParams& FreightParams::setFreightType(const FreightType& freightType_) {
	freightType = freightType_;
	return *this;
}

const string& FreightParams::getID() const {
	return id;
}

const string& FreightParams::getLocation() const {
	return location;
}

const string& FreightParams::getTime() const {
	return time;
}

FreightType FreightParams::getFreightType() const {
	return freightType;
}