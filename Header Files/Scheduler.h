#pragma once

#include <string>
#include <vector>
#include <utility>
#include "FreightManager.h"
#include "CargoManager.h"
#include "Freight.h"
#include "Cargo.h"

class Scheduler
{
private:
    FreightManager freightMgr;
    CargoManager cargoMgr;

    std::vector<std::pair<Records*, Records*>> matchedList;
    std::vector<Records*> unmatchedFreights;
    std::vector<Records*> unmatchedCargos;

public:
    void Start();

    void loadFreights(const std::string& filepath);
    void loadCargos(const std::string& filepath);

    void runScheduling();

    void exportSchedule(const std::string& filepath);

    void addFreight(const Freight& freight);
    void editFreight(const std::string& id, const Freight& updatedFreight);
    void deleteFreight(const std::string& id);

    void addCargo(const Cargo& cargo);
    void editCargo(const std::string& id, const Cargo& updatedCargo);
    void deleteCargo(const std::string& id);

    std::vector<std::pair<Records*, Records*>> getMatchedList() const;
    std::vector<Records*> getUnmatchedFreights() const;
    std::vector<Records*> getUnmatchedCargos() const;
    FreightManager& getFreightManager();
    CargoManager& getCargoManager();

}; 
