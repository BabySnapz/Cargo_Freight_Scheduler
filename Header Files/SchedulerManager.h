#pragma once

#include <vector>
#include <string>
#include <utility>
#include "iSchedulerManager.h"
#include "Freight.h"
#include "Cargo.h"
#include "SortAlgorithms.h"

class SchedulerManager
{
private:
    std::vector<std::pair<const Freight&, const Cargo&>> matchedList;
    SortAlgorithms* sortStrategy;

public:
    void setStrategy(SortAlgorithms* strategy);
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::pair<const Freight&, const Cargo&>> getMatchedList() override;

    virtual std::vector<std::pair<const Freight&, const Cargo&>> createMatchedList(const Freight& freights, const Cargo& cargos);
};

