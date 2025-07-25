#include "SortAlgorithms.h"
#include <algorithm>
#include <string>

// Helper: parse "hh:mmAM" or "hh:mmPM" into minutes since midnight
static int parseTime(const std::string& t) {
    // Expect exactly 7 chars: "07:00AM"
    int hour = std::stoi(t.substr(0, 2));      // [0–1]
    int minute = std::stoi(t.substr(3, 2));      // [3–4]
    std::string ampm = t.substr(5, 2);           // "AM" or "PM"

    // Convert to 24‑hour
    if (ampm == "AM") {
        if (hour == 12) hour = 0;                // 12:xx AM → 00:xx
    }
    else if (ampm == "PM") {
        if (hour != 12) hour += 12;              //  1–11 PM → 13–23
    }

    return hour * 60 + minute;
}

void SortByTime::sort(std::vector<iFreight*>& freights,
    std::vector<iCargo*>& cargos)
{
    std::sort(freights.begin(), freights.end(),
        [](iFreight* a, iFreight* b) {
            return parseTime(a->getTime())
                < parseTime(b->getTime());
        });

    std::sort(cargos.begin(), cargos.end(),
        [](iCargo* a, iCargo* b) {
            return parseTime(a->getTime())
                < parseTime(b->getTime());
        });
}

void SortByCapacity::sort(std::vector<iFreight*>& freights,
    std::vector<iCargo*>& cargos)
{
    std::sort(freights.begin(), freights.end(),
        [](iFreight* a, iFreight* b) {
            return a->getMaxCapacity() > b->getMaxCapacity();
        });

    // (unchanged) cargo sort by time if needed
    std::sort(cargos.begin(), cargos.end(),
        [](iCargo* a, iCargo* b) {
            return parseTime(a->getTime())
                < parseTime(b->getTime());
        });
}
