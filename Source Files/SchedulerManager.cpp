#include "SchedulerManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

SchedulerManager::SchedulerManager(FileHandler& fileHandler) : fileHandler(fileHandler){}

void SchedulerManager::setStrategy(SortAlgorithms* strategy)
{
    this->sortStrategy = strategy;

}

void SchedulerManager::exportSchedule(const std::string& filepath)
{
    fileHandler.exportSchedule(filepath, matchedList); // uses existing FileHandler
}

std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> SchedulerManager::getMatchedList()
{
    if (matchedList.empty())
    {
        std::cout << "[DEBUG] Matched list is empty!\n";
        return {};
    }
    return matchedList;
}

std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> SchedulerManager::createMatchedList(
    const std::vector<iFreight*>& freights,
    const std::vector<iCargo*>& cargos)
{
    if (!sortStrategy) {
        std::cout << "[DEBUG] Sort strategy not set!\n";
        return {};
    }

    // Clear previous clones and matches
    freightClones.clear();
    cargoClones.clear();
    matchedList.clear();

    // Clone freights with proper type conversion
    for (const auto* f : freights) {
        std::unique_ptr<iRecord> clonedRecord = f->clone();
        iFreight* clonedFreight = dynamic_cast<iFreight*>(clonedRecord.release());
        if (clonedFreight) {
            freightClones.emplace_back(clonedFreight);
        }
        else {
            std::cerr << "[ERROR] clone() did not return an iFreight*\n";
        }
    }

    // Clone cargos with proper type conversion
    for (const auto* c : cargos) {
        std::unique_ptr<iRecord> clonedRecord = c->clone();
        iCargo* clonedCargo = dynamic_cast<iCargo*>(clonedRecord.release());
        if (clonedCargo) {
            cargoClones.emplace_back(clonedCargo);
        }
        else {
            std::cerr << "[ERROR] clone() did not return an iCargo*\n";
        }
    }

    // Prepare raw pointers for sorting and matching
    std::vector<iFreight*> sortedFreights;
    std::vector<iCargo*> sortedCargos;

    for (auto& fPtr : freightClones) sortedFreights.push_back(fPtr.get());
    for (auto& cPtr : cargoClones) sortedCargos.push_back(cPtr.get());

    // Sort using the strategy
    sortStrategy->sort(sortedFreights, sortedCargos);

    // Perform matching and fill matchedList
    for (auto* freight : sortedFreights) {
        int remaining = freight->getRemainingCapacity();

        for (auto* cargo : sortedCargos) {
            if (cargo->getCargoGrouping() == 0)
                continue;

            if (!SchedulerPairVerifier::isMatched(*cargo, *freight))
                continue;

            int grouping = cargo->getCargoGrouping();
            int toUse = std::min(remaining, grouping);

            freight->useCapacity(toUse);
            cargo->useCargoGrouping(toUse);

            matchedList.emplace_back(
                *freight,
                *cargo,
                toUse,
                freight->getRemainingCapacity()
            );

            remaining = freight->getRemainingCapacity();
            if (remaining == 0)
                break;
        }
    }
    return matchedList;
}