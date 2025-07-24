#include <iostream>
#include "Freight.h"

using namespace std;

Freight::Freight(const std::string& id_, const std::string& location_,
    const std::string& time_, FreightType freightType_) : id(id_),
    location(location_), time(time_), freightType(freightType_),
    maxCapacity(computeCapacity(freightType_)), remainingCapacity(maxCapacity)
{

}

const string& Freight::getID() const {
    return id;
}

void Freight::showDetails() const {
    cout << getID() << ", " << getLocation() << ", " << getTime() << ", "
        << freightTypeToString(getFreightType()) << endl;
}

void Freight::edit(const iRecord& editedFreight) {
    const Freight& tempFreight = static_cast<const Freight&>(editedFreight);
    location = tempFreight.getLocation();
    time = tempFreight.getTime();
    freightType = tempFreight.getFreightType();
    maxCapacity = computeCapacity(tempFreight.getFreightType());
    remainingCapacity = tempFreight.getRemainingCapacity();
}

const string& Freight::getLocation() const {
    return location;
}

const string& Freight::getTime() const {
    return time;
}

FreightType Freight::getFreightType() const {
    return freightType;
}

int Freight::computeCapacity(FreightType t) {
    switch (t)
    {
    case FreightType::MiniMover:
        return 2;
    case FreightType::CargoCruiser:
        return 6;
    case FreightType::MegaCarrier:
        return 12;
    }
    return 0;
}

int Freight::getMaxCapacity() const {
    return maxCapacity;
}

int Freight::getRemainingCapacity() const {
    return remainingCapacity;
}

bool Freight::useCapacity(int amount) {
    if (amount <= remainingCapacity) {
        remainingCapacity -= amount;
        return true;
    }
    return false;
}