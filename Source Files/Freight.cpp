#include <iostream>
#include "Freight.h"

using namespace std;

Freight::Freight(const std::string& id_, const std::string& location_,
    const std::string& time_, FreightType freightType_) : id(id_),
    location(location_), time(time_), freightType(freightType_)
{

}

const string& Freight::getID() const {
    return id;
}

void Freight::showDetails() const{
    string type;

    switch (freightType)
    {
    case FreightType::MiniMover:
        type = "MiniMover";
        break;
    case FreightType::CargoCruiser:
        type = "CargoCruiser";
        break;
    case FreightType::MegaCarrier:
        type = "MegaCarrier";
        break;
    default:
        
        break;
    }
    cout << id << ", " << location << ", " << time << ", "
        << type << endl;
}
