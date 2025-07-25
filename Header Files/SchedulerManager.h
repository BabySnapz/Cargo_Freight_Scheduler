#pragma once

#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include "iSchedulerManager.h"
#include "SchedulerPairVerifier.h"
#include "SortAlgorithms.h"

class SchedulerManager : public iSchedulerManager
{
private:
    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> matchedList;
    SortAlgorithms* sortStrategy = nullptr;

public:
    void setStrategy(SortAlgorithms* strategy) override;
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> getMatchedList() override;
    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> createMatchedList(
        const std::vector<iFreight*>& freights,
        const std::vector<iCargo*>& cargos) override;
};
