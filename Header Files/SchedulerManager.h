#pragma once

#include <vector>
#include <string>
#include <utility>
#include "iSchedulerManager.h"
#include "SchedulerPairVerifier.h"
#include "SortAlgorithms.h"

class SchedulerManager : public iSchedulerManager, SchedulerPairVerifier
{
private:
    std::vector<std::pair<const Freight&, const Cargo&>> matchedList;
    SortAlgorithms* sortStrategy;

public:
    void setStrategy(SortAlgorithms* strategy);
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::pair<const Freight&, const Cargo&>> getMatchedList() override;

    std::vector<std::pair<const Freight&, const Cargo&>> createMatchedList(const std::vector<Freight>& freights, const std::vector<Cargo>& cargos);
};

