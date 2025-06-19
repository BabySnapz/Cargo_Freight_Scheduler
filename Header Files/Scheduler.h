#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iomanip>
#include "FreightManager.h"
#include "CargoManager.h"
#include "Freight.h"
#include "Cargo.h"

class Scheduler
{
private:
	bool finished = false;
    FreightManager freightMgr;
    CargoManager cargoMgr;

    std::vector<std::pair<Freight*, Cargo*>> matchedList;
    std::vector<Freight*> unmatchedFreights;
    std::vector<Cargo*> unmatchedCargos;

    

public:
    void Start();

    void loadFreights(const std::string& filepath);
    void loadCargos(const std::string& filepath);

    void removeMatchesWithFreightID(const std::string& freightID);
    void removeMatchesWithCargoID(const std::string& cargoID);

    bool runScheduling();

    void exportSchedule(const std::string& filepath);

    bool addFreight(const Freight& freight);
    bool editFreight(const std::string& id, const Freight& updatedFreight);
    bool deleteFreight(const std::string& id);

    bool addCargo(const Cargo& cargo);
    bool editCargo(const std::string& id, const Cargo& updatedCargo);
    bool deleteCargo(const std::string& id);

    std::vector<std::pair<Freight*, Cargo*>> getMatchedList() const;
    std::vector<Freight*> getUnmatchedFreights() const;
    std::vector<Cargo*> getUnmatchedCargos() const;
    FreightManager& getFreightManager();
    CargoManager& getCargoManager();

}; 
