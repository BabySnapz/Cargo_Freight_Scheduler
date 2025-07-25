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

void Freight::edit(const iRecord& editedFreight) {
    const Freight& tempFreight = static_cast<const Freight&>(editedFreight);
    location = tempFreight.getLocation();

    // Debug
    const Freight* tempFreightPtr = dynamic_cast<const Freight*>(&editedFreight);
    if (!tempFreightPtr)
    {
        throw std::invalid_argument("Invalid type for editedFreight in edit.");
    }

    time = tempFreightPtr->getTime();
    freightType = tempFreightPtr->getFreightType();
    maxCapacity = computeCapacity(tempFreightPtr->getFreightType());
    remainingCapacity = tempFreightPtr->getRemainingCapacity();
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

ostream& operator<<(ostream& out, const iFreight& aFreight) {
    out << aFreight.getID() << ", " << aFreight.getLocation() << ", " << aFreight.getTime() << ", "
               << freightTypeToString(aFreight.getFreightType()) << endl;
    return out;
}

