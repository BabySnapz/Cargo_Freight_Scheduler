#include "FreightManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Records* FreightManager::makeRecord(const string& id, const string& destination, const string& arrivalTime) {
	return new Freight(id, destination, arrivalTime);
}

bool FreightManager::addRecordToVector(Records* record) {
    auto f = static_cast<Freight*>(record);
    freights.push_back(f);
    return true;
}

bool FreightManager::addFreight(Freight* freight)
{
  return addRecordToVector(freight);
}

const std::vector<Freight*>& FreightManager::getAllFreights() const {
    return freights;
}
