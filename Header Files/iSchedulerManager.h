#pragma once
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include "iFreight.h"
#include "iCargo.h"
#include "SortAlgorithms.h"

class iSchedulerManager
{
public:
    virtual void setStrategy(SortAlgorithms* strategy) = 0;
    virtual void exportSchedule(const std::string& filepath) = 0;
    virtual std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> getMatchedList() = 0;
    virtual std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> createMatchedList(
        const std::vector<iFreight*>& freights,
        const std::vector<iCargo*>& cargos) = 0;
    virtual ~iSchedulerManager() = default;
};
