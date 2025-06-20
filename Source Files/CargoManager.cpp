#include <string>
#include <vector>

using namespace std;

#include "CargoManager.h"

Records* CargoManager::makeRecord(const string& id, const string& refuelStop, const string& refuelTime) {
    return new Cargo(id, refuelStop, refuelTime);
}

bool CargoManager::addCargo(Cargo* cargo)
{
    return addRecordToVector(cargo);
}

