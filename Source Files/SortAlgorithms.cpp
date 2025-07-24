#include "SortAlgorithms.h"
#include "SchedulerPairVerifier.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<std::pair<const iFreight&, const iCargo&>> SortByTime::sortList(
    const std::vector<const iFreight*>& freights,
    const std::vector<const iCargo*>& cargos)
{
    std::vector<std::pair<const iFreight&, const iCargo&>> matched;
    std::vector<bool> cargoAssigned(cargos.size(), false);  // Track used cargos

    // Step 1: Sort cargos by time
    std::vector<const iCargo*> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(), [](const iCargo* a, const iCargo* b) {
        return a->getTime() < b->getTime();
        });

    // Step 2: Sort freights by time
    std::vector<const iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), [](const iFreight* a, const iFreight* b) {
        return a->getTime() < b->getTime();
        });

    // Step 3: Match each cargo to first available freight
    for (size_t i = 0; i < sortedCargos.size(); ++i) {
        const iCargo* cargo = sortedCargos[i];

        for (const auto* freight : sortedFreights) {
            if (SchedulerPairVerifier::isMatched(*cargo, *freight)) {
                matched.emplace_back(*freight, *cargo);
                cargoAssigned[i] = true;
                break; // move to next cargo
            }
        }
    }

    return matched;
}



std::vector<std::pair<const iFreight&, const iCargo&>> SortByCapacity::sortList(
    const std::vector<const iFreight*>& freights,
    const std::vector<const iCargo*>& cargos)
{
    std::vector<std::pair<const iFreight&, const iCargo&>> matched;

    // Step 1: Sort freights by descending max capacity
    std::vector<const iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), [](const iFreight* a, const iFreight* b) {
        return a->getMaxCapacity() > b->getMaxCapacity(); // Bigger capacity first
        });

    // Step 2: Track which cargos are already matched
    std::vector<bool> cargoMatched(cargos.size(), false);

    // Step 3: For each freight, try to match with cargos
    for (const auto* freight : sortedFreights)
    {
        for (size_t i = 0; i < cargos.size(); ++i)
        {
            if (cargoMatched[i]) continue;

            const auto* cargo = cargos[i];

            if (SchedulerPairVerifier::isMatched(*cargo, *freight))
            {
                matched.emplace_back(*freight, *cargo);
                cargoMatched[i] = true;
                break;  // Only one cargo per freight (if that's your rule)
            }
        }
    }

    return matched;
}
