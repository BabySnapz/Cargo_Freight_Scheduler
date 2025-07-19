#include "SortAlgorithms.h"
#include "SchedulerPairVerifier.h"

std::vector<std::pair<const Freight&, const Cargo&>> SortByTime::sortList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos) 
{
    std::vector<std::pair<const Freight&, const Cargo&>> matched;
    for (const Freight& freight : freights) 
    {
        for (const Cargo& cargo : cargos) 
        {
            if (SchedulerPairVerifier::isMatched(cargo, freight)) 
            {
                matched.emplace_back(freight, cargo);
                break;
            }
        }
    }
    return matched;
}

std::vector<std::pair<const Freight&, const Cargo&>> SortByCapacity::sortList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos) 
{
    std::vector<std::pair<const Freight&, const Cargo&>> matched;
    for (const Freight& freight : freights) 
    {
        int count = 0;
        for (const Cargo& cargo : cargos) 
        {
            if (SchedulerPairVerifier::isMatched(cargo, freight)) 
            {
                matched.emplace_back(freight, cargo);
                if (++count >= freight.getCapacity()) break;
            }
        }
    }
    return matched;
}