#include <stdexcept>
#include "CargoParams.h"
#include "StringTools.h"

using namespace std;

void CargoParams::fieldsFromFile(vector<string>& tokens) {
	if (tokens.size() != 4) {
		throw runtime_error("Expected 4 fields for a cargo entry, received \"" + to_string(tokens.size()) + "\" fields.");
	}

	id = trimWhitespace(tokens[0]);
	location = trimWhitespace(tokens[1]);
	time = trimWhitespace(tokens[2]);
	if (id.empty() || location.empty() || time.empty()) {
		throw runtime_error("There are missing fields (id/location/time) for a cargo entry.");
	}
	string cargoGrpNum = trimWhitespace(tokens[3]);
	if (cargoGrpNum.empty()) {
		throw runtime_error("Missing cargo grouping.");
	}
	//convert safely to int
	try
	{
		cargoGrouping = stoi(cargoGrpNum);
	}
	catch (const std::exception& anException)
	{
		throw runtime_error("Invalid cargo grouping: " + cargoGrpNum + ", " + anException.what());
	}
}

CargoParams& CargoParams::setID(const string& id_) {
	id = id_;
	return *this;
}
CargoParams& CargoParams::setLocation(const string& location_) {
	location = location_;
	return *this;
}
CargoParams& CargoParams::setTime(const string& time_) {
	time = time_;
	return *this;
}
CargoParams& CargoParams::setCargoGrouping(int cargoGrouping_) {
	cargoGrouping = cargoGrouping_;
	return *this;
}

const string& CargoParams::getID() const {
	return id;
}
const string& CargoParams::getLocation() const {
	return location;
}
const string& CargoParams::getTime() const {
	return time;
}
int CargoParams::getCargoGrouping() const {
	return cargoGrouping;
}