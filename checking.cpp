#include "SortAlgorithms.h"
#include "SchedulerPairVerifier.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<std::pair<iFreight&, iCargo&>> SortByTime::sortList(
    std::vector<iFreight*>& freights,
    std::vector<iCargo*>& cargos
)
{
    std::vector<std::pair<iFreight&, iCargo&>> matched;

    // Step 1: Sort cargos by time
    std::vector<iCargo*> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(), [](iCargo* a, iCargo* b) {
        return a->getTime() < b->getTime();
        });

    // Step 2: Sort freights by time
    std::vector<iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), [](iFreight* a, iFreight* b) {
        return a->getTime() < b->getTime();
        });

    // Step 3: Match cargos to freights based on grouping, capacity, and isMatched
    for (size_t i = 0; i < sortedCargos.size(); ++i) {
        iCargo* cargo = sortedCargos[i];
        int cargoGrouping = cargo->getCargoGrouping();

        for (auto it = sortedFreights.begin(); it != sortedFreights.end();) {
            iFreight* freight = *it;
            int remainingCapacity = freight->getRemainingCapacity();

            if (!SchedulerPairVerifier::isMatched(*cargo, *freight)) {
                ++it;
                continue;
            }

            if (cargoGrouping <= remainingCapacity) {
                matched.emplace_back(*freight, *cargo);
                freight->useCapacity(cargoGrouping);
                cargo->useCargoGrouping(cargoGrouping);

                if (freight->getRemainingCapacity() == 0) {
                    it = sortedFreights.erase(it);
                }
                else {
                    ++it;
                }
                break;
            }
            else if (cargoGrouping > remainingCapacity) {
                freight->useCapacity(remainingCapacity);
                cargo->useCargoGrouping(remainingCapacity);
                cargoGrouping -= remainingCapacity;

                matched.emplace_back(*freight, *cargo);

                if (freight->getRemainingCapacity() == 0) {
                    it = sortedFreights.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
    }

    return matched;
}



std::vector<std::pair<iFreight&, iCargo&>> SortByCapacity::sortList(
    std::vector<iFreight*>& freights,
    std::vector<iCargo*>& cargos
)
{
    std::vector<std::pair<iFreight&, iCargo&>> matched;

    // Step 1: Sort freights by descending max capacity
    std::vector<iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), [](iFreight* a, iFreight* b) {
        return a->getMaxCapacity() > b->getMaxCapacity();
        });

    // Step 2: Sort cargos by arrival time
    std::vector<iCargo*> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(), [](iCargo* a, iCargo* b) {
        return a->getTime() < b->getTime();
        });

    // Step 3: Match cargos to freights based on capacity and timing
    for (auto* freight : sortedFreights) {
        int remainingCapacity = freight->getRemainingCapacity();

        for (size_t i = 0; i < sortedCargos.size(); ++i) {
            iCargo* cargo = sortedCargos[i];
            int cargoGrouping = cargo->getCargoGrouping();

            if (!SchedulerPairVerifier::isMatched(*cargo, *freight)) {
                continue;
            }

            if (cargoGrouping <= remainingCapacity) {
                matched.emplace_back(*freight, *cargo);
                freight->useCapacity(cargoGrouping);
                cargo->useCargoGrouping(cargoGrouping);

                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) {
                    break;
                }
            }
            else if (cargoGrouping > remainingCapacity) {
                freight->useCapacity(remainingCapacity);
                cargo->useCargoGrouping(remainingCapacity);
                cargoGrouping -= remainingCapacity;

                matched.emplace_back(*freight, *cargo);

                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) {
                    break;
                }
            }
        }
    }

    return matched;
}