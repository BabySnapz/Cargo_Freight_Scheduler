#include <iostream>
#include "Cargo.h"

using namespace std;

Cargo::Cargo(const std::string& id_, const std::string& location_, 
	const std::string& time_, int cargoGrouping_) : id(id_),location(location_),
	time(time_), cargoGrouping(cargoGrouping_)
{

}

const string& Cargo::getID() const {
	return id;
}

void Cargo::showDetails() const {
	cout << getID() << ", " << getLocation() << ", " << getTime() << ", " 
		<< getCargoGrouping() << endl;
}

void Cargo::edit(const iRecord& editedCargo) {
	const Cargo& tempCargo = static_cast<const Cargo&>(editedCargo);
	location = tempCargo.location;
	time = tempCargo.time;
	cargoGrouping = tempCargo.cargoGrouping;
}

const string& Cargo::getLocation() const {
	return location;
}

const string& Cargo::getTime() const {
	return time;
}

int Cargo::getCargoGrouping() const {
	return cargoGrouping;
}
