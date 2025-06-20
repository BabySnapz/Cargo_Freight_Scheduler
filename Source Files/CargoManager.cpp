#include "CargoManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Records* CargoManager::makeRecord(const string& id, const string& refuelStop, const string& refuelTime) {
    return new Cargo(id, refuelStop, refuelTime);
}

bool CargoManager::addRecordToVector(Records* record) {
    auto c = static_cast<Cargo*>(record);
    cargos.push_back(c);
    return true;
}

bool CargoManager::addCargo(Cargo* cargo)
{
    return addRecordToVector(cargo);
}

const vector<Cargo*>& CargoManager::getAllCargos() const {
    return cargos;
}
