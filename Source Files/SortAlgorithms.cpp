#include "SortAlgorithms.h"
#include "SchedulerPairVerifier.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<std::pair<const iFreight&, const iCargo&>> SortByTime::sortList(
    const std::vector< iFreight*>& freights,
    const std::vector< iCargo*>& cargos)
{
    std::vector<std::pair<const iFreight&, const iCargo&>> matched;
    std::vector<bool> cargoAssigned(cargos.size(), false);  // Track used cargos

    // Step 1: Sort cargos by time
    std::vector< iCargo*> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(), []( iCargo* a,  iCargo* b) {
        return a->getTime() < b->getTime();
        });

    // Step 2: Sort freights by time
    std::vector< iFreight*> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(), []( iFreight* a,  iFreight* b) {
        return a->getTime() < b->getTime();
        });

    // Step 3: Match cargos to freights based on grouping, capacity, and isMatched
    for (size_t i = 0; i < sortedCargos.size(); ++i) {
        iCargo* cargo = sortedCargos[i];
        int cargoGrouping = cargo->getCargoGrouping(); // Get cargo grouping

        for (auto it = sortedFreights.begin(); it != sortedFreights.end();) {
            iFreight* freight = *it; // Remove const for modification
            int remainingCapacity = freight->getRemainingCapacity();

			std::cout << "cargo quantity: " << cargoGrouping << std::endl; // this is for Debugging purposes!!!

            // Check if the cargo and freight are matched
            if (!SchedulerPairVerifier::isMatched(*cargo, *freight)) {
                ++it; // Skip this freight if not matched
                continue;
            }

            if (cargoGrouping <= remainingCapacity) {
                // Pair cargo with freight
                matched.emplace_back(*freight, *cargo);
                freight->useCapacity(cargoGrouping); // Update freight capacity
                cargoAssigned[i] = true;

                std::cout << "freight capacity: " << freight->getRemainingCapacity() << std::endl; // this is for Debugging purposes!!!

                // Remove freight if its capacity is fully filled
                if (freight->getRemainingCapacity() == 0) {
                    it = sortedFreights.erase(it); // Remove freight from vector
                }
                else {
                    ++it; // Move to next freight
                }
                break; // Move to next cargo
            }
            else if (cargoGrouping > remainingCapacity) {
                // Split cargo across multiple freights
                freight->useCapacity(remainingCapacity); // Use up freight's capacity
                cargoGrouping -= remainingCapacity;      // Reduce cargo grouping

                matched.emplace_back(*freight, *cargo); // Pair partially

                // Remove freight if its capacity is fully filled
                if (freight->getRemainingCapacity() == 0) {
                    it = sortedFreights.erase(it); // Remove freight from vector
                }
                else {
                    ++it; // Move to next freight
                }
            }
            else {
                ++it; // Move to next freight
            }
        }

        // If cargoGrouping is still greater than 0, it remains unpaired
        if (cargoGrouping > 0) {
            continue; // Move to next cargo
        }
    }

    return matched;
}



std::vector<std::pair<const iFreight&, const iCargo&>> SortByCapacity::sortList(
    const std::vector<iFreight*>& freights,
    const std::vector<iCargo*>& cargos)
{
    std::vector<std::pair<const iFreight&, const iCargo&>> matched;

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

    std::vector<bool> cargoMatched(cargos.size(), false);

    for (auto* freight : sortedFreights)
    {
        int remainingCapacity = freight->getRemainingCapacity();

        for (size_t i = 0; i < sortedCargos.size(); ++i)
        {
            if (cargoMatched[i]) continue;

            iCargo* cargo = sortedCargos[i];

            if (!SchedulerPairVerifier::isMatched(*cargo, *freight)) {
                continue;
            }

            int cargoGrouping = cargo->getCargoGrouping();

            if (cargoGrouping <= remainingCapacity) {
                matched.emplace_back(*freight, *cargo);
                freight->useCapacity(cargoGrouping);
                cargo->useCargoGrouping(cargoGrouping); // update cargo
                cargoMatched[i] = true;

                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) {
                    break;
                }
            }
            else if (cargoGrouping > remainingCapacity) {
                freight->useCapacity(remainingCapacity);
                cargo->useCargoGrouping(remainingCapacity); // update cargo

                matched.emplace_back(*freight, *cargo);

                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) {
                    break;
                }
                // No need to update cargoGrouping variable; next loop will get updated value from cargo->getCargoGrouping()
            }
        }
    }
    return matched;
}
