#include "SchedulerPairVerifier.h"



bool SchedulerPairVerifier::isMatched(const Cargo& cargo, const Freight& freight)
{
    if (cargo.getLocation() != freight.getLocation())
        return false;

    // Parse 12-hour time with AM/PM
    std::tm cargoTm = {}, freightTm = {};
    std::istringstream cargoStream(cargo.getTime());
    std::istringstream freightStream(freight.getTime());

    cargoStream >> std::get_time(&cargoTm, "%I:%M %p");
    freightStream >> std::get_time(&freightTm, "%I:%M %p");

    if (cargoStream.fail() || freightStream.fail()) 
    {
        std::cerr << "Time parsing failed. Make sure time format is HH:MM AM/PM.\n";
        return false;
    }

    // Convert to time_t for arithmetic
    std::time_t cargoTime = std::mktime(&cargoTm);
    std::time_t freightTime = std::mktime(&freightTm);

    // Compare: is cargo arrival time within 15 mins of freight time?
    double diffInSeconds = std::difftime(cargoTime, freightTime);
    return std::abs(diffInSeconds) <= 15 * 60; // 15 minutes = 900 seconds
}