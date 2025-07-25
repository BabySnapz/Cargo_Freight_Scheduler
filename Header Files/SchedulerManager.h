#pragma once

#include <vector>
#include <string>
#include <utility>
#include "iSchedulerManager.h"
#include "SchedulerPairVerifier.h"
#include "SortAlgorithms.h"

class SchedulerManager : public iSchedulerManager
{
private:
    std::vector<std::pair<const iFreight&, const iCargo&>> matchedList;
    SortAlgorithms* sortStrategy = nullptr;

public:
    void setStrategy(SortAlgorithms* strategy) override;
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::pair<const iFreight&, const iCargo&>> getMatchedList() override;
    std::vector<std::pair<const iFreight&, const iCargo&>> createMatchedList(
        const std::vector< iFreight*>& freights,
        const std::vector< iCargo*>& cargos) override;
};
