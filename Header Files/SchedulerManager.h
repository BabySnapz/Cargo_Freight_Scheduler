#pragma once

#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <memory>
#include "iSchedulerManager.h"
#include "SchedulerPairVerifier.h"
#include "SortAlgorithms.h"

class SchedulerManager : public iSchedulerManager
{
private:
    FileHandler& fileHandler;
    std::vector<std::unique_ptr<iFreight>> freightClones;
    std::vector<std::unique_ptr<iCargo>> cargoClones;

    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> matchedList;
    SortAlgorithms* sortStrategy = nullptr;

public:
    SchedulerManager(FileHandler& fileHandler); // constructor
    void setStrategy(SortAlgorithms* strategy) override;
    void exportSchedule(const std::string& filepath) override;
    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> getMatchedList() override;
    std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> createMatchedList(
        const std::vector<iFreight*>& freights,
        const std::vector<iCargo*>& cargos) override;
};
