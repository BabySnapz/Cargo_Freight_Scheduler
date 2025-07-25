#include "SchedulerManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void SchedulerManager::setStrategy(SortAlgorithms* strategy)
{
    this->sortStrategy = strategy;

}

void SchedulerManager::exportSchedule(const std::string& filepath)
{
    fs::path inputPath(filepath);
    fs::path filePath;

    if (inputPath.has_filename() && inputPath.extension() == ".txt")
    {
        filePath = inputPath;
    }
    else
    {
        if (!fs::exists(inputPath)) {
            try
            {
                fs::create_directories(inputPath);
            }
            catch (const fs::filesystem_error& e)
            {
                cerr << "Failed to create directory: " << e.what() << endl;
                return;
            }
        }
        filePath = inputPath / "Schedule.txt";
    }

    // Export logic would go here (if needed)
}

std::vector<std::pair<const iFreight&, const iCargo&>> SchedulerManager::getMatchedList()
{
	if (matchedList.empty()) 
    {
		std::cout << "[DEBUG] Matched list is empty!\n";
		return {};
	}
    return matchedList;
}

std::vector<std::pair<const iFreight&, const iCargo&>> SchedulerManager::createMatchedList(
    const std::vector< iFreight*>& freights,
    const std::vector< iCargo*>& cargos)
{
    if (!sortStrategy) {
        std::cout << "[DEBUG] Sort strategy not set!\n";
        return {};
    }

    // Make copies to sort
    std::vector<iFreight*> sortedFreights = freights;
    std::vector<iCargo*> sortedCargos = cargos;
    sortStrategy->sort(sortedFreights, sortedCargos);

    matchedList.clear();
    std::vector<bool> cargoMatched(sortedCargos.size(), false);

    for (auto* freight : sortedFreights) {
        int remainingCapacity = freight->getRemainingCapacity();
        for (size_t i = 0; i < sortedCargos.size(); ++i) {
            if (cargoMatched[i]) continue;
            iCargo* cargo = sortedCargos[i];
            int cargoGrouping = cargo->getCargoGrouping();

            if (!SchedulerPairVerifier::isMatched(*cargo, *freight)) continue;

            if (cargoGrouping <= remainingCapacity) {
                matchedList.emplace_back(*freight, *cargo);
                freight->useCapacity(cargoGrouping);
                cargo->useCargoGrouping(cargoGrouping);
                cargoMatched[i] = true;
                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) break;
            } else if (cargoGrouping > remainingCapacity) {
                freight->useCapacity(remainingCapacity);
                cargo->useCargoGrouping(remainingCapacity);
                matchedList.emplace_back(*freight, *cargo);
                remainingCapacity = freight->getRemainingCapacity();
                if (remainingCapacity == 0) break;
            }
        }
    }
    return matchedList;
}