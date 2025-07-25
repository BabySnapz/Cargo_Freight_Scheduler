#include "SchedulerManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

void SchedulerManager::setStrategy(SortAlgorithms* strategy)
{
    this->sortStrategy = strategy;

}

void SchedulerManager::exportSchedule(const std::string& filepath) {
    // --- 1. Resolve path ---
    fs::path p(filepath);
    fs::path out;
    if (p.has_filename() && p.extension() == ".txt") {
        out = p;
    }
    else {
        if (!fs::exists(p)) fs::create_directories(p);
        out = p / "Schedule.txt";
    }

    // --- 2. Open file ---
    std::ofstream ofs(out);
    if (!ofs) {
        std::cerr << "Failed to open " << out << "\n";
        return;
    }

    // --- 3. Write header (optional) ---
    ofs << "=== Freight???Cargo Schedule ===\n";

    // --- 4. Stream each match exactly as viewSchedule() does ---
    auto list = getMatchedList();
    if (list.empty()) {
        ofs << "No matches found.\n";
    }
    else {
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& [freight, cargo, used, remain] = list[i];
            ofs << "Match " << (i + 1) << ":\n"
                << "  Freight: " << freight << "\n"
                << "  Cargo:   " << cargo << "\n"
                << "  Used:    " << used << "\n"
                << "  Remain:  " << remain << "\n\n";
        }
    }
    ofs.close();
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

    // Make copies to sort
    std::vector<iFreight*> sortedFreights = freights;
    std::vector<iCargo*> sortedCargos = cargos;
    sortStrategy->sort(sortedFreights, sortedCargos);

    matchedList.clear();
   
    // 1) Track which cargos are already consumed
    std::vector<bool> cargoMatched(sortedCargos.size(), false);

    for (auto* freight : sortedFreights) {
        int remaining = freight->getRemainingCapacity();

        for (size_t i = 0; i < sortedCargos.size(); ++i) {
            if (cargoMatched[i])
                continue;                     // skip already matched

            auto* cargo = sortedCargos[i];
            if (!SchedulerPairVerifier::isMatched(*cargo, *freight))
                continue;

            int grouping = cargo->getCargoGrouping();
            // 3) Decide how much to assign this time
            int toUse = std::min(remaining, grouping);

            // 4) Apply it
            freight->useCapacity(toUse);
            cargo->useCargoGrouping(toUse);
            cargoMatched[i] = true;          // mark this cargo as done

            // 5) Record exactly the same fields you show in viewSchedule()
            matchedList.emplace_back(
                *freight,
                *cargo,
                toUse,
                freight->getRemainingCapacity()
            );

            // 6) Stop if this freight is now full
            remaining = freight->getRemainingCapacity();
            if (remaining == 0)
                break;
        }
    }

    return matchedList;  // now your member is properly populated
}