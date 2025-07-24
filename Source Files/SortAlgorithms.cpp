
#include "SortAlgorithms.h"
#include "SchedulerManager.h"


// Helper function to group freights by type and their capacity
std::unordered_map<int, std::vector<Freight>> groupFreightsByType(const std::vector<Freight>& freights) 
{
    std::unordered_map<int, std::vector<Freight>> grouped;
    for (const auto& freight : freights) 
    {
        grouped[freight.getMaxCapacity()].push_back(freight);
    }
    return grouped;
}

// Sort by Time: Assign cargos to available freights based on their earliest arrival time

std::vector<std::pair<const Freight&, const Cargo&>> SortByTime::sortList(
    const std::vector<Freight>& freights,
    const std::vector<Cargo>& cargos)
{
    std::vector<std::pair<const Freight&, const Cargo&>> matched;

    // Sort cargos by their arrival time (ascending)
    std::vector<Cargo> sortedCargos = cargos;
    std::sort(sortedCargos.begin(), sortedCargos.end(),
        [](const Cargo& a, const Cargo& b) {
            return a.getTime() < b.getTime();
        });

    // Create a shallow copy of the freights list (they remain constant)
    std::vector<Freight> availableFreights = freights;

    // Loop through each cargo and assign to the first available matching freight
    for (auto& cargo : sortedCargos) {
        for (auto& freight : availableFreights) {

            if (SchedulerPairVerifier::isMatched(cargo, freight)) {
                matched.emplace_back(freight, cargo);  // Add to matched list

                // Remove assigned freight so it won't be reused
                availableFreights.erase(
                    std::remove(availableFreights.begin(), availableFreights.end(), freight),
                    availableFreights.end());
                break;  // Move to next cargo
            }
        }
    }

    return matched;
}


// Sort by Capacity: Assign cargos to freights sorted in descending order of capacity

std::vector<std::pair<const Freight&, const Cargo&>> SortByCapacity::sortList(
    const std::vector<Freight>& freights,
    const std::vector<Cargo>& cargos)
{
    std::vector<std::pair<const Freight&, const Cargo&>> matched;

    // Sort freights by descending capacity
    std::vector<Freight> sortedFreights = freights;
    std::sort(sortedFreights.begin(), sortedFreights.end(),
        [](const Freight& a, const Freight& b) {
            return a.getMaxCapacity() > b.getMaxCapacity();
        });

    // Make a list of cargos that are yet to be assigned
    std::vector<Cargo> unassignedCargos = cargos;

    // Loop through sorted freights (largest first)
    for (auto& freight : sortedFreights) 
    {
        auto it = unassignedCargos.begin();

        while (it != unassignedCargos.end()) 
        {
            // Check if the cargo matches the freight (location + time window)
            if (SchedulerPairVerifier::isMatched(*it, freight)) 
            {
                matched.emplace_back(freight, *it);      // Assign cargo to freight
                it = unassignedCargos.erase(it);         // Remove assigned cargo
                break;                                    // One cargo per freight, move to next freight
            }
            else 
            {
                ++it; // Move to next cargo
            }
        }
    }

    return matched;
}