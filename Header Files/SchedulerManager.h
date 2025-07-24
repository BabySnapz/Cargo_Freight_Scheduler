#pragma once

#include <vector>
#include <string>
#include <utility>
#include "iSchedulerManager.h"
#include "SchedulerPairVerifier.h"
#include "SortAlgorithms.h"
#include "iFreight.h"
#include "iCargo.h"

class SchedulerManager : public iSchedulerManager, SchedulerPairVerifier
{
private:
    std::vector<std::pair<const iFreight&, const iCargo&>> matchedList;
    SortAlgorithms* sortStrategy;

public:
    void setStrategy(SortAlgorithms* strategy) override;
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::pair<const iFreight&, const iCargo&>> getMatchedList() override;

    std::vector<std::pair<const iFreight&, const iCargo&>> createMatchedList(
        const std::vector<const iFreight*>& freights,
        const std::vector<const iCargo*>& cargos);
};
