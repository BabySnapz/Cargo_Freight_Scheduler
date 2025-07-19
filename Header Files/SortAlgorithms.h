#pragma once

#include <vector>
#include <utility>
#include "Freight.h"
#include "Cargo.h"

class SortAlgorithms
{
public:
    virtual std::vector<std::pair<const Freight&, const Cargo&>> sortList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos) = 0;
    virtual ~SortAlgorithms() = default;
};

class SortByTime : public SortAlgorithms 
{
public:
    std::vector<std::pair<const Freight&, const Cargo&>> sortList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos) override;
};

class SortByCapacity : public SortAlgorithms 
{
public:
    std::vector<std::pair<const Freight&, const Cargo&>> sortList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos) override;
};
