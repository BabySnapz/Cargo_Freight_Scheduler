#include "SchedulerPairVerifier.h"


bool SchedulerPairVerifier::isMatched(const iCargo& cargo, const iFreight& freight)
{
    if (cargo.getLocation() != freight.getLocation()) {
        std::cout << "[DEBUG] Location mismatch: " << cargo.getLocation()
            << " != " << freight.getLocation() << "\n";
        return false;
    }

    std::tm cargoTm = {}, freightTm = {};
    std::istringstream cargoStream(cargo.getTime());
    std::istringstream freightStream(freight.getTime());

    cargoStream >> std::get_time(&cargoTm, "%I:%M %p");
    freightStream >> std::get_time(&freightTm, "%I:%M %p");

    if (cargoStream.fail() || freightStream.fail()) {
        std::cerr << "[DEBUG] Time parsing failed for Cargo: " << cargo.getTime()
            << ", Freight: " << freight.getTime() << "\n";
        return false;
    }

    std::time_t cargoTime = std::mktime(&cargoTm);
    std::time_t freightTime = std::mktime(&freightTm);
    double diffInSeconds = std::difftime(cargoTime, freightTime);

    std::cout << "[DEBUG] Time diff: " << std::abs(diffInSeconds)
        << " seconds between Cargo: " << cargo.getID()
        << " and Freight: " << freight.getID() << "\n";

    return std::abs(diffInSeconds) <= 15 * 60;
}
