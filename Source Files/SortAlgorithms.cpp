#include "SortAlgorithms.h"
#include <algorithm>

void SortByTime::sort(std::vector<iFreight*>& freights, std::vector<iCargo*>& cargos) {
    std::sort(freights.begin(), freights.end(), [](iFreight* a, iFreight* b) {
        return a->getTime() < b->getTime();
        });
    std::sort(cargos.begin(), cargos.end(), [](iCargo* a, iCargo* b) {
        return a->getTime() < b->getTime();
        });
}

void SortByCapacity::sort(std::vector<iFreight*>& freights, std::vector<iCargo*>& cargos) {
    std::sort(freights.begin(), freights.end(), [](iFreight* a, iFreight* b) {
        return a->getMaxCapacity() > b->getMaxCapacity();
        });
    std::sort(cargos.begin(), cargos.end(), [](iCargo* a, iCargo* b) {
        return a->getTime() < b->getTime();
        });
}