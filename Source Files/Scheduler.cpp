#include "Scheduler.h"
#include <iostream>

using namespace std;

void Scheduler::Start()
{
    cout << "Scheduler started." << endl;
}

void Scheduler::loadFreights(const string& filepath)
{
    freightMgr.loadFromFile(filepath);
}

void Scheduler::loadCargos(const string& filepath)
{
    cargoMgr.loadFromFile(filepath);
}

void Scheduler::runScheduling()
{

    cout << "Running scheduling algorithm..." << endl;
}

void Scheduler::exportSchedule(const string& filepath)
{

    cout << "Exporting schedule to " << filepath << endl;
}

void Scheduler::addFreight(const Freight& freight)
{
    freightMgr.addFreight(new Freight(freight));
}

void Scheduler::editFreight(const string& id, const Freight& updatedFreight)
{
    freightMgr.editRecord(id, new Freight(updatedFreight));
}

void Scheduler::deleteFreight(const string& id)
{
    freightMgr.deleteRecord(id);
}

void Scheduler::addCargo(const Cargo& cargo)
{
    cargoMgr.addCargo(new Cargo(cargo));
}

void Scheduler::editCargo(const string& id, const Cargo& updatedCargo)
{
    cargoMgr.editRecord(id, new Cargo(updatedCargo));
}

void Scheduler::deleteCargo(const string& id)
{
    cargoMgr.deleteRecord(id);
}

std::vector<std::pair<Freight, Cargo>> Scheduler::getMatchedList() const
{

    return {};
}
FreightManager& Scheduler::getFreightManager()
{
    return freightMgr;
}

CargoManager& Scheduler::getCargoManager()
{
    return cargoMgr;
}