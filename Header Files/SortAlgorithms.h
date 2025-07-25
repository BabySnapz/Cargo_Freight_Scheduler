#pragma once

#include <vector>
#include <utility>
#include "iFreight.h"
#include "iCargo.h"

class SortAlgorithms
{
public:
    // Sorts the vectors in-place
    virtual void sort(std::vector<iFreight*>& freights, std::vector<iCargo*>& cargos) = 0;
    virtual ~SortAlgorithms() = default;
};

class SortByTime : public SortAlgorithms
{
public:
    void sort(std::vector<iFreight*>& freights, std::vector<iCargo*>& cargos) override;
};

class SortByCapacity : public SortAlgorithms
{
public:
    void sort(std::vector<iFreight*>& freights, std::vector<iCargo*>& cargos) override;
};
