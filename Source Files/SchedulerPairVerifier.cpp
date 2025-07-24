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

    // Assume time is in format: "hh:mmAM" or "hh:mmPM"
    cargoStream >> std::get_time(&cargoTm, "%I:%M%p");
    freightStream >> std::get_time(&freightTm, "%I:%M%p");

    if (cargoStream.fail() || freightStream.fail()) {
        std::cerr << "[DEBUG] Failed to parse time - Cargo: " << cargo.getTime()
            << ", Freight: " << freight.getTime() << "\n";
        return false;
    }

    // Set dummy date to avoid mktime returning 0
    cargoTm.tm_year = freightTm.tm_year = 124;  // Year 2024
    cargoTm.tm_mon = freightTm.tm_mon = 0;    // January
    cargoTm.tm_mday = freightTm.tm_mday = 1;    // 1st

    std::time_t cargoTime = std::mktime(&cargoTm);
    std::time_t freightTime = std::mktime(&freightTm);

    if (cargoTime == -1 || freightTime == -1) {
        std::cerr << "[DEBUG] mktime failed\n";
        return false;
    }

    if (freightTime < cargoTime) {
        return false;
    }

    double diffInSeconds = std::difftime(freightTime, cargoTime);
    int absSeconds = static_cast<int>(std::abs(diffInSeconds));
    int hours = absSeconds / 3600;
    int minutes = (absSeconds % 3600) / 60;

    std::cout << "[DEBUG] Time diff: " << hours << "h " << minutes << "m"
        << " between Cargo: " << cargo.getID()
        << " and Freight: " << freight.getID() << "\n";

    return std::abs(diffInSeconds) <= 15 * 60;
}