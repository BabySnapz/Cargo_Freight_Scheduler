#pragma once

#include <vector>
#include <utility>
#include "iFreight.h"
#include "iCargo.h"

class SortAlgorithms
{
public:
    virtual std::vector<std::pair<const iFreight&, const iCargo&>> sortList(
        const std::vector<const iFreight*>& freights,
        const std::vector<const iCargo*>& cargos) = 0;

    virtual ~SortAlgorithms() = default;
};

class SortByTime : public SortAlgorithms
{
public:
    std::vector<std::pair<const iFreight&, const iCargo&>> sortList(
        const std::vector<const iFreight*>& freights,
        const std::vector<const iCargo*>& cargos) override;
};

class SortByCapacity : public SortAlgorithms
{
public:
    std::vector<std::pair<const iFreight&, const iCargo&>> sortList(
        const std::vector<const iFreight*>& freights,
        const std::vector<const iCargo*>& cargos) override;
};
