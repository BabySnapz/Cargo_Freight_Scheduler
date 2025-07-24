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

    std::vector<const iCargo*> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(), [](const iCargo* a, const iCargo* b) {
        return a->getTime() < b->getTime();
        });

    std::vector<const iFreight*> availableFreights = freights;

    for (const auto* cargo : sortedCargos) {
        for (auto it = availableFreights.begin(); it != availableFreights.end(); ++it) {
            if (SchedulerPairVerifier::isMatched(*cargo, **it)) {
                matched.emplace_back(**it, *cargo);
                availableFreights.erase(it);
                break;
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

    std::vector<const iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), [](const iFreight* a, const iFreight* b) {
        return a->getMaxCapacity() > b->getMaxCapacity();
        });

    std::vector<const iCargo*> unassignedCargos = cargos;

    for (const auto* freight : sortedFreights) {
        auto it = unassignedCargos.begin();
        while (it != unassignedCargos.end()) {
            if (SchedulerPairVerifier::isMatched(**it, *freight)) {
                matched.emplace_back(*freight, **it);
                it = unassignedCargos.erase(it);
                break;
            }
            else {
                ++it;
            }
        }
    }

    return matched;
}
